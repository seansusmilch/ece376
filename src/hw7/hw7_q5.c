const unsigned char MSG0[21] = "  D/A Converter  ";

#include <pic18.h>
#include <math.h>
#include "lcd_portd.c"

void init(void){
    ADCON1 = 0x0F;
    // Turn on the A/D input
    TRISA = 0xFF;
    TRISE = 0x0F;
    ADCON2 = 0x95;
    ADCON1 = 0x07;
    ADCON0 = 0x01;

    LCD_Init();
    LCD_Move(0,0); for(int i=0; i < 20; i++) LCD_Write(MSG0[i]);
    Wait_ms(100);
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

    SCI_CRLF();
}

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

void main(void){
    init();

    int X, Y;

    LCD_Move(0,0); LCD_Write("X");
    LCD_Move(1,0); LCD_Write("Y");

    while(1){
        while(!RB0){
            X = A2D_Read(0);
            LCD_Move(0,1); LCD_Out(X, 4, 0);
        }

        Y = pow(X, 0.5);
        LCD_Move(1,1); LCD_Out(Y, 4, 0);

        while(RB0);
    }
}