// Global Variables
const unsigned char MSG[16] = "Combo Lock      ";
unsigned char TABLE[4] = {1, 2, 4, 8};
int STEP, N, TIME;

// Subroutine Declarations
#include <pic18.h>
#include "keypad.c"
#include "LCD_PortD.C"
        
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
   LCD_Move(0,0);
   for (i=0; i<16; i++) LCD_Write(MSG[i]);
   Wait_ms(100);
    CODE = 4567;

    while(1) {
        TEMP = ReadKey();
        if(TEMP < 10)
            CODE_NEXT = (CODE_NEXT * 10) + TEMP;
        
        if(TEMP == 10){
            if(CODE_NEXT < 0 || CODE_NEXT > 9999){
                // invalid entry
            }else if(CODE_NEXT == CODE){
                for(STEP=0; STEP < 50; STEP++){
                    PORTC = TABLE[STEP % 4];
                    Wait_ms(10);
                }
                Wait_ms(2000);
                for(STEP=50; STEP > 0; STEP--){
                    PORTC = TABLE[STEP % 4];
                    Wait_ms(10);
                }
            }
            CODE_NEXT = 0;
        }
    }
  
}
