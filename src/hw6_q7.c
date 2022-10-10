// Global Variables
const unsigned char MSG0[21] = "Electronic Dice "; 
// Subroutines
#include <pic18.h>
#include "lcd_portd.c"
 
// Main Routine
void main(void)
{
    unsigned int i, DIE, X;
    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;
    LCD_Init(); 
    LCD_Move(0,0); for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    Wait_ms(500);
    // Initialize Serial Port to 9600 baud
    TRISC = TRISC | 0xC0;
    TXIE = 0;
    RCIE = 0;
    BRGH = 0;
    BRG16 = 1;
    SYNC = 0;
    SPBRG = 255;
    TXSTA = 0x22;
    RCSTA = 0x90;
    while(1) {
        while(!RB0);
        while(RB0) { 
            DIE = (DIE + 1) % 6;
            X = (X + 1) % 101;
        } 
        DIE = DIE + 1;
        if(X < 10) DIE = 6;
        LCD_Move(1,0); LCD_Out(DIE, 1, 0);
        SCI_Out(DIE, 1, 0);
        SCI_CRLF();
    }
}