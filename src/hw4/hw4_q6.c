// GLOBALS
const unsigned char UNLOCKED_MSG[17] = "    UNLOCKED    ";
const unsigned char LOCKED_MSG[17] = "     LOCKED     ";

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

void write_unlocked(void){
    unsigned char i;
    LCD_Move(0,0);
    for(i=0; i<17; i++)
        LCD_Write(UNLOCKED_MSG[i]);
}

void write_locked(void){
    unsigned char i;
    LCD_Move(0,0);
    for(i=0; i<17; i++)
        LCD_Write(LOCKED_MSG[i]);
}

int look_for(unsigned char x){
    while(PORTB == x);
    if(PORTB == 0)
        return 1;
    return 0;
}

void main(void){
    init();
    unsigned int i, j;
    unsigned char next;

    /* 
    to unlock, PORTB needs have the following sequence of values
    1 0 2 0 4 0 8 0 UNLOCKED
    */

    write_locked();
    next = 1;
   
    while(1) {
        while(PORTB == 0);

        if(look_for(next) == 1){
            switch (next){
            case 1:
                next = 2;
                break;
            case 2:
                next = 4;
                break;
            case 4:
                next = 8;
                break;
            case 8:
                PORTA = 255;
                write_unlocked();
                Wait_ms(3000);
                PORTA = 0;
                write_locked();
            
            default:
                next = 1;
                break;
            }
        }else{
            next = 1;
        }

    }

}