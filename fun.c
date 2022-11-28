#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

struct user_t {
    char name[50];
    double time;
    double lat;
    double lon;
    double alt;
    //we assume that no more memory will be needed in execution.
};

struct distance {
    struct user_t *first_user;
    struct user_t *second_user;
    double distance;
};

struct user_t *other_users;
struct user_t *our_user;
int *n_other_users;
struct distance *distances;
// global variables can be a pain, so we dont actually use them, we 
// just use to global pointers and point them to our variables in main.

void print_user(struct user_t *user) {
    printf("Name: %s\n", user->name);
    printf("Time: %f\n", user->time);
    printf("Longitude: %f\n", user->lon);
    printf("Latitude: %f\n", user->lat);
    printf("Altitude: %f\n", user->alt);
}

void scan_user(struct user_t *user, char *name, double time, double lat, double lon, double alt) {
    strcpy(user->name, name);
    printf("asfd");
    user->time = time;
    user->lat = lat;
    user->lon = lon;
    user->alt = alt;
}

void manualinput(void) {
    printf("Enter the number of other users you want to enter:\n");
    int n = 0;
    scanf("%d", &n);
    printf("Enter name of our user:\n");
    char *name = malloc(50*sizeof(char));
    scanf("%s", name);
    printf("Enter time of our user:\n");
    double time = 0;
    scanf("%lf", &time);
    printf("Enter lat of our user:\n");
    double lat = 0;
    scanf("%lf", &lat);
    printf("Enter lon of our user:\n");
    double lon = 0;
    scanf("%lf", &lon);
    printf("Enter alt of our user:\n");
    double alt = 0;
    scanf("%lf", &alt);

    scan_user(our_user, name, time, lat, lon, alt);

    for(int i=0; i<n; i++) {
        
        printf("Enter user %d's name: \n", i+1);
        char *name = malloc(50*sizeof(char));
        scanf("%s", name);
        printf("Enter user %d's time: \n", i+1);
        double time;
        scanf("%lf", &time);
        printf("Enter user %d's lat: \n", i+1);
        double lat;
        scanf("%lf", &lat);
        printf("Enter user %d's lon: \n", i+1);
        double lon;
        scanf("%lf", &lon);
        printf("Enter user %d's alt: \n", i+1);
        double alt;
        scanf("%lf", &alt);
        
        scan_user(other_users + i, name, time, lat, lon, alt);

    }
    *n_other_users = n;
}
void autoinput(void) {
    printf("Enter the name of the file which contains user data:\n");
    char *filename = malloc(50*sizeof(char));
    scanf("%s", filename);
    FILE *ptr;
    ptr = fopen(filename, "r");

    int n=0;
    char name[50];
    double time;
    double lat;
    double lon;
    double alt;

    fscanf(ptr, "%d", &n);
    fscanf(ptr, "%s", name);
    fscanf(ptr, "%lf", &time);
    fscanf(ptr, "%lf", &lat);
    fscanf(ptr, "%lf", &lon);
    fscanf(ptr, "%lf", &alt);

    scan_user(our_user, name, time, lat, lon, alt);

    printf("Finished scanning 'our_user'\n");

    for(int i=0; i<n; i++) {

        fscanf(ptr, "%s", name);
        fscanf(ptr, "%lf", &time);
        fscanf(ptr, "%lf", &lat);
        fscanf(ptr, "%lf", &lon);
        fscanf(ptr, "%lf", &alt);

        scan_user(other_users + i, name, time, lat, lon, alt);        

    }
    *n_other_users = n;
    fclose(ptr);
    printf("Finished scanning 'other_users'\n");

}


void calc_distances(void) {
    int lon1 = our_user->lon;
    int lat1 = our_user->lat;
    int alt1 = our_user->alt;

    for(int i=0; i<*n_other_users; i++) {
        struct distance dis1;
        
        int lon2 = (other_users+i)->lon;
        int lat2 = (other_users+i)->lat;
        int alt2 = (other_users+i)->alt;

        double final = sqrt(pow(lon1-lon2, 2)+pow(lat1-lat2, 2)+pow(alt1-alt2, 2));
        
        (distances+i)->first_user = our_user;
        (distances+i)->second_user = (other_users+i);
        (distances+i)->distance = final;

    }
}

struct distance *calc_min(void) {
    double min = INT_MAX;
    struct distance *user_dist;
    for(int i=0; i<*n_other_users; i++) {
        if( (distances+i)->distance < min ) {
            min = (distances+i)->distance;
            user_dist = (distances+i);
        }
    }
    return user_dist;
}

void print_otherusers(void) {
    for(int i=0; i<*n_other_users; i++) {
        print_user(other_users + i);
    }
} 

void print_distance(struct distance *dist) {
    printf("*******\n");
    printf("first user: %s\n", dist->first_user->name);
    printf("second user: %s\n", dist->second_user->name);
    printf("Distance: %lf\n", dist->distance);
}

void print_distances(void) {
    for(int i=0; i<*n_other_users; i++) {
        print_distance(distances+i);
    }
}

int main (void){

    struct user_t OUR_USER;
    our_user = &OUR_USER;
    struct user_t * OTHER_USERS = malloc(100 * sizeof(struct user_t));
    other_users = OTHER_USERS;
    int n_of_other_users = 0;
    n_other_users = &n_of_other_users;

    printf("To enter User Data Manually, press 1,\n");
    printf("And to read User Data from a File, press 2 then hit enter.\n");

    int option = 0;
    scanf("%d", &option);
    switch (option) {
        case 1:
            manualinput();
            break;
        case 2:
            autoinput();
            break;
    }

    struct distance * DISTANCES = malloc(*n_other_users*sizeof(struct distance));
    distances = DISTANCES;

    printf("*********\nprinting our user:\n");
    print_user(our_user);
    printf("*********\nprinting other users:\n");
    print_otherusers();

    printf("Calculating distances from our user to other users...\n");
    calc_distances();

    print_distances();



    struct distance *closest_dist = calc_min();
    printf("Calculating the closest user to our user...\n");

    printf("the user %s is the closest user to our user. they're distance is: %lf meters.", closest_dist->second_user->name, closest_dist->distance);
}