#ifndef OPCONTROL_H_
#define OPCONTROL_H_

#include "main.h"

//here
#define ARM_MAX_R 1000
#define ARM_MAX_L 1000
#define ARM_GROUND_R 100
#define ARM_GROUND_L 100
#define ARM_MID_R 500
#define ARM_MID_L 500


void drive_armcontrol (void *ignore)
{
  //int armtarget_L = 0;
  //int armtarget_R = 0;
  int armheight_L;
  int armheight_R;
  int power_L;
  int power_R;

  int armdiff_L;
  int armdiff_R;
  int lastdiff_L;
  int lastdiff_R;

  float k_proportion = 0.1;
  int proportion_L;
  int proportion_R;

  float k_integral = 0;
  int integral_activezone = 100;
  int integral_L;
  int integral_R;

  float k_derivative = 0;
  int derivative_L;
  int derivative_R;

  armtarget_L = analogRead(potarmL);
  armtarget_R = analogRead(potarmR);

  while(true){

    //set value
    armheight_L = analogRead(potarmL);
    armheight_R = analogRead(potarmR);

    //find error
    armdiff_L = armtarget_L - armheight_L;
    armdiff_R = armtarget_R - armheight_R;

    //calculate P
    proportion_L = armdiff_L;
    proportion_R = armdiff_R;

    //intergral cap+calcualte I
    if(abs(armdiff_L) < integral_activezone){
    integral_L = integral_L + (armdiff_L);}
    else{integral_L = 0;}

    if(abs(armdiff_R) < integral_activezone){
      integral_R = integral_R + (armdiff_R);}
    else{integral_R = 0;}

    //calculate D
    derivative_L =  armdiff_L - lastdiff_L;
    lastdiff_L = armdiff_L;
    derivative_R =  armdiff_R - lastdiff_R;
    lastdiff_R = armdiff_R;

    //calcualte power values
    power_L = (derivative_L*k_derivative) + (integral_L*k_integral)+(proportion_L*k_proportion);
    power_R = (derivative_R*k_derivative) + (integral_R*k_integral)+(proportion_R*k_proportion);

    if(joystickGetDigital(1,6,JOY_UP)){
      motorSet(ArmLT, ArmLT_Dir*127);
      motorSet(ArmLB, ArmLB_Dir*127);
      motorSet(ArmRT, ArmRT_Dir*127);
      motorSet(ArmRB, ArmRB_Dir*127);
      armtarget_L = analogRead(potarmL);
      armtarget_R = analogRead(potarmR);}

    else if(joystickGetDigital(1,6,JOY_DOWN)){
      motorSet(ArmLT, ArmLT_Dir*-127);
      motorSet(ArmLB, ArmLB_Dir*-127);
      motorSet(ArmRT, ArmRT_Dir*-127);
      motorSet(ArmRB, ArmRB_Dir*-127);
      armtarget_L = analogRead(potarmL);
      armtarget_R = analogRead(potarmR);}
    else {
        motorSet(ArmLT, ArmLT_Dir*power_L);
        motorSet(ArmLB, ArmLB_Dir*power_L);
        motorSet(ArmRT, ArmRT_Dir*power_R);
        motorSet(ArmRB, ArmRB_Dir*power_R);
        }
  //delay
    delay(20);
    }
  }

void armpresets(){
    if(joystickGetDigital(1,8,JOY_UP)){
      armtarget_L = ARM_MAX_L;
      armtarget_R = ARM_MAX_R;}
    else if(joystickGetDigital(1,8,JOY_DOWN)){
      armtarget_L = ARM_GROUND_L;
      armtarget_R = ARM_GROUND_R;}
    else if (joystickGetDigital(1,8,JOY_LEFT)){
      armtarget_L = ARM_MID_L;
      armtarget_R = ARM_MID_R;}
    else if(joystickGetDigital(1,8,JOY_RIGHT)){
    //  armtarget_L = ;
    //  armtarget_R = ;
    }
    else{
    }
  }

#endif
