// GLOBALS
const unsigned char AMSG[3] = "A ";
const unsigned char BMSG[3] = "B ";
const unsigned char CMSG[3] = "C ";
const unsigned char DMSG[3] = "D ";
unsigned short A, B, C, D;

#include <pic18.h>
// Subroutines
#include "lcd_portd.c"

void init(void){
    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;

    LCD_Init();                  // initialize the LCD
    LCD_Move(0,0);
}

void writeScores(void){
    unsigned char i;

    LCD_Move(0,0);
    for(i=0; i<2; i++)
        LCD_Write(AMSG[i]);
    LCD_Move(0,1);
    LCD_Out(A, 5, 0);

    LCD_Move(0,8);
    for(i=0; i<2; i++)
        LCD_Write(BMSG[i]);
    LCD_Move(0,9);
    LCD_Out(B, 5, 0);

    LCD_Move(1,0);
    for(i=0; i<2; i++)
        LCD_Write(CMSG[i]);
    LCD_Move(1,1);
    LCD_Out(C, 5, 0);

    LCD_Move(1,8);
    for(i=0; i<2; i++)
        LCD_Write(DMSG[i]);
    LCD_Move(1,9);
    LCD_Out(D, 5, 0);
}

void main(void){
    init();
    unsigned int i, j;
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    
    Wait_ms(500);

    while(1) {
        if(RB3 == 1){
            while(RB3 == 1){}
            A = A + 1;
        }
        if(RB2 == 1){
            while(RB2 == 1){}
            B = B + 1;
        }
        if(RB1 == 1){
            while(RB1 == 1){}
            C = C + 1;
        }
        if(RB0 == 1){
            while(RB0 == 1){}
            D = D + 1;
        }

        if(RB7 == 1){
            A = 0;
            B = 0;
            C = 0;
            D = 0;
        }

        writeScores();
        Wait_ms(50);        // Wait 100ms (approx)

    }
}