#include "selection_mode.h"

#include <avr/io.h>
#include <util/delay.h>

class robot robotMain;

int main()
{    
    robotMain.setRed();
    selection();
    return 0;
}