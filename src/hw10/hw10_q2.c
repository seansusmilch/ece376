// Capture2.C
//
// Reflex test
//
// Interrupts
//   Timer1:  Time measured to 100ns
//   Capture1:  Rising edge on RC2
//   Capture2:  Falling edge on RC1


#include <pic18.h>

// Global Variables
unsigned long int TIME, TIME0, TIME1;
const unsigned char MSG0[21] = "Reflex Test          "; 

// Interrupt Service Routine

void interrupt IntServe(void) 
{
    if (TMR1IF) {
        TIME = TIME + 0x10000;
        TMR1IF = 0;
    }
    if (CCP1IF) {  // rising edge
        TIME0 = TIME + CCPR1;
        CCP1IF = 0;
    }
    if (CCP2IF) {
        TIME1 = TIME + CCPR2;
        CCP2IF = 0;
    }
}

// Subroutines
#include        "lcd_portd.c"


// Main Routine

void main(void)
{
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

    unsigned int i;
    TRISA = 0;
    TRISB = 0xFF;
    TRISC = 0x04;	// capture every rising edge
    TRISD = 0;
    ADCON1 = 0x0F;
    
    // set up Timer1 for PS = 1
    TMR1CS = 0;
    T1CON = 0x81;
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IP = 1;
    PEIE = 1;
    // set up Capture1 for rising edges
    TRISC2 = 1;
    CCP1CON = 0x05;
    CCP1IE = 1;
    PEIE = 1;
    // set up Capture2 for falling edges
    TRISC1 = 1;
    CCP2CON = 0x05;
    CCP2IE = 1;
    PEIE = 1;

    LCD_Init();
    LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]);
    Wait_ms(1000);

    TIME = 0;

    // turn on all interrupts
    GIE = 1;

    unsigned int count, time_wait;
   
    while(1) {
        while(!RB1);
        while(RB1){
            count = (count + 1) % 100;
        }
        // LCD_Move(1,0); for(int i=0; i<20; i++) LCD_Write(MSG_clr[i]);
        count += 1;
        // LCD_Move(1,0); LCD_Out(count, 3, 0);
        time_wait = ((float) count / 100) * 4000;
        time_wait += 3000;
        Wait_ms(time_wait);
        PORTA = 255;
        while(!RB0);
        PORTA = 0;
        while(RB0);


        // LCD_Move(0,0);  LCD_Out(TIME0, 9, 7);
        LCD_Move(1,0);  LCD_Out(TIME1-TIME0, 9, 7);
        SCI_Out(TIME1-TIME0, 9, 7);
        SCI_CRLF();
    }
}