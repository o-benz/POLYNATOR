#include "map.h"

map::map()
{
    // map::resetMatrix();
}

void map::removePoint(uint8_t point)
{
    for(uint8_t i = 0; i < 28; i++)
    {
        adjacencyMatrix[i][point] = 0;
        adjacencyMatrix[point][i] = 0;
    }
}