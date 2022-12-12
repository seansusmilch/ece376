// Timer1 Compare.C
//
// Output a square wave with a frequency of 349.23Hz
// on RC0 using Timer1 Compare interrupts

#include <pic18.h>

// Global Variables
unsigned long int TIME;

const unsigned char MSG0[21] = "T1 Compare          "; 


// Interrupt Service Routine

void interrupt IntServe(void) 
{
   if (TMR1IF) {
      TIME = TIME + 0x10000;
      TMR1IF = 0;
      }   
   if (CCP1IF) {
      RC0 = !RC0;
      CCPR1 += 14317;
      CCP1IF = 0;
      }   
   }

// Subroutines
#include        "lcd_portd.c"



// Main Routine

void main(void)
{
   unsigned char i;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0x04;	// capture every rising edge
   TRISD = 0;
   ADCON1 = 0x0F;
  
   LCD_Init();                  // initialize the LCD
   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
 
   TIME = 0;


// set up Timer1 for PS = 1
   TMR1CS = 0;
   T1CON = 0x81;
   TMR1ON = 1;
   TMR1IE = 1;
   TMR1IP = 1;
   PEIE = 1;
// set up Compare for no change
   CCP1CON = 0x0A;
   CCP1IE = 1;
   PEIE = 1;


// turn on all interrupts
   GIE = 1;
   
   while(1) {
      LCD_Move(1,0);  LCD_Out(TIME + TMR1, 10, 7);
      }
   }