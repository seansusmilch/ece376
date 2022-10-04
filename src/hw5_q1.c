// NeoPixel0.C
//
// This program drives a NeoPixel connected to RD0
// Drives the NeoPixel with 16 colors
//
//
// Global Variables

unsigned char PIXEL @ 0x000;

const unsigned char MSG0[20] = "LED FLASHLIGHT     ";
const unsigned char MSG1[20] = "                   ";

// Subroutine Declarationsb
#include <pic18.h>

// Subroutines
#include        "lcd_portd.c"
#include        "keypad.c"
  
void NeoPixel_Display(unsigned char RED, 
		unsigned char GREEN, unsigned char BLUE)
{
   PIXEL = GREEN;	asm("  call Pixel_8 ");
   PIXEL = RED;		asm("  call Pixel_8 ");
   PIXEL = BLUE;	asm("  call Pixel_8 ");

   asm("    return");


#asm
Pixel_8:
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    call	Pixel_1
    return

Pixel_1:
	bsf		((c:3971)),0	; PORTD,0
    nop
	btfss   ((c:0000)),7
	bcf		((c:3971)),0
	rlncf   ((c:0000)),F
    nop
    nop
    bcf		((c:3971)),0
    return

#endasm
   }

void set_brightness(unsigned char x){
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
    NeoPixel_Display(x, x, x);
}
// Main Routine

void main(void)
{
   unsigned int i, N;
   unsigned char RED, GREEN, BLUE;
   int BRIGHTNESS_NEXT, BRIGHTNESS, TEMP;

   TRISA = 0;
   TRISB = 0xFF;
   TRISC = 0xF8;
   TRISD = 0;
   TRISE = 0;
   TRISA = 0;
   PORTB = 0;
   PORTC = 0;
   PORTD = 0;
   PORTE = 0;
   ADCON1 = 0x0F;

   LCD_Init();                  // initialize the LCD
   TRISD0 = 0;

   LCD_Move(0,0);  for (i=0; i<20; i++) LCD_Write(MSG0[i]); 
   LCD_Move(1,0);  for (i=0; i<20; i++) LCD_Write(MSG1[i]); 
   Wait_ms(100); 
    BRIGHTNESS = 10;
    BRIGHTNESS_NEXT = 0;
// Base Program
    set_brightness(5);
    while(1) {
        TEMP = ReadKey();
        if(TEMP<10)
            BRIGHTNESS_NEXT = (BRIGHTNESS_NEXT*10) + TEMP;

        if(TEMP == 10){
            if(BRIGHTNESS_NEXT < 0 || BRIGHTNESS_NEXT > 255){
                BRIGHTNESS_NEXT = 0;
            }
            BRIGHTNESS = BRIGHTNESS_NEXT;
            BRIGHTNESS_NEXT = 0;
            set_brightness(BRIGHTNESS);
        }

        LCD_Move(1,5); LCD_Out(BRIGHTNESS_NEXT, 5, 0)
        Wait_ms(100); 
    }

}