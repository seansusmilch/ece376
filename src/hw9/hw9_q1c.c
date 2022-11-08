// Measure time to 100ns

// Global Variables

const unsigned char MSG0[21] = "T0_Time.C           "; 
const unsigned char MSG1[21] = "                    ";     

unsigned long int TIME;

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

    // set up Timer0 for PS = 1
    T0CS = 0;
    T0CON = 0x88;
    TMR0ON = 1;
    TMR0IE = 1;
    TMR0IP = 1;
    PEIE = 1;
    // turn on all interrupts
    GIE = 1;

    TIME = 0;


    while(1) {
        LCD_Move(0,0);
        TRISB = 0xFF;
        TIME1 = TIME + TMR0;
        
        for(i=0; i<10; i++) { // start
            while(!RB0);
            while(RB0);
        }

        TIME2 = TIME + TMR0;
        LCD_Move(1,0);  LCD_Out(TIME2 - TIME1, 10, 7);
    }
}