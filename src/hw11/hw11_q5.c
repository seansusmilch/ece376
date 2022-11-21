const unsigned char MSG0[21] = "Z Transform      "; 
const unsigned char MSG1[21] = "                 "; 

#include <pic18.h>
#include "lcd_portd.c"

unsigned int A2D_Read(unsigned char c){
    unsigned int result;
    unsigned char i;
    c = c & 0x0F;
    ADCON0 = (c << 2) + 0x01; // set Channel Select
    for (i=0; i<20; i++); // wait 2.4us (approx)
    GODONE = 1; // start the A/D conversion
    while(GODONE); // wait until complete (approx 8us)
    return(ADRES);
}

void D2A(unsigned int X){
    unsigned char i;
    TRISC0 = 0;
    TRISC3 = 0;
    TRISC5 = 0;

    // Add 0011 to the first four bits to set up the D/A
    X = X & 0x0FFF;
    X = X + 0x3000;
    RC0 = 1;
    RC3 = 1;

    // CS goes low to select the D/A chip
    RC0 = 0;

    // Send out 16 bits of data
    for (i=0; i<16; i++) {
        if (X & 0x8000) RC5 = 1; else RC5 = 0;
        RC3 = 0;
        X = X << 1;
        RC3 = 1;
    }

    // CS goes high to terminate the communicaitons
    RC0 = 1;
}

void main(){
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;

    LCD_Init();
    LCD_Move(0,0);  for (int i=0; i<20; i++) LCD_Write(MSG0[i]); 
    LCD_Move(1,0);  for (int i=0; i<20; i++) LCD_Write(MSG1[i]); 

    unsigned int x0,x1,x2,y0,y1,y2;

    while(1) {
        x2 = x1;
        x1 = x0;
        x0 = A2D_Read(0);
        y2 = y1;
        y1 = y0;
        y0 = 1.9406*y1 - 0.9802*y2 + 0.0099*(x1 - x2);
        D2A(y0);
        Wait_ms(10);
    }
}