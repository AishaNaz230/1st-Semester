#include<stdio.h>
int markZone(char map[][5],int r,int c,char label){
if(r<0||r>=5||c<0||c>=5||map[r][c]!='*'){
    return 0;
}
map[r][c]=label;
return 1+markZone(map,r-1,c,label)+markZone(map,r+1,c,label)+markZone(map,r,c-1,label)+markZone(map,r,c+1,label);
}
int main(){
float temp[5][5]={{2.1,-1.5,-2.0,3.0,4.2},{1.8,-0.5,2.5,3.1,-1.0},{3.3,2.0,1.5,-0.8,-2.0},{-1.2,3.4,4.0,3.8,-0.6},{-2.5,-3.1,5.1,6.0,4.7}};
char map[5][5];
int i,j;
for(i=0;i<5;i++){
    for(j=0;j<5;j++){
    map[i][j]=(temp[i][j]<0)?'*':'.';
    }
}
char label='A';
int totalZones=0;
for(i=0;i<5;i++){
for(j=0;j<5;j++){
if(map[i][j]=='*'){
int size=markZone(map,i,j,label);
printf("Zone %c: %d stations\n",label,size);
label++;
totalZones++;
}
}
}
printf("Total zones: %d\n",totalZones);
for(i=0;i<5;i++){
for(j=0;j<5;j++){
    printf("%c ",map[i][j]);
}
printf("\n");
}
}