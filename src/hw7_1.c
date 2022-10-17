const unsigned char MSG0[21] = "  Reflex Test    ";
const unsigned char MSG_ms[3] = "ms";

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
}

void main(void){
    init();

    unsigned int count, time_wait;
    unsigned long time_reflex;
    PORTA = 0;

    while(1){
        while(!RB0);
        while(RB0){
            count = (count + 1) % 100;
        }
        count += 1;
        LCD_Move(1,0); LCD_Out(count, 3, 0);
        time_wait = ((float) count / 100) * 4000;
        time_wait += 3000;

        time_reflex = 0;
        Wait_ms(time_wait);
        PORTA = 255;
        while(!RB0){
            time_reflex++;
            PORTA++; // used to calibrate the count to milliseconds calculation
        }
        PORTA = 0;
        while(RB0);
        
        time_reflex = time_reflex / 526.3;
        LCD_Move(1,5); LCD_Out(time_reflex, 5, 0);
        for(int i=0; i<2; i++) LCD_Write(MSG_ms[i]);
        SCI_Out(time_reflex, 5, 0);
        SCI_CRLF();
    }
}

/*
 00189
 00275
 00385
 00218
 00163
 00356
 00160
 00206
 00190
 00188
 00235
 00170
 00387
 00242
 00164
 00161
 00258
 00174
 00164

*/