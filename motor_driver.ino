/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%BEACHTECH-ROBOTICS 
%ATiny85 Bi-direction DC motor control
%Greggory Hartsfield
%August/31/2022
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

// Requires headers for AVR defines and ISR function
#include <avr/io.h>
#include <avr/interrupt.h>

#define INTERRUPT_PIN1 PCINT1  // This is PB1 per the schematic
#define INTERRUPT_PIN2 PCINT2  

//Defineing the pins on ATtiny
#define S1       PB0
#define S2       PB1
#define pwm1     PB2
#define pwm2     PB3
#define pwm3     PB4
#define pwm4     PB5

int maxInput = 2000;   //PWM Max range input of 2000ms
int minInput = 1000;   //PWM Min range input of 1000ms

boolean S1motorDir = 0;
boolean S2motorDir = 0;

int Value1;
int Value2;
int V1;
int V2;
void setup() {
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);
  pinMode(pwm3,   OUTPUT);
  pinMode(pwm4,   OUTPUT);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN1);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(S1, INPUT_PULLUP);        // Set our interrupt pin as input with a pullup to keep it stable
  PCMSK |= (2 << INTERRUPT_PIN2);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (2 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(S2, INPUT_PULLUP);        // Set our interrupt pin as input with a pullup to keep it stable
  sei();                            //last line of setup - enable interrupts after setup
}
 
void loop() {
  Value1 = analogRead(S2);
  Value2 = analogRead(S2);

  if(S1motorDir = 1){
    V1 = map(Value1, 1500, 2000, 0, 255);
    analogWrite(pwm1, V1);
    analogWrite(pwm2, 0);
  }else{
    V1 = map(Value1, 1000, 1500, 0, 255);
    analogWrite(pwm1, 0);
    analogWrite(pwm2, V1);
  }  
  
  if(S2motorDir =1 ){
    V2 = map(Value2, 1500, 2000, 0, 255);
    analogWrite(pwm3, Value2);
    analogWrite(pwm4, 0);
  }else{
    V2 = map(Value2, 1000, 1500, 0, 255);
    analogWrite(pwm3, 0);
    analogWrite(pwm4, V2);
  } 
   
  if(S1>1500){
    S1motorDir = 1;    
  }else{
    S1motorDir = 0; 
  }
  
  if(S2>1500){
    S2motorDir = 1;
  }else{
    S2motorDir = 0; 
  }
}
