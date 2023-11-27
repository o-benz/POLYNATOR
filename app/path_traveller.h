#define DELAY_BUTTON 30

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "robot.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"


#define DEMO_DDR   DDRC
#define DEMO_PORT    PORTC   

#define COLUMNS 7
#define ROWS 4

class robot robotTravel;

volatile bool gIsSelectionPressed = false;
volatile bool gIsValidationPressed = false;

ISR(INT2_vect) 
{
    _delay_ms(BUTTON_DEBOUNCE_DELAY);
    gIsSelectionPressed = true;
    EIFR |= (1 << INTF2);
}

ISR(INT1_vect) 
{
    _delay_ms(BUTTON_DEBOUNCE_DELAY);
    gIsValidationPressed = true;
    EIFR |= (1 << INTF1);
}

void static inline w(void){
    cp_wait_ms(150);
}

//robot robotTravel;


void path_travel()
{
    // Switch case here is better: 

    robotTravel.setDark();
    LCM disp(&DEMO_DDR, &DEMO_PORT); 
    
    //if(gIsSelectionPressed){
    //i++;}
    bool start = true;
    bool no = false;
    bool yes = false;  
    gIsSelectionPressed= false;

    static uint8_t row = 1; 
    static uint8_t column = 1;
    bool linePicking = true;

    //i++;
    while(true){ 
        while(linePicking){
            disp.write("LIGNE",0); 
            w();
        switch (row) {
        case 1 :
            disp.write("1", 16);
            w();

            if (gIsSelectionPressed) {
                row++;
                gIsSelectionPressed= false;
            }
            break;

        case 2:
            disp.write("2", 16);
            w();
            if (gIsSelectionPressed) {
                row++;
                gIsSelectionPressed= false;
            }
            break;

        case 3:
            disp.write("3", 16);
            w();
            if (gIsSelectionPressed) {
                //row[2];
                //itoa(row,row, 10);
                row++;
                gIsSelectionPressed= false;
            }
            break;

        case 4:
            disp.write("4", 16);
            w();
            if (gIsSelectionPressed) {
                row++;
                gIsSelectionPressed= false;
            }
            break;

        case 5:
            row = 1; 
            break;
        }

        if(gIsValidationPressed){
            linePicking = false;
        }
        
        }
        
        bool columnsPicking = false;
        if(gIsValidationPressed){
            linePicking = false; 
            //uint8_t i  = row;  // this is the row to travel to 
            // char row[2]; // will need to redo the same thing for the switch case
             //rowToGoTo = row; 
            //itoa(i,row, 10); // 10 is for decimal 
            //disp.write(row, 16);
            //w();
            disp.clear();
            columnsPicking = true;
            //gIsSelectionPressed = true;
            gIsValidationPressed = false;
            
        }

    while (columnsPicking) {  
        //disp.clear();
        disp.write("COLONNE",0); 
        w();

    switch (column) {
        case 1:
            disp.write("1", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 2:
            disp.write("2", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 3:
            disp.write("3", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 4:
            disp.write("4", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 5:
            disp.write("5", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 6:
            disp.write("6", 16);
            w();
            if (gIsSelectionPressed) {
                column++;
                gIsSelectionPressed= false;
            }
            break;

        case 7:
            disp.write("7", 16);
            w();
            if (gIsSelectionPressed){
                column ++;
                gIsSelectionPressed= false;
            }
            break;
        
        case 8:
            column = 1; 
            break;
    }

        if(gIsValidationPressed){
            columnsPicking = false;
        }
    }
    
    if(gIsValidationPressed ){
            columnsPicking = false;
            disp.clear();
            uint8_t i = row;
            uint8_t j  = column; 
            char row[2];
            char column[2];
            itoa(i,row, 10);
            itoa(j,column,10);

            disp.write("(L: ", 0);
            w();
            disp.write(row, 4);
            w();
            disp.write(",C: ", 6);
            w();
            disp.write(column,9); 
            w();
            disp.write(")", 10);
            w();
            disp.write("OK ? ", 12);
            w();
            gIsValidationPressed = false;
            no = true;
        }

    if(no){
        disp.write("NON", 16);
        w();

        if(gIsValidationPressed){
            disp.clear();
            gIsValidationPressed = false;
            linePicking = true; 
            no = false;
            row = 1;
            column = 1; 
        }
        
        else if(gIsSelectionPressed) {
            gIsSelectionPressed = false; 
            yes = true; 
            no = false;
    }
    }

    if(yes){
        disp.write("OUI", 16);
        w();

        if(gIsValidationPressed){
            disp.write("start the trajet");
            w(); 
            yes = false;
            gIsValidationPressed = false;

        }
        else if(gIsSelectionPressed && !no) {
            gIsSelectionPressed = false; 
            no = true; 
            yes= false;
        }
    }
    }
}



    // if(gIsSelectionPressed && no){
    //     disp.write("NON", 16);
    //     w();
    //     if(gIsValidationPressed){
    //         //row=0;
    //         //column =0; 
    //     }
    // }
            
    // }
    // }
    // if(gIsSelectionPressed && yes ){
    //     disp.write("OUI", 16);
    //     w();

    //     //no = true;
    //     if(gIsValidationPressed){
    //         disp.write(" !", 16); 
    //         w();
    //     }
    // }
    