void BarGraph(unsigned int TIME){
    /*
    Breakpoints
    15000/8
    1   1875
    2   3750
    3   5625
    4   7500
    5   9375
    6   11250
    7   13125
    8   15000
    */

    int t = TIME / 8;

    if(t < 1875){
        PORTD = 0;
        return;
    }
    RD0 = 1;

    if(t >= 3750) RD1 = 1;
    if(t >= 5625) RD2 = 1;
    if(t >= 7500) RD3 = 1;
    if(t >= 9375) RD4 = 1;
    if(t >= 11250) RD5 = 1;
    if(t >= 13125) RD6 = 1;
    if(t >= 15000) RD7 = 1;
}