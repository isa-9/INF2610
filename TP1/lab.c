/* INF2610 - TP1
/ Matricule 1 : 2204379
/ Matricule 2 : 2212694
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>

struct Wheel {
    int id;
    bool isRearWheel;
};

struct Wing {
    int* id;
};

struct Plane {
    char* id;
    char planeType[10];
    bool isAvailable;
    struct Wheel* wheels;
    struct Wing* wings;
};

struct Wheel *createWheels(int id) {
    struct Wheel* wheels = malloc(7 * sizeof(struct Wheel));
    for(int i = 0; i < 7; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = i > 2;
    }
    return wheels;
}

void populateWingAttributes(struct Wing* wing, int id) {
    printf("AAAA");
    for(int i = 0; i < 9; i++) {
        printf("i: %d", i);
        wing->id[i] = id % 10;
        id /= 10;
    }
}

struct Wing* createWings(long id) {
    struct Wing* wings = malloc(2 * sizeof(struct Wing));
    wings[0].id = malloc(9 * sizeof(int));
    wings[1].id = malloc(9 * sizeof(int));

    printf("A\n");
    populateWingAttributes(&(wings[0]), id++);
    printf("B\n");
    populateWingAttributes(&wings[1], id);
    
    return wings;
}

void createPlanes(struct Plane* planes, char* id, int nPlanes) {
    int idInt = sscanf(id, "%d", &idInt);
    // int wheelsId;
    // long wingsId;
    for(int i = 0; i < nPlanes; i++) {
        planes[i].isAvailable = true;

        //sscanf(id[i], "%d", &wheelsId);
        planes[i].wheels = createWheels(idInt);

        //sscanf(id[i], "%ld", &wingsId);
        planes[i].wings = createWings((long)idInt++);
    }
}

void setAvailability(struct Plane* plane, bool isAvailable ){
    plane->isAvailable = isAvailable;
}

char** getAvailablePlanes(struct Plane** planes, int nPlanes){
    char** id = malloc(nPlanes*sizeof(char*));
    int j = 0;
    for (int i = 0; i < nPlanes; i++){
        if(planes[i]->isAvailable) {
            id[j++] = planes[i]->id;
        }    
    }
    return id;
}

void setPlaneType(struct Plane* plane){
    struct Wing firstWing = plane->wings[0];

    int identifier = 0;
    for(int i = 8; i >=0; i--) {
        identifier += firstWing.id[i];
        identifier *= 10;
    }
    
    identifier %= 9;

    char* size;

    if(identifier >= 0 && identifier <= 2) {
        size = "Small\0";
    } else if (identifier >= 3 && identifier <= 6) {
        size = "Medium\0";
    } else if (identifier == 7 || identifier == 8) {
        size = "Large\0";
    }

    int index = 0;
    while(size[index] != '\0') {
        plane->planeType[index] = size[index];
    }

    printf("%s", size);    
}

struct Plane* getPlanesByType(struct Plane** planes, char* type, int nPlanes) {
    struct Plane* typePlanes = malloc(nPlanes*sizeof(struct Plane));
    int j = 0;
    for (int i = 0; i < nPlanes; i++){
        if(strcmp(type, planes[i]->planeType)) {
            typePlanes[j++] = *planes[i];
        }    
    }
    return typePlanes;
}

int main(int argc, char** argv) {
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */

    struct Wheel* wheels = createWheels(id);
    printf("1\n");

    /* Create wing - [4 points] */

    long longId = 1;
    struct Wing* wings = createWings(longId);
    printf("2\n");


    /* Create plane - [4 points] */

    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    char planesId[] = "304321684";
    // createPlanes(planes, *id, 3);
    createPlanes(planes, planesId, 3);
    printf("3\n");

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(&plane, true);
    printf("4\n");
    

    /* Get available planes - [1 point] */
    getAvailablePlanes(&planes, numberOfPlanes);
    printf("5\n");
    

    /* Classify planes - [2 points] */
    
    plane = planes[1];
    setPlaneType(&plane);
    printf("6\n");
    

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Small";
    getPlanesByType(&planes, planeType,numberOfPlanes);
    printf("7\n");
}
