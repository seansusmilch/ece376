// ---  1234.C -------------------
// Write the numbers 1,2,3,4 to
// PORTA / B / C / D

// Global Variables

// Subroutine Declarations
#include <pic18.h>

   
// Main Routine



void main(void)
{

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;
    
   PORTA = 1;
   PORTB = 2;
   PORTC = 3;
   PORTD = 4;

   while(1);

   }