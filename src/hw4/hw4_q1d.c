#include <pic18.h>

void main(void){
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON1 = 0x0F;

    float A, B, C;
    A = 3.14159265379;
    B = 2.718281828;
    while(1) {
        i = (i + 1)% 128;
        if(i == 0) PORTC += 1;
            C = A / B;
    }
}