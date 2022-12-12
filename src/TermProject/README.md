# Variable Speed Music Scales

Plays a musical scale depending on which button on PORTB is pushed. Will also vary in speed depending on value of the potentiometer

# Requirements

## Inputs

* Port B push buttons
* Potentiometer on Port A

## Outputs

* LCD Display
* Speaker

## Function

PortB will have a different musical scale attached to each button: Bb (B flat) for RB0, B (B natural) for RB1, C for RB2, 

When a button is pushed, the speaker will play each note of the scale at the speed set by the potentiometer. Once the speaker reaches the top note of the scale, if the same button is still pushed, the speaker will play the scale again.

The LCD will display the current scale, note, and speed.