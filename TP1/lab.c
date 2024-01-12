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
    for(int i = 0; i < 9; i++) {
        wing->id[i] = id % 10;
        id /= 10;
    }
}

struct Wing* createWings(long id) {
    struct Wing* wings = malloc(2 * sizeof(struct Wing));
    wings[0].id = malloc(9 * sizeof(int));
    wings[1].id = malloc(9 * sizeof(int));

    populateWingAttributes(&(wings[0]), id++);
    populateWingAttributes(&wings[1], id);

    return wings;
}

void createPlanes(struct Plane* planes, char* id, int nPlanes) {
    int idInt;
    sscanf(id, "%d", &idInt);

    for(int i = 0; i < nPlanes; i++) {
        planes[i].id = malloc(sizeof(id));
        sprintf(planes[i].id, "%d", idInt);

        planes[i].id = malloc(10 * sizeof(char));

        planes[i].isAvailable = true;

        planes[i].wheels = createWheels(idInt);

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
        if((*planes)[i].isAvailable) {
            id[j] = malloc(sizeof((*planes)[i].id));
            id[j++] = (*planes)[i].id;
        }
    }
    return id;
}

void setPlaneType(struct Plane* plane){
    const int N_CHAR_TYPE = 10;

    struct Wing firstWing = plane->wings[0];

    int identifier = 0;
    for(int i = 8; i >=0; i--) {
        identifier *= 10;
        identifier += firstWing.id[i];
    }
    
    identifier %= 9;

    char* size = malloc(N_CHAR_TYPE * sizeof(char));

    if(identifier <= 2) {
        size = "Small\0";
    } else if (identifier <= 6) {
        size = "Medium\0";
    } else {
        size = "Large\0";
    }

    int index = 0;
    while(size[index] != '\0') {
        plane->planeType[index] = size[index];
        index++;
    }

    printf("%s\n", size);    
}

struct Plane* getPlanesByType(struct Plane** planes, char* type, int nPlanes) {
    struct Plane* typePlanes = malloc(nPlanes*sizeof(struct Plane));
    int j = 0;
    for (int i = 0; i < nPlanes; i++){
        if(strcmp(type, (*planes)[i].planeType)) {
            typePlanes[j++] = (*planes)[i];
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

    /* Create wing - [4 points] */

    long longId = 1;
    struct Wing* wings = createWings(longId);


    /* Create plane - [4 points] */

    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    char planesId[] = "304321684";
    // createPlanes(planes, *id, 3);
    createPlanes(planes, planesId, 3);

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane plane = planes[0];
    setAvailability(&plane, true);
    

    /* Get available planes - [1 point] */
    getAvailablePlanes(&planes, numberOfPlanes);
    

    /* Classify planes - [2 points] */
    
    plane = planes[1];
    setPlaneType(&plane);
    

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Small";
    getPlanesByType(&planes, planeType,numberOfPlanes);
}
