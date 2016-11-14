#include "main.h"
#include "API.h"


void armtaskcode (void *ignore)
{
float karm = 0.5;
  while(true){

    if (joystickGetDigital(1, 6, JOY_UP)){
      motorSet(ArmLT, ArmLT_Dir*127);
      motorSet(ArmLB, ArmLB_Dir*127);
      motorSet(ArmRT, ArmRT_Dir*127);
      motorSet(ArmRB, ArmRB_Dir*127);
      armtarget = analogRead(potarmL);
    }else if(joystickGetDigital(1,6,JOY_DOWN)){
      motorSet(ArmLT, ArmLT_Dir*-127);
      motorSet(ArmLB, ArmLB_Dir*-127);
      motorSet(ArmRT, ArmRT_Dir*-127);
      motorSet(ArmRB, ArmRB_Dir*-127);
      armtarget = analogRead(potarmL);
    }
    else if(joystickGetDigital(2,6,JOY_UP)){
      motorSet(ArmLT, ArmLT_Dir*127);
      motorSet(ArmLB, ArmLB_Dir*127);
      motorSet(ArmRT, ArmRT_Dir*127);
      motorSet(ArmRB, ArmRB_Dir*127);
      armtarget = analogRead(potarmL);
    }
    else if(joystickGetDigital(2,6,JOY_DOWN)){
      motorSet(ArmLT, ArmLT_Dir*-127);
      motorSet(ArmLB, ArmLB_Dir*-127);
      motorSet(ArmRT, ArmRT_Dir*-127);
      motorSet(ArmRB, ArmRB_Dir*-127);
      armtarget = analogRead(potarmL);
    }
    else {
        int armheightL = analogRead(potarmL);
        int armheightR = analogRead(potarmR);

        int armdifferenceL = armtarget - armheightL;
        int armdifferenceR = armtarget - armheightR;

        motorSet(ArmLT, motorcap(ArmLT_Dir*armdifferenceL*karm));
        motorSet(ArmLB, motorcap(ArmLB_Dir*armdifferenceL*karm));
        motorSet(ArmRT, motorcap(ArmRT_Dir*armdifferenceR*karm));
        motorSet(ArmRB, motorcap(ArmRB_Dir*armdifferenceR*karm));

        delay(25);
    }
  }
}

void armpresets(){
  if(joystickGetDigital(2,8,JOY_UP)){
    armtarget = FENCE_HIGH;}
  else if(joystickGetDigital(2,8,JOY_DOWN)){
    armtarget = GROUND;}
  else if (joystickGetDigital(2,8,JOY_LEFT)){
    armtarget = FENCE_HIGH;}
  else if(joystickGetDigital(2,8,JOY_RIGHT)){
    armtarget = FENCE_LOW;}
  else{}
}
