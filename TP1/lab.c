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
    for(int i = 0; i < 9; i++) {
        wing->id[i] = id % 10;
        id /= 10;
    }
}

struct Wing* createWings(long id) {
    struct Wing* wings = malloc(2 * sizeof(struct Wing));
    populateWingAttributes(&wings[0], id++);
    populateWingAttributes(&wings[1], id);
    return wings;
}

void createPlanes(struct Plane* planes, char** id, int nPlanes) {
    int wheelsId;
    long wingsId;
    for(int i = 0; i < nPlanes; i++) {
        planes[i].isAvailable = true;

        sscanf(id[i], "%d", &wheelsId);
        planes[i].wheels = createWheels(wheelsId);

        sscanf(id[i], "%ld", &wingsId);
        planes[i].wings = createWings(wingsId);
    }
}


int main(int argc, char** argv) {
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */

    struct Wheel* wheels = createWheels(id);


    /* Create wing - [4 points] */

    long longId = 1;
    struct Wing* wings = createWings(longId);


    /* Create plane - [4 points] */

    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    char* planesId[] = { "1000", "304321684", "202020202020"};
    // createPlanes(planes, *id, 3);
    createPlanes(planes, planesId, 3);

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    /*
    Plane plane = planes[0];
    setAvailability(plane, true);
    */

    /* Get available planes - [1 point] */
    /*
    getAvailablePlanes(planes, numberOfPlanes);
    */

    /* Classify planes - [2 points] */
    /*
    Plane plane = planes[1];
    setPlaneType(plane);
    */

    /* Return type specific planes - [2 points] */
    /*
    char planeType[] = "Small";
    getPlanesByType(planes, planeType,numberOfPlanes);
    */
}
