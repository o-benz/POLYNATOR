#include "exec.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"
#define DEMO_DDR DDRC
#define DEMO_PORT PORTC
#define MAX_VERTICES 28

// starting from leftmost to the right. 
uint8_t minDistance(uint8_t distance[], bool emptySet[]){
    uint8_t placeholder = 255; 
    uint8_t min = placeholder;
    uint8_t min_index =-1;
    
    //empty set for the shortest path tree
    //checks if the distance value of the vertex is equal to the current minimum distance.
    for(uint8_t i = 0; i< 28; i++){ //iterate through the vertices //chiffre magic 
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
            if (!emptySet[v] && robotExec.mapExec.adjacencyMatrix[u][v] && distance[u] != placeholder &&
                distance[u] + robotExec.mapExec.adjacencyMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + robotExec.mapExec.adjacencyMatrix[u][v];
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