#include "robot.h"
#include "drive.h"
#include "orientation.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"

#define DEMO_DDR DDRC
#define DEMO_PORT PORTC
#define MAX_VERTICES 28; 

uint8_t adjacencyMatrix[28][28] = {
           //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
            {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
            {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //5
            {0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //6
            {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //7
            {1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
            {0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
            {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //10
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //11
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //12
            {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //13
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //14
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0}, //15
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //16
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //17
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //18
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0}, //19
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //20
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //21
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //22
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, //23
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //24
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0}, //25
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 2, 0, 5, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 5, 0, 1}, //27
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };

// starting from leftmost to the right. 

uint8_t minDistance(uint8_t distance[], bool emptySet[]){

    uint8_t placeholder = 255; 
    uint8_t min = placeholder;
    uint8_t min_index =-1;
    
    //empty set for the shortest path tree
    //checks if the distance value of the vertex is equal to the current minimum distance. 

    for(uint8_t i = 0; i< MAX_VERTICES; i++){ //iterate through the vertices 
        if(!emptySet[i] && distance[i] <= min){
            min = distance[i];
            min_index = i;
        }
    }
    return min_index; // the index of the min distance vertex 
}

uint8_t* shortestPath(uint8_t startPoint, uint8_t targetPoint) { 
    uint8_t placeholder = 255;
    bool emptySet[MAX_VERTICES] = {false};
    static uint8_t distance[MAX_VERTICES];

    for (uint8_t i = 0; i < MAX_VERTICES; i++) {
        distance[i] = placeholder;
    }

    distance[startPoint] = 0;

    uint8_t previous[MAX_VERTICES] = {0};

    for (uint8_t count = 0; count < MAX_VERTICES - 1; count++) {
        uint8_t u = minDistance(distance, emptySet);
        emptySet[u] = true;

        for (uint8_t v = 0; v < MAX_VERTICES; v++) {
            if (!emptySet[v] && adjacencyMatrix[u][v] && distance[u] != placeholder &&
                distance[u] + adjacencyMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adjacencyMatrix[u][v];
                previous[v] = u;
            }
        }
    }

    uint8_t path[MAX_VERTICES];
    uint8_t pathLength = 0;
    uint8_t current = targetPoint;

    while (current != startPoint) {
        path[pathLength++] = current;
        current = previous[current];
    }

    path[pathLength++] = startPoint;

    static uint8_t reversedPath[MAX_VERTICES];
    for (uint8_t i = 0; i < pathLength; i++) {
        reversedPath[i] = path[pathLength - i - 1];
    }

    return reversedPath;
}