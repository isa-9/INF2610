/* INF2610 - TP1
/ Matricule 1 : 2204379
/ Matricule 2 : 2212694
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 

struct Wheel {
    int id;
    bool isRearWheel;
};

struct Wing {
    int id[];
}

struct Plane {
    char id[];
    char planeType[10];
    bool isAvailable;
    Wheel wheels[];
    Wing wings[];
};


int main(int argc, char** argv) {
    printf("Hello\n");
    /* Remove comment once the code is completed for the given section to test */
    int id = 1;


    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    /*
    Wheel[] wheels;
    wheels = createWheels(id);    
    */

    /* Create wing - [4 points] */
    /*
    long longId = 1;
    Wing[] wings;
    wings = createWings(longId);
    */

    /* Create plane - [4 points] */
    /*
    int numberOfPlanes = 3;
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, *id, 3);
    */

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
