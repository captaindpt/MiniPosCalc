#include <stdio.h>
#include <string.h>
#include <math.h>

struct member{
    float lat;
    float lon;
    float alt;
    char name[15];  
};

struct member returnMemeber(){
    float lat = 1234;
    float lon = 2345;
    float alt = 3456;
    char name[15] = "james";

    struct member Mymember;
    Mymember.lat = lat;
    Mymember.lon = lon;
    Mymember.alt = alt;
    strcpy(Mymember.name, name);

    return Mymember;
}


void addmem(struct member *stc, int *n){
    float lat;
    float lon;
    float alt;
    char name[15];

    printf("enter latitude");
    scanf("%d", &lat);
    printf("enter long");
    scanf("%d", &lon);
    printf("eneter altitufr");
    scanf("%d", &alt);
    printf("enter name");
    scanf("%s", name);
    
    struct member thismember;
    thismember.lat = lat;
    thismember.lon = lon;
    thismember.alt = alt;
    strcpy(thismember.name, name);

    stc[*n]= thismember;

    *n = *n +1; }

void scanmem(char *string){
    int x;
    struct member people[x];
    x = 0;
    FILE *ptr;
    ptr = fopen(string, "r");

}


int main (){ 
// distance function
   int i;
for(i=1; i<3; i++){
    struct memeber Mymember;
    struct memeber memeber[i];
    float latm, lonm, altm, distance;
    distance= sqrt((latm+lat)*(latm+lat));
}
}