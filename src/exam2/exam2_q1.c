void main(void){
    ADCON1 = 0x0F;
    PORTB = 0xFF;
    PORTC = 0;

    int Time = 0;

    while(1){
        if(!RB0){
            Time = 0;
        }else{
            Time += 1;
            Wait_ms(1000);
        }

        if(Time > 30){
            RC0 = !RC0;
        }else{
            RC0 = 0;
        }
        Wait_ms(2);
    }
}