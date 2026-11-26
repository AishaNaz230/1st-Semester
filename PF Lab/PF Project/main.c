#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define MAX_PACKAGES   500
#define MAX_BOOKINGS   5000
#define LINE_BUF       512
#define FIELD_LEN      64
#define ENC_KEY        5

#define PACKAGES_FILE  "packages.txt"
#define BOOKINGS_FILE  "booking.txt"
#define ADMIN_FILE     "admin.txt"

typedef struct {
    char   destination[FIELD_LEN];
    char   hotel_type[FIELD_LEN];
    char   vehicle_type[FIELD_LEN];
    int    days;
    double price;               /* price per person */
} Package;

typedef struct {
    char   name[FIELD_LEN];
    char   cnic[FIELD_LEN];
    int    persons;
    char   date[FIELD_LEN];
    int    package_number;      /* package's position when it was booked (for reference only) */
    double bill;
    char   destination[FIELD_LEN];   /* snapshot of the package at booking time */
    char   hotel_type[FIELD_LEN];
    char   vehicle_type[FIELD_LEN];
    int    days;
} Booking;

static Package packages[MAX_PACKAGES];
static int     package_count = 0;
static int     unsaved_changes = 0;   /* admin edits not yet written to disk */

/* ====================================================================== */
/*                           Small utilities                              */
/* ====================================================================== */

static void trim(char *s) {
    size_t n = strlen(s);
    while (n > 0 && isspace((unsigned char)s[n - 1])) s[--n] = '\0';
    size_t lead = 0;
    while (s[lead] && isspace((unsigned char)s[lead])) lead++;
    if (lead) memmove(s, s + lead, strlen(s + lead) + 1);
}

static void copy_field(char *dst, const char *src, size_t cap) {
    strncpy(dst, src, cap - 1);
    dst[cap - 1] = '\0';
}

/* Reads one line (without newline). Returns 0 on EOF. Handles too-long lines. */
static int read_line(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    if (!strchr(buf, '\n')) {            /* line was longer than buffer: discard rest */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    trim(buf);
    return 1;
}

static void prompt_line(const char *label, char *buf, size_t size) {
    printf("%s", label);
    fflush(stdout);
    if (!read_line(buf, size)) {         /* stdin closed -> exit cleanly */
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
}

/* Password input without echo (falls back to normal input if not a terminal) */
static void read_password(const char *label, char *buf, size_t size) {
    printf("%s", label);
    fflush(stdout);

    size_t i = 0;
    int c;

    while ((c = _getch()) != '\r' && c != '\n' && c != EOF) {
        if (c == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } 
        else if (i < size - 1 && c >= 32) {
            buf[i++] = (char)c;
            putchar('*');
        }
    }

    buf[i] = '\0';
    putchar('\n');
}

static void xor_crypt(char *s) {
    for (int i = 0; s[i]; i++) s[i] = (char)(s[i] ^ ENC_KEY);
}

/* ---- validated numeric input ---- */

static int parse_int(const char *s, int *out) {
    char *end;
    if (!*s) return 0;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v > 1000000 || v < -1000000) return 0;
    *out = (int)v;
    return 1;
}

static int parse_double(const char *s, double *out) {
    char *end;
    if (!*s) return 0;
    double v = strtod(s, &end);
    if (*end != '\0' || v != v || v > 1e12 || v < -1e12) return 0;
    *out = v;
    return 1;
}

/* Keeps asking until a valid int in [lo, hi] is entered. */
static int ask_int(const char *label, int lo, int hi) {
    char buf[64];
    int v;
    for (;;) {
        prompt_line(label, buf, sizeof(buf));
        if (parse_int(buf, &v) && v >= lo && v <= hi) return v;
        printf("  Invalid input. Enter a whole number between %d and %d.\n", lo, hi);
    }
}

static double ask_positive_double(const char *label) {
    char buf[64];
    double v;
    for (;;) {
        prompt_line(label, buf, sizeof(buf));
        if (parse_double(buf, &v) && v > 0) return v;
        printf("  Invalid input. Enter a number greater than 0.\n");
    }
}

/* Text field: required, and must not contain '|' (our file delimiter). */
static void ask_text(const char *label, char *out, size_t size) {
    char buf[LINE_BUF];
    for (;;) {
        prompt_line(label, buf, sizeof(buf));
        if (!*buf)               { printf("  This field cannot be empty.\n"); continue; }
        if (strchr(buf, '|'))    { printf("  The '|' character is not allowed.\n"); continue; }
        if (strlen(buf) >= size) { printf("  Too long (max %d characters).\n", (int)size - 1); continue; }
        copy_field(out, buf, size);
        return;
    }
}

/* Optional text for update: blank keeps the old value. */
static void ask_text_keep(const char *label, char *current, size_t size) {
    char buf[LINE_BUF];
    for (;;) {
        printf("%s [%s]: ", label, current);
        fflush(stdout);
        if (!read_line(buf, sizeof(buf))) { printf("\n"); exit(0); }
        if (!*buf) return;
        if (strchr(buf, '|'))    { printf("  The '|' character is not allowed.\n"); continue; }
        if (strlen(buf) >= size) { printf("  Too long (max %d characters).\n", (int)size - 1); continue; }
        copy_field(current, buf, size);
        return;
    }
}

static int ask_yes_no(const char *label) {
    char buf[16];
    for (;;) {
        prompt_line(label, buf, sizeof(buf));
        if (buf[0] == 'y' || buf[0] == 'Y') return 1;
        if (buf[0] == 'n' || buf[0] == 'N') return 0;
        printf("  Please type y or n.\n");
    }
}

/* ---- CNIC & date validation ---- */

static int valid_cnic(const char *s) {
    if (strlen(s) != 13) return 0;
    for (int i = 0; i < 13; i++)
        if (!isdigit((unsigned char)s[i])) return 0;
    return 1;
}

static int is_leap(int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }

static int days_in_month(int m, int y) {
    static const int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return (m == 2 && is_leap(y)) ? 29 : d[m - 1];
}

/* Accepts DD/MM/YYYY or DD-MM-YYYY, must be a real date, not in the past.
 * Normalises to DD/MM/YYYY in `out`. Returns 1 if OK. */
static int parse_travel_date(const char *in, char *out, size_t out_size, const char **err) {
    int d, m, y;
    char sep1, sep2;
    if (sscanf(in, "%d%c%d%c%d", &d, &sep1, &m, &sep2, &y) != 5 ||
        (sep1 != '/' && sep1 != '-') || sep1 != sep2) {
        *err = "Use the format DD/MM/YYYY (example: 25/12/2026).";
        return 0;
    }
    if (y < 2000 || y > 2100 || m < 1 || m > 12 || d < 1 || d > days_in_month(m, y)) {
        *err = "That is not a valid calendar date.";
        return 0;
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int ty = t->tm_year + 1900, tm_ = t->tm_mon + 1, td = t->tm_mday;
    if (y < ty || (y == ty && (m < tm_ || (m == tm_ && d < td)))) {
        *err = "Travelling date cannot be in the past.";
        return 0;
    }
    snprintf(out, out_size, "%02d/%02d/%04d", d, m, y);
    return 1;
}

/* ====================================================================== */
/*                         File handling                                  */
/* ====================================================================== */

/* Splits `line` on '|' in place. Returns number of fields found (max `max`). */
static int split_fields(char *line, char *fields[], int max) {
    int n = 0;
    char *p = line;
    while (n < max) {
        fields[n++] = p;
        p = strchr(p, '|');
        if (!p) break;
        *p++ = '\0';
    }
    return n;
}

static int load_packages(void) {
    FILE *fp = fopen(PACKAGES_FILE, "r");
    package_count = 0;
    if (!fp) return 0;

    char line[LINE_BUF];
    while (fgets(line, sizeof(line), fp) && package_count < MAX_PACKAGES) {
        trim(line);
        if (!*line) continue;
        char *f[5];
        if (split_fields(line, f, 5) != 5) continue;
        for (int i = 0; i < 5; i++) trim(f[i]);

        Package *p = &packages[package_count];
        int days; double price;
        if (!parse_int(f[3], &days) || !parse_double(f[4], &price)) continue;
        copy_field(p->destination,  f[0], sizeof(p->destination));
        copy_field(p->hotel_type,   f[1], sizeof(p->hotel_type));
        copy_field(p->vehicle_type, f[2], sizeof(p->vehicle_type));
        p->days = days;
        p->price = price;
        package_count++;
    }
    fclose(fp);
    unsaved_changes = 0;
    return package_count;
}

static int save_packages(void) {
    FILE *fp = fopen(PACKAGES_FILE, "w");
    if (!fp) return 0;
    for (int i = 0; i < package_count; i++)
        fprintf(fp, "%s|%s|%s|%d|%.2f\n", packages[i].destination, packages[i].hotel_type,
                packages[i].vehicle_type, packages[i].days, packages[i].price);
    fclose(fp);
    unsaved_changes = 0;
    return 1;
}

/* Loads bookings using the single 10-field booking format. Caller frees the array.
 * Returns the number of loaded bookings, or -1 if the file cannot be opened. */
static int load_bookings(Booking **out) {
    *out = NULL;

    FILE *fp = fopen(BOOKINGS_FILE, "r");
    if (!fp) return -1;

    Booking *arr = malloc(sizeof(Booking) * MAX_BOOKINGS);
    if (!arr) {
        fclose(fp);
        return -1;
    }

    int n = 0;
    char line[LINE_BUF];

    while (fgets(line, sizeof(line), fp) && n < MAX_BOOKINGS) {
        trim(line);
        if (!*line) continue;

        char *f[10];
        if (split_fields(line, f, 10) != 10) continue;

        for (int i = 0; i < 10; i++) trim(f[i]);

        int persons, pkg, days;
        double bill;
        if (!parse_int(f[2], &persons) ||
            !parse_int(f[4], &pkg) ||
            !parse_double(f[5], &bill) ||
            !parse_int(f[9], &days))
            continue;

        Booking *b = &arr[n];
        memset(b, 0, sizeof(*b));

        copy_field(b->name, f[0], sizeof(b->name));
        copy_field(b->cnic, f[1], sizeof(b->cnic));
        b->persons = persons;
        copy_field(b->date, f[3], sizeof(b->date));
        b->package_number = pkg;
        b->bill = bill;
        copy_field(b->destination, f[6], sizeof(b->destination));
        copy_field(b->hotel_type, f[7], sizeof(b->hotel_type));
        copy_field(b->vehicle_type, f[8], sizeof(b->vehicle_type));
        b->days = days;

        n++;
    }

    fclose(fp);
    *out = arr;
    return n;
}

static int save_all_bookings(const Booking *arr, int n) {
    FILE *fp = fopen(BOOKINGS_FILE, "w");
    if (!fp) return 0;
    for (int i = 0; i < n; i++)
        fprintf(fp, "%s|%s|%d|%s|%d|%.2f|%s|%s|%s|%d\n", arr[i].name, arr[i].cnic, arr[i].persons,
                arr[i].date, arr[i].package_number, arr[i].bill, arr[i].destination,
                arr[i].hotel_type, arr[i].vehicle_type, arr[i].days);
    fclose(fp);
    return 1;
}

static int append_booking(const Booking *b) {
    FILE *fp = fopen(BOOKINGS_FILE, "a");
    if (!fp) return 0;
    fprintf(fp, "%s|%s|%d|%s|%d|%.2f|%s|%s|%s|%d\n", b->name, b->cnic, b->persons, b->date,
            b->package_number, b->bill, b->destination, b->hotel_type, b->vehicle_type, b->days);
    fclose(fp);
    return 1;
}

/* ====================================================================== */
/*                            Display                                     */
/* ====================================================================== */

static void line_sep(void) {
    printf("--------------------------------------------------------------------------------\n");
}

static void show_packages(void) {
    printf("\n");
    line_sep();
    printf("%-4s %-20s %-16s %-16s %-5s %14s\n", "No.", "Destination", "Hotel", "Transport", "Days", "Price/person");
    line_sep();
    if (package_count == 0) printf("  (no packages available)\n");
    for (int i = 0; i < package_count; i++)
        printf("%-4d %-20.20s %-16.16s %-16.16s %-5d %11.2f Rs\n", i + 1, packages[i].destination,
               packages[i].hotel_type, packages[i].vehicle_type, packages[i].days, packages[i].price);
    line_sep();
}

#define BOOKING_HEADER "%-3s %-18s %-13s %-10s %-13s %-4s %12s\n"

static void print_booking_row(int idx, const Booking *b) {
    printf("%-3d %-18.18s %-13.13s %-10.10s %-13.13s %-4d %12.2f\n", idx, b->name, b->cnic, b->date,
           b->destination, b->persons, b->bill);
}

static void show_bookings(const Booking *arr, int n) {
    printf("\n");
    line_sep();
    printf(BOOKING_HEADER, "No.", "Name", "CNIC", "Date", "Destination", "Ppl", "Total (Rs)");
    line_sep();
    if (n == 0) printf("  (no bookings yet)\n");
    for (int i = 0; i < n; i++) print_booking_row(i + 1, &arr[i]);
    line_sep();
}

static void print_receipt(const Booking *b) {
    printf("\n========== BOOKING SUCCESSFUL ==========\n");
    printf("Name            : %s\n", b->name);
    printf("CNIC            : %s\n", b->cnic);
    printf("Package Number  : %d\n", b->package_number);
    printf("Destination     : %s\n", b->destination);
    printf("Hotel / Transport: %s / %s\n", b->hotel_type, b->vehicle_type);
    printf("Days            : %d\n", b->days);
    printf("Travelling Date : %s\n", b->date);
    printf("Persons         : %d\n", b->persons);
    printf("Total           : %.2f Rs\n", b->bill);
    printf("========================================\n");
}

/* ====================================================================== */
/*                              User side                                 */
/* ====================================================================== */

static void book_package(int pkg_index) {
    Booking b;
    memset(&b, 0, sizeof(b));

    printf("\nBooking: %s (%s, %s, %d days) - %.2f Rs per person\n",
           packages[pkg_index].destination, packages[pkg_index].hotel_type,
           packages[pkg_index].vehicle_type, packages[pkg_index].days, packages[pkg_index].price);
    printf("(Type 0 at the name prompt to cancel)\n\n");

    char buf[LINE_BUF];
    for (;;) {
        prompt_line("Name: ", buf, sizeof(buf));
        if (strcmp(buf, "0") == 0) { printf("Booking cancelled.\n"); return; }
        if (!*buf)                 { printf("  Name is required.\n"); continue; }
        if (strchr(buf, '|'))      { printf("  The '|' character is not allowed.\n"); continue; }
        if (strlen(buf) >= sizeof(b.name)) { printf("  Name too long.\n"); continue; }
        copy_field(b.name, buf, sizeof(b.name));
        break;
    }

    for (;;) {
        prompt_line("CNIC (13 digits, no dashes): ", buf, sizeof(buf));
        if (valid_cnic(buf)) { copy_field(b.cnic, buf, sizeof(b.cnic)); break; }
        printf("  CNIC must be exactly 13 digits.\n");
    }

    b.persons = ask_int("Number of persons: ", 1, 1000);

    for (;;) {
        const char *err = "";
        prompt_line("Travelling date (DD/MM/YYYY): ", buf, sizeof(buf));
        if (parse_travel_date(buf, b.date, sizeof(b.date), &err)) break;
        printf("  %s\n", err);
    }

    b.package_number = pkg_index + 1;
    b.bill = packages[pkg_index].price * b.persons;
    copy_field(b.destination,  packages[pkg_index].destination,  sizeof(b.destination));
    copy_field(b.hotel_type,   packages[pkg_index].hotel_type,   sizeof(b.hotel_type));
    copy_field(b.vehicle_type, packages[pkg_index].vehicle_type, sizeof(b.vehicle_type));
    b.days = packages[pkg_index].days;

    printf("\nTotal bill will be %.2f Rs.\n", b.bill);
    if (!ask_yes_no("Confirm booking? (y/n): ")) { printf("Booking cancelled.\n"); return; }

    if (!append_booking(&b)) {
        printf("ERROR: could not write to %s. Booking NOT saved.\n", BOOKINGS_FILE);
        return;
    }
    print_receipt(&b);
}

static void customize_package(void) {
    char dest[FIELD_LEN];
    char hotel[FIELD_LEN], vehicle[FIELD_LEN];
    double price;

    printf("\n--- Customize Package ---\n");
    ask_text("Destination: ", dest, sizeof(dest));
    printf("Package types:\n  1. First Class (2500 Rs/km + 1000 Rs/day)\n"
           "  2. Business    (2000 Rs/km +  800 Rs/day)\n"
           "  3. Economy     (1500 Rs/km +  600 Rs/day)\n");
    int ptype = ask_int("Package type (1-3): ", 1, 3);
    int days = ask_int("Number of days: ", 1, 365);
    double distance = ask_positive_double("Distance (km): ");

    switch (ptype) {
        case 1: price = 2500.0 * distance + days * 1000.0; strcpy(hotel, "First Class"); strcpy(vehicle, "First Class"); break;
        case 2: price = 2000.0 * distance + days *  800.0; strcpy(hotel, "Business");    strcpy(vehicle, "Business");    break;
        default:price = 1500.0 * distance + days *  600.0; strcpy(hotel, "Economy");     strcpy(vehicle, "Economy");     break;
    }

    printf("\nCustom package: %s | %s | %s | %d days\n", dest, hotel, vehicle, days);
    printf("Price per person: %.2f Rs\n", price);
    if (!ask_yes_no("Create this package? (y/n): ")) { printf("Cancelled.\n"); return; }

    if (package_count >= MAX_PACKAGES) { printf("ERROR: package limit reached.\n"); return; }

    /* Re-sync with disk first so we don't clobber admin edits, then append. */
    FILE *fp = fopen(PACKAGES_FILE, "a");
    if (!fp) { printf("ERROR: failed to write %s. Custom package not saved.\n", PACKAGES_FILE); return; }
    fprintf(fp, "%s|%s|%s|%d|%.2f\n", dest, hotel, vehicle, days, price);
    fclose(fp);

    load_packages();
    printf("Custom package created as package #%d.\n", package_count);

    if (ask_yes_no("Book it now? (y/n): ")) book_package(package_count - 1);
}

static void user_menu(void) {
    load_packages();
    for (;;) {
        printf("\n=========== USER MENU ===========\n"
               "1. View packages\n"
               "2. Book a package\n"
               "3. Customize a package\n"
               "4. Refresh package list\n"
               "0. Back to main menu\n");
        int ch = ask_int("Choice: ", 0, 4);
        switch (ch) {
            case 1: load_packages(); show_packages(); break;
            case 2:
                load_packages();
                show_packages();
                if (package_count == 0) break;
                {
                    int sel = ask_int("Enter package number to book (0 = cancel): ", 0, package_count);
                    if (sel > 0) book_package(sel - 1);
                }
                break;
            case 3: customize_package(); break;
            case 4: load_packages(); printf("Package list refreshed (%d packages).\n", package_count); break;
            case 0: return;
        }
    }
}

/* ====================================================================== */
/*                              Admin side                                */
/* ====================================================================== */

static int read_admin_file(char *id, size_t id_sz, char *pass, size_t pass_sz) {
    FILE *fp = fopen(ADMIN_FILE, "r");
    if (!fp) return 0;
    char a[LINE_BUF] = "", b[LINE_BUF] = "";
    if (!fgets(a, sizeof(a), fp)) { fclose(fp); return 0; }
    if (!fgets(b, sizeof(b), fp)) b[0] = '\0';
    fclose(fp);
    a[strcspn(a, "\r\n")] = '\0';
    b[strcspn(b, "\r\n")] = '\0';
    copy_field(id, a, id_sz);
    copy_field(pass, b, pass_sz);
    xor_crypt(pass);                      /* decrypt */
    return *id != '\0';
}

static int write_admin_file(const char *id, const char *plain_pass) {
    char enc[FIELD_LEN];
    copy_field(enc, plain_pass, sizeof(enc));
    xor_crypt(enc);
    FILE *fp = fopen(ADMIN_FILE, "w");
    if (!fp) return 0;
    fprintf(fp, "%s\n%s\n", id, enc);
    fclose(fp);
    return 1;
}

/* Creates admin.txt if it does not exist (replaces the separate Admin.c tool). */
static void first_time_admin_setup(void) {
    char id[FIELD_LEN], p1[FIELD_LEN], p2[FIELD_LEN];
    printf("\nNo admin account found. Let's create one.\n");
    for (;;) {
        ask_text("Choose Admin ID: ", id, sizeof(id));
        read_password("Choose password: ", p1, sizeof(p1));
        read_password("Confirm password: ", p2, sizeof(p2));
        if (!*p1)                { printf("  Password cannot be empty.\n"); continue; }
        if (strcmp(p1, p2) != 0) { printf("  Passwords do not match. Try again.\n"); continue; }
        break;
    }
    if (write_admin_file(id, p1)) printf("Admin account created.\n");
    else                          printf("ERROR: could not write %s.\n", ADMIN_FILE);
}

static int admin_login(void) {
    char id[FIELD_LEN], pass[FIELD_LEN];
    if (!read_admin_file(id, sizeof(id), pass, sizeof(pass))) {
        first_time_admin_setup();
        if (!read_admin_file(id, sizeof(id), pass, sizeof(pass))) return 0;
    }
    for (int attempt = 1; attempt <= 3; attempt++) {
        char eid[LINE_BUF], epass[LINE_BUF];
        prompt_line("\nAdmin ID: ", eid, sizeof(eid));
        read_password("Password: ", epass, sizeof(epass));
        if (strcmp(eid, id) == 0 && strcmp(epass, pass) == 0) {
            printf("Login successful.\n");
            return 1;
        }
        printf("Invalid ID or password. (%d/3 attempts)\n", attempt);
    }
    printf("Too many failed attempts.\n");
    return 0;
}

static void read_package_details(Package *p, int is_update) {
    if (is_update) {
        char buf[64];
        double dv; int iv;
        ask_text_keep("Destination", p->destination, sizeof(p->destination));
        ask_text_keep("Hotel type", p->hotel_type, sizeof(p->hotel_type));
        ask_text_keep("Vehicle type", p->vehicle_type, sizeof(p->vehicle_type));
        for (;;) {
            printf("Days [%d]: ", p->days); fflush(stdout);
            if (!read_line(buf, sizeof(buf))) exit(0);
            if (!*buf) break;
            if (parse_int(buf, &iv) && iv > 0 && iv <= 365) { p->days = iv; break; }
            printf("  Enter a whole number between 1 and 365.\n");
        }
        for (;;) {
            printf("Price per person [%.2f]: ", p->price); fflush(stdout);
            if (!read_line(buf, sizeof(buf))) exit(0);
            if (!*buf) break;
            if (parse_double(buf, &dv) && dv > 0) { p->price = dv; break; }
            printf("  Enter a number greater than 0.\n");
        }
    } else {
        ask_text("Destination: ", p->destination, sizeof(p->destination));
        ask_text("Hotel type: ", p->hotel_type, sizeof(p->hotel_type));
        ask_text("Vehicle type: ", p->vehicle_type, sizeof(p->vehicle_type));
        p->days = ask_int("Days: ", 1, 365);
        p->price = ask_positive_double("Price per person (Rs): ");
    }
}

static void admin_add_package(void) {
    if (package_count >= MAX_PACKAGES) { printf("ERROR: package limit reached.\n"); return; }
    Package p;
    memset(&p, 0, sizeof(p));
    printf("\n--- Add Package ---\n");
    read_package_details(&p, 0);
    packages[package_count++] = p;
    unsaved_changes = 1;
    printf("Package added (use 'Save packages' to write it to disk).\n");
}

static void admin_update_package(void) {
    show_packages();
    if (package_count == 0) return;
    int sel = ask_int("Package number to update (0 = cancel): ", 0, package_count);
    if (sel == 0) return;
    printf("Press Enter to keep the current value.\n");
    read_package_details(&packages[sel - 1], 1);
    unsaved_changes = 1;
    printf("Package updated (use 'Save packages' to write it to disk).\n");
}

static void admin_delete_package(void) {
    show_packages();
    if (package_count == 0) return;
    int sel = ask_int("Package number to delete (0 = cancel): ", 0, package_count);
    if (sel == 0) return;

    printf("(Existing bookings keep their own copy of the package details, so they are not affected.)\n");
    char q[128];
    snprintf(q, sizeof(q), "Really delete '%s'? (y/n): ", packages[sel - 1].destination);
    if (!ask_yes_no(q)) { printf("Cancelled.\n"); return; }

    for (int i = sel - 1; i < package_count - 1; i++) packages[i] = packages[i + 1];
    package_count--;
    unsaved_changes = 1;
    printf("Package removed (use 'Save packages' to write it to disk).\n");
}

static void admin_save_packages(void) {
    if (save_packages()) printf("Packages saved to %s.\n", PACKAGES_FILE);
    else                 printf("ERROR: failed to save %s.\n", PACKAGES_FILE);
}

static void admin_view_bookings(void) {
    Booking *arr;
    int n = load_bookings(&arr);
    if (n < 0) { printf("\nNo bookings found (%s missing or unreadable).\n", BOOKINGS_FILE); return; }
    show_bookings(arr, n);
    double total = 0;
    for (int i = 0; i < n; i++) total += arr[i].bill;
    printf("Total bookings: %d   |   Total revenue: %.2f Rs\n", n, total);
    free(arr);
}

static void admin_cancel_booking(void) {
    Booking *arr;
    int n = load_bookings(&arr);
    if (n < 0) { printf("\nNo bookings found.\n"); return; }
    if (n == 0) { printf("\nThere are no bookings to cancel.\n"); free(arr); return; }
    show_bookings(arr, n);
    int sel = ask_int("Booking number to cancel (0 = cancel): ", 0, n);
    if (sel > 0) {
        char q[128];
        snprintf(q, sizeof(q), "Really delete booking of '%s'? (y/n): ", arr[sel - 1].name);
        if (ask_yes_no(q)) {
            for (int i = sel - 1; i < n - 1; i++) arr[i] = arr[i + 1];
            n--;
            if (save_all_bookings(arr, n)) printf("Booking removed.\n");
            else                           printf("ERROR: could not rewrite %s.\n", BOOKINGS_FILE);
        }
    }
    free(arr);
}

static void admin_change_password(void) {
    char id[FIELD_LEN], pass[FIELD_LEN], cur[LINE_BUF], n1[FIELD_LEN], n2[FIELD_LEN];
    if (!read_admin_file(id, sizeof(id), pass, sizeof(pass))) { printf("ERROR: cannot read admin file.\n"); return; }
    read_password("Current password: ", cur, sizeof(cur));
    if (strcmp(cur, pass) != 0) { printf("Wrong current password.\n"); return; }
    read_password("New password: ", n1, sizeof(n1));
    read_password("Confirm new password: ", n2, sizeof(n2));
    if (!*n1 || strcmp(n1, n2) != 0) { printf("Passwords empty or do not match. Not changed.\n"); return; }
    if (write_admin_file(id, n1)) printf("Password changed.\n");
    else                          printf("ERROR: could not write %s.\n", ADMIN_FILE);
}

static void admin_menu(void) {
    load_packages();
    for (;;) {
        printf("\n=========== ADMIN MENU ===========%s\n", unsaved_changes ? "  [unsaved changes]" : "");
        printf("1. View packages\n"
               "2. Add package\n"
               "3. Update package\n"
               "4. Delete package\n"
               "5. Save packages\n"
               "6. View bookings\n"
               "7. Cancel (delete) a booking\n"
               "8. Change admin password\n"
               "0. Logout\n");
        int ch = ask_int("Choice: ", 0, 8);
        switch (ch) {
            case 1: show_packages(); break;
            case 2: admin_add_package(); break;
            case 3: admin_update_package(); break;
            case 4: admin_delete_package(); break;
            case 5: admin_save_packages(); break;
            case 6: admin_view_bookings(); break;
            case 7: admin_cancel_booking(); break;
            case 8: admin_change_password(); break;
            case 0:
                if (unsaved_changes) {
                    if (ask_yes_no("You have unsaved package changes. Save before logout? (y/n): "))
                        admin_save_packages();
                }
                return;
        }
    }
}

/* ====================================================================== */
/*                                 main                                   */
/* ====================================================================== */

int main(void) {
    load_packages();
    for (;;) {
        printf("\n====================================\n"
               "   TOURIST MANAGEMENT SYSTEM\n"
               "====================================\n"
               "1. User\n"
               "2. Admin\n"
               "0. Exit\n");
        int ch = ask_int("Choice: ", 0, 2);
        if (ch == 1)      user_menu();
        else if (ch == 2) { if (admin_login()) admin_menu(); }
        else { printf("Goodbye!\n"); return 0; }
    }
}
