// Identifier le coin 
// Array (column, row)
#include <avr/io.h>
#include <util/delay.h>

enum class colour { yellow, red, black};
enum class orientation {north, south, east, west};

struct coords {
    uint8_t x;
    uint8_t y;
};

struct Node {
    coords position;
    orientation direction;
};

struct line {
    coords startingCoord;
    coords finishingCoord; 
    colour colourPicked;
};


// the map 
line mapArray[35] = {{{1,1}, {2,1}, colour::black},
                    {{1,1}, {1,2}, colour::black}, 
                    {{2,1}, {3,1}, colour::black}, 
                    {{3,1}, {4,1}, colour::black}, 
                    {{5,1}, {6,1}, colour::black}, 
                    {{6,1}, {7,1}, colour::yellow}, 
                    {{1,3}, {1,4}, colour::red}, 
                    {{1,2}, {2,2}, colour::red}, 
                    {{2,2}, {3,2}, colour::black}, 
                    {{4,2}, {5,2}, colour::yellow}, 
                    {{5,2}, {6,2}, colour::black}, 
                    {{6,2}, {7,2}, colour::black}, 
                    {{2,2}, {2,3}, colour::black},
                    {{1,3}, {2,3}, colour::yellow},
                    {{2,3}, {3,3}, colour::black},
                    {{3,3}, {4,3}, colour::black},
                    {{4,3}, {5,3}, colour::red},
                    {{3,1}, {3,2}, colour::black}, 
                    {{3,2}, {3,3}, colour::red}, 
                    {{3,3}, {3,4}, colour::black}, 
                    {{4,1}, {4,2}, colour::black}, 
                    {{4,3}, {4,4}, colour::black}, 
                    {{5,2}, {5,3}, colour::red}, 
                    {{5,3}, {5,4}, colour::red}, 
                    {{6,1}, {6,2}, colour::yellow}, 
                    {{6,2}, {6,3}, colour::black}, 
                    {{6,3}, {6,4}, colour::black},
                    {{7,1}, {7,2}, colour::black}, 
                    {{7,2}, {7,3}, colour::black}, 
                    {{7,3}, {7,4}, colour::black}, 
                    {{1,4}, {2,4}, colour::black}, 
                    {{2,4}, {3,4}, colour::black}, 
                    {{4,4}, {5,4}, colour::yellow},
                    {{5,4}, {6,4}, colour::red}, 
                    {{6,4}, {7,4}, colour::black}
};