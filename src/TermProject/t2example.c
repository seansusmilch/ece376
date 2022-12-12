// Global Variables
const unsigned int A4 = 236;
const unsigned int B4 = 210;
const unsigned int C5 = 198;

const unsigned char MSG0[20] = "T2 Piano            ";
const unsigned char MSG1[20] = "PR2 =               ";


// Subroutine Declarations
#include <pic18.h>
#include "lcd_portd.c"

void interrupt IntServe(void) 
{
 if (TMR2IF) {
    if(PORTB) RA1 = !RA1;
    else RA1 = 0;
    TMR2IF = 0;
    }
 }

void Play(unsigned char NOTE)
{
 PR2 = NOTE;
 TMR2ON = 1;
 Wait_ms(450);
 TMR2ON = 0;
 Wait_ms(50);
 }

// Main Routine
void main(void)
{
 unsigned char i, j;
 TRISA = 0;
 TRISB = 0xFF;
 TRISC = 0;
 TRISD = 0;
 TRISE = 0;
 ADCON1 = 15;

// Timer2 Initialize
 TMR2ON = 1;
 TMR2IE = 1;
 PEIE = 1;
 T2CON = 0x5D; // A=12, C=4 0 1011 1 01
 PR2 = 49;
 GIE = 1;

 LCD_Init();
 LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]); 
 LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]); 

 
 while(1) {
    // if (RB0) PR2 = A4;
    // if (RB1) PR2 = B4;
    // if (RB2) PR2 = C5;
    if(RB0) Play(A4);
    if(RB1) Play(B4);
    if(RB2) Play(C5);
    LCD_Move(1,5);  LCD_Out(PR2, 3, 0);
    }; 
 }