
// Global Variables

const unsigned char MSG0[21] = "Chord.C             "; 
const unsigned char MSG1[21] = "                    ";     

// const unsigned int A3 = 22727;
// const unsigned int B3 = 20247;
// const unsigned int C4 = 19110;
// const unsigned int D4 = 17026;
const unsigned int E4 = 15168;
const unsigned int F4 = 14317;
const unsigned int Fsharp = 13514;
const unsigned int G4 = 12755;
// const unsigned int A4 = 11363;

unsigned int N0, N1, N3;

// Subroutine Declarations
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"

// Interrupt Service Routine
void interrupt IntServe(void)
{
    if (TMR0IF) {
        TMR0 = -N0;
        if (PORTB) RC0 = !RC0;
        TMR0IF = 0;
        }
    if (TMR1IF) {
        TMR1 = -N1;
        if (PORTB) RC1 = !RC1;
        TMR1IF = 0;
        }
    if (TMR2IF) {
        TMR2 = - N2
        if (PORTB) RC2 = !RC2;
        TMR2IF = 0;
        }   
    if (TMR3IF) {
        TMR3 = -N3;
        if (PORTB) RC3 = !RC3;
        TMR3IF = 0;
    }
}
    

            
    // Main Routine

    void main(void)
    {
    unsigned char i;

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
    // set up Timer1 for PS = 1
    TMR1CS = 0;
    T1CON = 0x81;
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IP = 1;
    PEIE = 1;
    // set up Timer2 for PS = 1
    T2CON = 0x96;
    PR2   = 249;
    TMR2ON = 1;
    TMR2IE = 1;
    TMR2IP = 1;
    PEIE = 1;
    // set up Timer3 for every 1.3513879 ms
    TMR3CS = 0;
    T3CON = 0x81;
    TMR3ON = 1;
    TMR3IE = 1;
    TMR3IP = 1;
    PEIE = 1;
    // turn on all interrupts
    GIE = 1;

    N0 = E4;
    N1 = F4;
    N3 = G4;

    while(1) {

        LCD_Move(0,10);  LCD_Out(N0, 5, 0);
        LCD_Move(1,0);  LCD_Out(N1, 5, 0);
        LCD_Move(1,10);  LCD_Out(N3, 5, 0);
    }      
}
