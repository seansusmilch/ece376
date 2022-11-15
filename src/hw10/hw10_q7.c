/**
 * @file hw10_q7.c
 * @brief Generate frequencies from 100Hz to 999Hz
based on keypad input
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <pic18.h>
// Global Variables
unsigned long int INCREMENT;
const unsigned char MSG0[21] = "Freq Generator       "; 
const unsigned char MSG1[21] = "                     "; 

// Interrupt Service Routine

void interrupt IntServe(void) 
{
    if (TMR1IF) {
        TIME = TIME + 0x10000;
        TMR1IF = 0;
    }
    if (CCP1IF) {
        RB0 = !RB0;
        CCPR1 += INCREMENT;
        CCP1IF = 0;
    }
   }

// Subroutines
#include "lcd_portd.c"
#include "keypad.c"



// Main Routine

void main(void)
{
    unsigned int i;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0x04;	// capture every rising edge
    TRISD = 0;
    ADCON1 = 0x0F;

    // set up Timer1 for PS = 1
    TMR1CS = 0;
    T1CON = 0x81;
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IP = 1;
    PEIE = 1;
    // set up Capture1 for rising edges
    //    TRISC2 = 1;
    CCP1CON = 0x0A;
    CCP1IE = 1;
    PEIE = 1;

    LCD_Init();           
    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    Wait_ms(1000);
    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

    TIME = 0;

    // turn on all interrupts
    GIE = 1;
    
    int frequency = 500, TEMP, entry = 0;
    
    while(1) {
        INCREMENT = 10000000/(2*frequency);
        LCD_Move(0,0);  LCD_Out(frequency, 3, 0);

        TEMP = ReadKey();

        if (TEMP < 10) entry = (entry*10) + TEMP;

        if (TEMP == 10) {
            if(entry <= 999 && entry >= 100)
                frequency = entry;
            entry = 0;

        }
        if (TEMP == 11) entry = entry/10;

        LCD_Move(1,0);  LCD_Out(entry, 3, 0);
    }
}