#include "main.h"
#include "arm.h"
#include "util.h"
#include "pid.h"
#include "autofunctions.h"

#define ARM_UP 100
#define ARM_DOWN 60

void armtask (void*ignore){

  PID_init(&pidarm_auto, 0.8, 0, 0, 0); // was 0.4
  PID_init(&pidarm_op, 0.8, 0, 0, 0);
  arm_target_global = encoderGet(encoder_ARM);

//  test_armdown = 100;
//  test_armup = 100;

  while(true){
    if(!isEnabled()){break;}

    arm_pos_global = encoderGet(encoder_ARM);

/*
    if(!isAutonomous() && joystickGetDigital(1, 6, JOY_UP)){

      delay(40);
      motorset_arm(127);
      arm_target_global = encoderGet(encoder_ARM)+ARM_UP;} //was 150

    else if(!isAutonomous() && joystickGetDigital(1, 6, JOY_DOWN)){

      delay(40);
      motorset_arm(-127);
      arm_target_global = encoderGet(encoder_ARM)-ARM_DOWN;} //was 50


    /*
    if(!isAutonomous() && (joystickGetDigital(1, 6, JOY_UP)||joystickGetDigital(1, 6, JOY_DOWN)))
      {
      while(joystickGetDigital(1, 6, JOY_UP)){
          motorset_arm(127);
          delay(20);}

      while(joystickGetDigital(1, 6, JOY_DOWN)){
          motorset_arm(-127);
          delay(20);}

      motorset_arm(0);
      delay(ARM_DELAY);
      arm_target_global = encoderGet(encoder_ARM);
      }


  //if(!joystickGetDigital(1, 6, JOY_UP)||!joystickGetDigital(1, 6, JOY_DOWN)){

else{
     if(isAutonomous()){motorset_arm( PID_cal(&pidarm_auto, arm_target_global, arm_pos_global) );}
     else{motorset_arm( PID_cal(&pidarm_op, arm_target_global, arm_pos_global) );}

   }
*/

if(joystickGetDigital(1, 6, JOY_UP)) {  arm_target_global = arm_target_global + 13;}
if(joystickGetDigital(1, 6, JOY_DOWN)) { arm_target_global = arm_target_global- 13;}
//if(joystickGetDigital(2, 6, JOY_UP)) {  arm_target_global = arm_target_global + 13;}
//if(joystickGetDigital(2, 6, JOY_DOWN)) { arm_target_global = arm_target_global- 13;}

if(arm_target_global < -15 ) {  arm_target_global  = -15; }
if(arm_target_global > 657)  {  arm_target_global  = 657; }


if(isAutonomous()){motorset_arm( PID_cal(&pidarm_auto, arm_target_global, arm_pos_global) );}
else{motorset_arm( PID_cal(&pidarm_op, arm_target_global, arm_pos_global) );}



    delay(20);



    }

  motorset_arm(0);
  taskDelete(arm_task);
  }

void armpresets(){
  if(joystickGetDigital(1,8,JOY_UP)){arm_target_global = ARM_SKILLS_1;}
    else if(joystickGetDigital(1,8,JOY_DOWN)){arm_target_global = ARM_GROUND;}
    //else if (joystickGetDigital(1,8,JOY_LEFT)){arm_target_global = ARM_LOW;}
    //else if(joystickGetDigital(1,8,JOY_RIGHT)){arm_target_global = ARM_PARALLEL;}
    else{}
  }
