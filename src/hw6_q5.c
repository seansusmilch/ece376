// Global Variables
const unsigned char MSG0[21] = "-Sided Die      "; 
// Subroutines
#include <pic18.h>
#include "lcd_portd.c"

unsigned int A2D_Read(unsigned char c)
{
   unsigned int result;
   unsigned char i;
   c = c & 0x0F;
   ADCON0 = (c << 2) + 0x01; // set Channel Select
   for (i=0; i<10; i++); // wait 2.4us (approx)
   GODONE = 1; // start the A/D conversion
   while(GODONE); // wait until complete (approx 8us)
   return(ADRES);
}

// Main Routine
void main(void)
{
    unsigned int i, DIE, X, N;
    int A2D;
    ADCON1 = 0x0F;
    // Turn on the A/D input
    TRISA = 0xFF;
    TRISE = 0x0F;
    ADCON2 = 0x95;
    ADCON1 = 0x07;
    ADCON0 = 0x01;

    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    LCD_Init(); 
    // LCD_Move(0,0); for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    Wait_ms(500);
    // Initialize Serial Port to 9600 baud
    // TRISC = TRISC | 0xC0;
    // TXIE = 0;
    // RCIE = 0;
    // BRGH = 0;
    // BRG16 = 1;
    // SYNC = 0;
    // SPBRG = 255;
    // TXSTA = 0x22;
    // RCSTA = 0x90;
    while(1) {
        while(!RB0){
            A2D = A2D_Read(0);
            N = (A2D / 52) + 1;
            LCD_Move(0,0); LCD_Out(N, 2, 0);
            for (i=0; i<20; i++) LCD_Write(MSG0[i]);
        }
        while(RB0) { 
            DIE = (DIE + 1) % N;
        } 
        DIE = DIE + 1;
        LCD_Move(1,0); LCD_Out(DIE, 2, 0);
        // SCI_Out(DIE, 1, 0);
        // SCI_CRLF();
    }
}