#define DELAY_BUTTON 30

#include <stdlib.h>

#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include "lcm_so1602dtr_m_fw.h"
#include "travel.h"


#define DEMO_DDR   DDRC
#define DEMO_PORT    PORTC   

#define COLUMNS 7
#define ROWS 4

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

void static inline w(void)
{
    cp_wait_ms(150);
}

volatile uint8_t curPoint = 0;

void path_travel()
{
    robotExec.setDark();
    LCM disp(&DEMO_DDR, &DEMO_PORT); 
    
    bool no = false;
    bool yes = false;  
    gIsSelectionPressed= false;

    static uint8_t row = 1; 
    static uint8_t column = 1;
    bool rowSelection = true;

    while(true)
    { 
        while(rowSelection)
        {
            disp.write("LIGNE",0); 
            w();

            switch (row) 
            {
            case 1 :
                disp.write("1", 16);
                w();

                if (gIsSelectionPressed) 
                {
                    row++;
                    gIsSelectionPressed= false;
                }
                break;

            case 2:
                disp.write("2", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    row++;
                    gIsSelectionPressed= false;
                }
                break;

            case 3:
                disp.write("3", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    row++;
                    gIsSelectionPressed= false;
                }
                break;

            case 4:
                disp.write("4", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    row++;
                    gIsSelectionPressed= false;
                }
                break;

            case 5:
                row = 1; 
                break;
            }

            if(gIsValidationPressed)
            {
                rowSelection = false;
            }
            
        }
            
        bool columnSelection = false;
        if(gIsValidationPressed)
        {
            rowSelection = false; 
            disp.clear();

            columnSelection = true;
            gIsValidationPressed = false;
        }

        while (columnSelection) 
        {  
            disp.write("COLONNE",0); 
            w();

        switch (column) 
        {
            case 1:
                disp.write("1", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 2:
                disp.write("2", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 3:
                disp.write("3", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 4:
                disp.write("4", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 5:
                disp.write("5", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 6:
                disp.write("6", 16);
                w();
                if (gIsSelectionPressed) 
                {
                    column++;
                    gIsSelectionPressed= false;
                }
                break;

            case 7:
                disp.write("7", 16);
                w();
                if (gIsSelectionPressed)
                {
                    column ++;
                    gIsSelectionPressed= false;
                }
                break;
            
            case 8:
                column = 1; 
                break;
            }

            if(gIsValidationPressed)
            {
                columnSelection = false;
            }
        }
        
        if(gIsValidationPressed )
        {
                columnSelection = false;
                disp.clear();
                uint8_t i = row;
                uint8_t j  = column; 
                
                char row[2];
                char column[2];
                itoa(i,row, 10);
                itoa(j,column,10);

                disp.write("(L: " + row + ",C: " + column + ")" + "OK ? ", 0);
                w();
                // disp.write(row, 4);
                // w();
                // disp.write(",C: ", 6);
                // w();
                // disp.write(column,9); 
                // w();
                // disp.write(")", 10);
                // w();
                // disp.write("OK ? ", 12);
                // w();
                gIsValidationPressed = false;
                no = true;
            }

        if(no)
        {
            disp.write("NON", 16);
            w();

            if(gIsValidationPressed)
            {
                disp.clear();
                gIsValidationPressed = false;
                rowSelection = true; 
                no = false;
                row = 1;
                column = 1; 
            }
            
            else if(gIsSelectionPressed) 
            {
                gIsSelectionPressed = false; 
                yes = true; 
                no = false;
            }
        }

        if(yes){
            disp.write("OUI", 16);
            w();

            if(gIsValidationPressed)
            {

                yes = false;
                gIsValidationPressed = false;
                disp.clear();

                // CODE DRIVE
                _delay_ms(500);
                curPoint = doTravel(row, column, curPoint);
                robotExec.resetMap(); // si on veut pas se rappeler des poteaux
                path_travel();
            }
            else if(gIsSelectionPressed && !no) 
            {
                gIsSelectionPressed = false; 
                no = true; 
                yes= false;
            }
        }
    }
}