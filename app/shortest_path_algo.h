#include "exec.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"

#define DEMO_DDR DDRC
#define DEMO_PORT PORTC
#define MAX_VERTICES 28
#define PLACE_HOLDER 255 
#define INDEX_INIT_VALUE -1 

/**
 * @brief Implements Dijkstra's algorithm to calculate the shortest distance between vertices in a graph, specifically for the given map.
 * 
 * In the adjacency matrix in the library, each point on the map is represented as an integer value. The mapping starts with the top-left point
 * (Row: 1, Column: 1) represented as 1, and the mapping proceeds row-wise. For example, (Row: 1, Column: 2) is 2, (Row: 1, Column: 3) is 3, 
 * and so on. The last point (Row: 4, Column: 7) represents the integer 28.
 * 
 * This algorithm initializes with a start vertex, calculates the shortest paths to all other vertices, 
 * and constructs the shortest path tree. The result is a static array representing the shortest path from 
 * a given start point to a target point.
 */
 

uint8_t minimumDistanceBetweenEachVertex(uint8_t distance[], bool emptySet[])
{
    uint8_t min = PLACE_HOLDER;
    uint8_t min_index = INDEX_INIT_VALUE;

    for(uint8_t i = 0; i< MAX_VERTICES; i++)
    { 
        if(!emptySet[i] && distance[i] <= min)
        {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index; 
}

uint8_t* shortestPath(uint8_t startPoint, uint8_t targetPoint) 
{ 
    bool emptySet[MAX_VERTICES] = {false};
    static uint8_t distance[MAX_VERTICES];
    for (uint8_t i = 0; i < MAX_VERTICES; i++) 
    {
        distance[i] = PLACE_HOLDER;
    }

    distance[startPoint] = 0;
    uint8_t previous[MAX_VERTICES] = {0};
    for (uint8_t count = 0; count < MAX_VERTICES - 1; count++) 
    {
        uint8_t u = minimumDistanceBetweenEachVertex(distance, emptySet);
        emptySet[u] = true;
        for (uint8_t v = 0; v < MAX_VERTICES; v++) 
        {
            if (!emptySet[v] && robotExec.mapExec.adjacencyMatrix[u][v] && distance[u] != PLACE_HOLDER &&
                distance[u] + robotExec.mapExec.adjacencyMatrix[u][v] < distance[v]) 
            {
                distance[v] = distance[u] + robotExec.mapExec.adjacencyMatrix[u][v];
                previous[v] = u;
            }
        }
    }
    uint8_t path[MAX_VERTICES];
    uint8_t pathLength = 0;
    uint8_t current = targetPoint;
    while (current != startPoint) 
    {
        path[pathLength++] = current;
        current = previous[current];
    }

    path[pathLength++] = startPoint;
    static uint8_t reversedPath[MAX_VERTICES];
    for (uint8_t i = 0; i < pathLength; i++) 
    {
        reversedPath[i] = path[pathLength - i - 1];
    }
    return reversedPath;
}