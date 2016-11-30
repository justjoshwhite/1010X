#ifndef OPCONTROL_H_
#define OPCONTROL_H_

#include "main.h"
///*
//here
#define CLAW_MAX 1000
#define CLAW_CLOSED 100


void drive_clawcontrol (void *ignore)
{
  int clawpos;
  int power_L;
  int power_R;

  int clawdiff;
  int lastdiff;

  float k_proportion = 0.5;
  int proportion;

  float k_integral = 0;
  int integral_activezone = 100;
  int integral;

  float k_derivative = 0;
  int derivative;

  while(true){

    //set value
    clawpos = analogRead(potclaw);

    //find error
    clawdiff = clawtarget - clawpos;

    //calculate P
    proportion = clawdiff;

    //intergral cap+calcualte I
    if(abs(clawdiff) < integral_activezone){
    integral = integral + (clawdiff);}
    else{integral = 0;}

    //calculate D
    derivative =  clawdiff - lastdiff;
    lastdiff = clawdiff;


    //calculate power values
    power_L = (derivative*k_derivative) + (integral*k_integral)+(proportion*k_proportion);
    power_R = (derivative*k_derivative) + (integral*k_integral)+(proportion*k_proportion);

    if(joystickGetDigital(1,5,JOY_UP)){
      motorSet(ClawL, ClawL_Dir*127);
      motorSet(ClawR, ClawR_Dir*127);
      clawtarget = analogRead(potclaw);}

    else if(joystickGetDigital(1,5,JOY_DOWN)){
      motorSet(ClawL, ClawL_Dir*-127);
      motorSet(ClawR, ClawR_Dir*-127);
      clawtarget = analogRead(potclaw);}

    else {
      motorSet(ClawL, ClawL_Dir*power_L);
      motorSet(ClawR, ClawR_Dir*power_R);
        }
  //delay
    delay(20);
    }
  }

void clawpresets(){
    if(joystickGetDigital(1,7,JOY_UP)){
      clawtarget = CLAW_MAX;}
    else if(joystickGetDigital(1,7,JOY_DOWN)){
      clawtarget = CLAW_CLOSED;}
    else if (joystickGetDigital(1,7,JOY_LEFT)){}
    else if(joystickGetDigital(1,7,JOY_RIGHT)){}
    else{}
  }
//*/
#endif
