// Timer2.C
// Set up a Timer2 interrupt for 1ms
// Display time on the LCD display

// Global Variables

const unsigned char MSG0[21] = "Timer2.C            ";
const unsigned char MSG1[21] = "1ms Interrupt       ";
   
const unsigned char RUN;
unsigned int T2;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// High-priority service
void interrupt IntServe(void){
    if (TMR2IF) {
        if(T2 != 0){
            RC0 = !RC0;
            T2 -= 1;
        }
        TMR2IF = 0;
        }
    }

// Main Routine

void main(void){
    unsigned char i;
    unsigned int j;

    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;

    ADCON1 = 0x0F;

    T2 = 0;

    LCD_Init();                  // initialize the LCD

    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]);

    Wait_ms(1000);
    LCD_Inst(1);  // clear LCD


    // set up Timer2 for 1ms
    T2CON = 0x4D;
    PR2 = 249;
    TMR2ON = 1;
    TMR2IE = 1;
    TMR2IP = 1;
    PEIE = 1;


    // turn on all interrupts
    GIE = 1;



    while(1){
        if(RB0){
            T2 = 5000;
        }else if(RB1){
            T2 = 10000;
        }else if(RB2){
            T2 = 15000;
        }else if(RB3){
            T2 = 20000;
        }
        while(PORTB != 0);

        LCD_Move(0,  0);  LCD_Out(T2, 5, 3);
        // LCD_Move(1,  0);  LCD_Out(PR2, 5, 0);
        // LCD_Move(1,  8);  LCD_Out(T2CON, 5, 0);

        }
   }