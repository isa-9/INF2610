/* INF2610 - TP1
/ Matricule 1 : 2204379
/ Matricule 2 : 2212694
/ Note: Les tests que nous avons fait dans le main ont été mis en commentaire.
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
     const int N_WHEELS = 7;
     const int INDEX_REARWHEEL = 7;

    struct Wheel* wheels = malloc(N_WHEELS * sizeof(struct Wheel));
    for(int i = 0; i < N_WHEELS; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = i > INDEX_REARWHEEL;
    }
    return wheels;
}

void populateWingAttributes(struct Wing* wing, int id) {
    const int TABLE_SIZE = 9;
    const int DECIMAL_BASE = 10;

    for(int i = 0; i < TABLE_SIZE; i++) {
        wing->id[i] = id % DECIMAL_BASE;
        id /= DECIMAL_BASE;
    }
}

struct Wing* createWings(long id) {
    const int TABLE_SIZE = 9;

    struct Wing* wings = malloc(2 * sizeof(struct Wing));
    wings[0].id = malloc(TABLE_SIZE * sizeof(int));
    wings[1].id = malloc(TABLE_SIZE * sizeof(int));

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
    const int DECIMAL_BASE = 10;
    const int MODULO_DIVIDER = 9;
    const int TABLE_LENGHT = 9;
    const int MAX_SMALL = 2;
    const int MAX_MEDIUM = 6;
    


    struct Wing firstWing = plane->wings[0];

    int identifier = 0;
    for(int i = TABLE_LENGHT-1; i >=0; i--) {
        identifier *= DECIMAL_BASE;
        identifier += firstWing.id[i];
    }
    
    identifier %= MODULO_DIVIDER;

    char* size = malloc(N_CHAR_TYPE * sizeof(char));

    if(identifier <= MAX_SMALL) {
        size = "Small\0";
    } else if (identifier <= MAX_MEDIUM) {
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
        if(strcmp(type, (*planes)[i].planeType) == 0) {
            typePlanes[j++] = (*planes)[i];
        }    
    }
    return typePlanes;
}

/* TEST FUNCTIONS */
void printWheel(struct Wheel* wheel) {
    printf("Wheel\n");
    printf("\tid: %d\n", wheel->id);
    printf("\tisRearWheel: %s\n", wheel->isRearWheel ? "true" : "false");
}

void printWing(struct Wing* wing) {
    const int TABLE_ID_WING_LENGHT = 9;
    printf("Wing:\n");
    printf("\t id: [ %d", wing->id[TABLE_ID_WING_LENGHT-1]);
    for (int i = TABLE_ID_WING_LENGHT-2; i >= 0; i--) {
        printf(", %d", wing->id[i]);
    }
    printf(" ]\n");
}

void printPlane(struct Plane* plane){
    const int N_WHEELS = 7;
    const int N_WINGS = 2;

    printf("Plane %s: \n", plane->id);
    printf("\tplaneType: %s\n", plane->planeType);
    printf("\tisAvailable: %s\n", plane->isAvailable ? "true" : "false");

    for (int i = 0; i < N_WHEELS; i++){
        printWheel(&(plane->wheels[i]));
    }

    for (int i = 0; i < N_WINGS; i++){
        printWing(&(plane->wings[i]));
    }
    
}

int main(int argc, char** argv) {
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */

    struct Wheel* wheels = createWheels(id);
    // printWheel(&wheels[0]);

    /* Create wing - [4 points] */

    long longId = 1;
    struct Wing* wings = createWings(longId);
    // printWing(&wings[0]);


    /* Create plane - [4 points] */

    int numberOfPlanes = 3;
    struct Plane* planes = malloc(sizeof(struct Plane) * numberOfPlanes);
    char planesId[] = "304321684";

    createPlanes(planes, planesId, 3);

    // for (int i = 0; i < numberOfPlanes; i++) {
    //     printPlane(&planes[i]);
    // }

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane* plane = &planes[0];
    setAvailability(plane, true);
    // printPlane(&plane);

    plane = &planes[2];
    setAvailability(plane, false);
    // printPlane(&plane);
    

    /* Get available planes - [1 point] */
    // const int nAvailablePlanes = 2; // Since planes[2].isAvailable is set to false. 
    char** availablePlanes = getAvailablePlanes(&planes, numberOfPlanes);

    // for(int i = 0; i < nAvailablePlanes; i++) {
    //     printf("%s\n", availablePlanes[i]);
    // }
    

    /* Classify planes - [2 points] */
    
    plane = &planes[1];
    setPlaneType(plane);
    // printPlane(&plane);

    // for (int i = 0; i < numberOfPlanes; i++) {
    //     printPlane(&planes[i]);
    // }
    

    /* Return type specific planes - [2 points] */
    
    char planeType[] = "Medium";
    struct Plane* typePlanes = getPlanesByType(&planes, planeType, numberOfPlanes);
    // printPlane(&typePlanes[0]);
}
