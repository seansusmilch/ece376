// Global Variables
const unsigned char MSG[21] = "Combo Lock          ";
const unsigned char MSG_LOCKED[21] = "LOCKED              ";
const unsigned char MSG_UNLOCKED[21] = "UNLOCKED            ";
const unsigned char MSG_INVALID[21] = "INVALID             ";
unsigned char TABLE[4] = {1, 2, 4, 8};
int STEP, N, TIME;

// Subroutine Declarations
#include <pic18.h>
#include "lcd_portd.c"
#include "keypad.c"
        
// Main Routine

void main(void)
{
   int i;
    int CODE, CODE_NEXT, TEMP;
   TRISA = 0;
   TRISB = 0;
   TRISC = 0xF8;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   STEP = 0;

   LCD_Init();
   LCD_Move(0,0); for (i=0; i<21; i++) LCD_Write(MSG[i]);
   LCD_Move(1,0); for (i=0; i<21; i++) LCD_Write(MSG[i]);
   
   Wait_ms(100);
   LCD_Move(1,0); for(i=0; i<21; i++) LCD_Write(MSG_LOCKED[i]);
    CODE = 4567;
    CODE_NEXT = 0;
    TEMP = -1;
    PORTB = 0;
    PORTC = 0;
    while(1) {
        if(TEMP < 10){
            CODE_NEXT = (CODE_NEXT * 10) + TEMP;
        }else if(TEMP == 10){
            if(CODE_NEXT < 0 || CODE_NEXT > 9999){
                LCD_Move(1,0); for(i=0; i<21; i++) LCD_Write(MSG_INVALID[i]);
                Wait_ms(1000);
                LCD_Move(1,0); for(i=0; i<21; i++) LCD_Write(MSG_LOCKED[i]);
            }else if(CODE_NEXT == CODE){
                LCD_Move(1,0); for(i=0; i<16; i++) LCD_Write(MSG_UNLOCKED[i]);
                for(STEP=0; STEP < 50; STEP++){
                    PORTB = TABLE[STEP % 4];
                    Wait_ms(10);
                }
                Wait_ms(2000);
                LCD_Move(1,0); for(i=0; i<16; i++) LCD_Write(MSG_LOCKED[i]);
                for(STEP=50; STEP > 0; STEP--){
                    PORTB = TABLE[STEP % 4];
                    Wait_ms(10);
                }
            }
            CODE_NEXT = 0;
        }
        LCD_Move(1,9); LCD_Out(CODE_NEXT, 4, 0);
        TEMP = ReadKey();
    }
}
