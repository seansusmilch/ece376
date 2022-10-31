const unsigned char MSG0[21] = "  Reflex Test    ";
const unsigned char MSG_ms[3] = "ms";
unsigned int TIME;

#include <pic18.h>
#include "lcd_portd.c"

void init(void){
    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    ADCON1 = 0x0F;

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

    // Timer 2 interrupt for 0.1ms
    T2CON = 0x45;
    PR2 = 25;
    TMR2ON = 0;
    TMR2IE = 1;
    TMR2IP = 1;
    PEIE = 1;

    // turn on all interrupts
    GIE = 1;
}

void interrupt timer2(void){
    if(TMR2IF){
        RC0 = !RC0;
        TIME += 1;
        TMR2IF = 0;
    }
}

void main(void){
    init();

    unsigned int count, time_wait;
    PORTA = 0;
    TIME = 0;

    while(1){
        TMR2ON = 0;

        while(!RB0);
        while(RB0){
            count = (count + 1) % 100;
        }
        count += 1;
        LCD_Move(1,0); LCD_Out(count, 3, 0);
        time_wait = ((float) count / 100) * 4000;
        time_wait += 3000;

        TIME = 0;
        Wait_ms(time_wait);
        PORTA = 255;
        TMR2ON = 1;
        while(!RB0);
        TMR2ON = 0;
        PORTA = 0;
        while(RB0);
        
        LCD_Move(1,5); LCD_Out(TIME, 6, 1);
        for(int i=0; i<2; i++) LCD_Write(MSG_ms[i]);
        SCI_Out(TIME, 5, 0);
        SCI_CRLF();
    }
}

/*
 02937
 01991
 00000
 02468
 03964
 05069
 01939
 02793
 02567
 02807
 04691
*/