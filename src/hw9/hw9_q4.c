// Measure time to 100ns

// Global Variables

const unsigned char MSG0[21] = "Reflex Test         "; 
const unsigned char MSG1[21] = "                    ";     

unsigned long int TIME, T2TIME;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

void interrupt IntServe(void)
{
    if (TMR0IF) {
        TIME = TIME + 0x10000;
        TMR0IF = 0;
    }
    if(TMR2IF){
        T2TIME += 1;
        TMR2IF = 0;
    }
}

// Main Routine

void main(void)
{
    unsigned char i;
    unsigned long int TIME1, TIME2;

    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;

    LCD_Init();                  // initialize the LCD

    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

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

    // set up Timer0 for PS = 1
    T0CS = 0;
    T0CON = 0x88;
    TMR0ON = 1;
    TMR0IE = 1;
    TMR0IP = 1;
    PEIE = 1;
    // set up Timer2 for 1ms
    T2CON = 0xA4;
    PR2   = 249;
    TMR2ON = 0;
    TMR2IE = 1;
    TMR2IP = 1;
    PEIE = 1;
    // turn on all interrupts
    GIE = 1;

    TIME = 0;

    unsigned long int count, time_wait;

    while(1) {
        LCD_Move(0,0);
        while(!RB0);
        while(RB0){
            count = (count + 1) % 100;
        }
        // LCD_Move(1,0); for(int i=0; i<20; i++) LCD_Write(MSG_clr[i]);
        count += 1;
        // LCD_Move(1,0); LCD_Out(count, 3, 0);
        time_wait = ((float) count / 100) * 4000;
        time_wait += 3000;

        // Wait_ms(time_wait);
        // Wait with TMR 2 instead
        T2TIME = 0;
        TMR2ON = 1;
        while(T2TIME < time_wait * 10);
        PORTA = 255;

        TIME1 = TIME + TMR0;
        while(!RB0);
        TIME2 = TIME + TMR0;
        PORTA = 0;
        TMR2ON = 0;
        while(RB0);

        LCD_Move(1,0);  LCD_Out(TIME2 - TIME1, 10, 7);
        SCI_Out(TIME2 - TIME1, 10, 7);
        SCI_CRLF();
    }
}