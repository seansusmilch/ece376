/**
 * @file scales.c
 * @author your name (you@domain.com)
 * @brief Plays a musical scale depending on which button on PORTB is pushed. Will also vary in speed depending on value of the potentiometer
 * @version 0.1
 * @date 2022-12-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
// Notes in Hz
#define Eb4 311.13
#define E4 329.63
#define F4 349.23
#define Gb4 369.99
#define G4 392.00
#define Ab4 415.30
#define A4 440.00
#define Bb4 466.16
#define B4 493.88
#define C5 523.25
#define Db5 554.37
#define D5 587.33
#define Eb5 622.25
#define E5 659.25
#define F5 698.46
#define Gb5 739.99
#define G5 783.99
#define Ab5 830.61
#define A5 880.00
#define Bb5 932.33
#define B5 987.77
#define C6 1046.50
#define Db6 1108.73
#define D6 1174.66
#define Eb6 1244.51
#define E6 1318.51
#define F6 1396.91

// Scales
#define scale_length 8
unsigned char scale_pos = 0;
float *current_scale;
unsigned int NEXT_TIME, NOTE_LENGTH, T2;

struct Scale{
    char name[2];
    float notes[scale_length];
}

struct Scale Bb_scale = {"Bb", {Bb4, C5, D5, Eb5, F5, G5, A5, Bb5}};
struct Scale B_scale =  {"B ", {B4, Db5, Eb5, E5, Gb5, Ab5, Bb5, B5}};
struct Scale C_scale =  {"C ", {C5, D5, E5, F5, G5, A5, B5, C6}};
struct Scale Db_scale = {"Db", {Db5, Eb5, F5, Gb5, Ab5, Bb5, C6, Db6}};
struct Scale D_scale =  {"D ", {D5, E5, Gb5, G5, A5, B5, Db6, D6}};
struct Scale Eb_scale = {"Eb", {Eb4, F4, G4, Ab4, Bb4, C5, D5, Eb5}};
struct Scale E_scale =  {"E ", {E4, Gb4, Ab4, A4, B4, Db5, Eb5, E5}};
struct Scale F_scale =  {"F ", {F4, G4, A4, Bb4, C5, D5, E5, F5}};


unsigned int NOTE = 5000000/440;
unsigned char PLAYING = 0;

const unsigned char MSG_scale[20] = "Scale:        Hz";
const unsigned char MSG_speed[20] = "Speed:          ";


// Subroutine Declarations
#include <pic18.h>
#include "lcd_portd.c"

unsigned int A2D_Read(unsigned char c){
    unsigned int result;
    unsigned char i;
    c = c & 0x0F;
    ADCON0 = (c << 2) + 0x01; // set Channel Select
    for (i=0; i<10; i++); // wait 2.4us (approx)
    GODONE = 1; // start the A/D conversion
    while(GODONE); // wait until complete (approx 8us)
    return(ADRES);
}

void interrupt IntServe(void){
    if(TMR1IF){
        TMR1IF = 0;
    }
    if(TMR2IF){
        // When timer2 is triggered, play the next note
        T2++;
        if(PLAYING && T2 >= NEXT_TIME){
            NEXT_TIME = T2 + NOTE_LENGTH;
            scale_pos++;
            if(scale_pos<scale_length){
                NOTE = 5000000/current_scale[scale_pos];
            }else{
                PLAYING = 0;
            }
        }
        TMR2IF = 0;
    }
    if(CCP1IF){
        if(PLAYING){
            RC3 = !RC3;
            CCPR1 += NOTE;
        }
        CCP1IF = 0;
    }
}

void Play(float NOTE_hz, unsigned int duration){
    NOTE = 5000000/NOTE_hz;
    CCPR1 = TMR1 + NOTE;
    CCP1IE = 1;
    PLAYING = 1;

    Wait_ms(duration);
    PLAYING = 0;
    CCP1IE = 0;
}

unsigned int A2DtoDuration(unsigned int A2Din){
    unsigned int duration = 1024; // in ms
    // duration = (duration - A2Din)/1.5;
    return duration - A2Din;
}

void PlayScale(struct Scale scale, unsigned int AnalogIn){
    LCD_Move(0,7);  for(int i=0; i<2; i++) LCD_Write(scale.name[i]); // print name of current scale

    current_scale = scale.notes;
    scale_pos = 0;
    T2 = 0;
    NOTE_LENGTH = A2DtoDuration(AnalogIn);
    LCD_Move(1,6); LCD_Out(NOTE_LENGTH, 4, 0);
    NEXT_TIME = NOTE_LENGTH;

    NOTE = 5000000/current_scale[0];
    CCPR1 = TMR1 + NOTE;
    CCP1IE = 1;
    PLAYING = 1;
}

void init(void){
    // Turn on the A/D input
    TRISA = 0xFF;
    TRISE = 0x0F;
    ADCON2 = 0x95;
    ADCON1 = 0x07;
    ADCON0 = 0x01;

    TRISB = 0xFF;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;

    // set up Timer1 for PS = 1
    TMR1CS = 0;
    T1CON = 0x81;
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IP = 1;

    // set up Compare for no change
    CCP1CON = 0x0A;
    CCP1IE = 0;

    // Timer2 Initialize
    T2CON = 0x4D;
    PR2   = 249;
    TMR2ON = 1;
    TMR2IE = 1;
    TMR2IP = 1;

    PEIE = 1;
    GIE = 1;

    LCD_Init();
    LCD_Move(0,0);  for (int i=0; i<20; i++) LCD_Write(MSG_scale[i]); 
    LCD_Move(1,0);  for (int i=0; i<20; i++) LCD_Write(MSG_speed[i]); 
}

// Main Routine
void main(void){
    init();
    unsigned int A2D;
    while(1) {
        A2D = A2D_Read(0);
        if(!PLAYING && !(scale_pos > 0 && scale_pos < scale_length)){
            if (RB0) PlayScale(Bb_scale, A2D);
            if (RB1) PlayScale(B_scale, A2D);
            if (RB2) PlayScale(C_scale, A2D);
            if (RB3) PlayScale(Db_scale, A2D);
            if (RB4) PlayScale(D_scale, A2D);
            if (RB5) PlayScale(Eb_scale, A2D);
            if (RB6) PlayScale(E_scale, A2D);
            if (RB7) PlayScale(F_scale, A2D);
        }
        // if (RB2) Play(C5);
        LCD_Move(0,10);  LCD_Out(current_scale[scale_pos], 3, 0); // print current note
        LCD_Move(1,11); LCD_Out(A2DtoDuration(A2D), 4, 0); // print current A2D
    }
}