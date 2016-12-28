#include "main.h"
#include "claw.h"
#include "util.h"
#include "pid.h"

void clawtask(void*ignore){

    PID_init(&pid_claw, 0.5, 0, 0, 0);
    claw_target_global = encoderGet(encoder_CLAW);

    test_clawup = 100;
    test_clawdown = 100;


    while(true){
      if(!isEnabled()){break;}

      claw_pos_global = encoderGet(encoder_CLAW);


if(!isAutonomous() && joystickGetDigital(1, 5, JOY_UP)){
  motorset_claw(127); //cloase
  claw_target_global = encoderGet(encoder_CLAW) + 130;
}

else if(!isAutonomous() && joystickGetDigital(1, 5, JOY_DOWN)){
  motorset_claw(-127); //cloase
  claw_target_global = encoderGet(encoder_CLAW) - 100;

}


/*
      if(!isAutonomous() && (joystickGetDigital(1, 5, JOY_UP)||joystickGetDigital(1, 5, JOY_DOWN)||joystickGetDigital(2, 5, JOY_DOWN)||joystickGetDigital(2, 5, JOY_UP)))
        {
        while(joystickGetDigital(1, 5, JOY_UP)){
            motorset_claw(127);
            delay(20);}

        while(joystickGetDigital(1, 5, JOY_DOWN)){
            motorset_claw(-127);
            delay(20);}

        while(joystickGetDigital(2, 5, JOY_UP)){
            motorset_claw(127);
            delay(20);}

        while(joystickGetDigital(2, 5, JOY_DOWN)){
            motorset_claw(-127);
            delay(20);}

        motorset_claw(0);
        delay(CLAW_DELAY);
        claw_target_global = encoderGet(encoder_CLAW);
        }

        */
      else{
      motorset_claw( PID_cal(&pid_claw, claw_target_global, claw_pos_global) );}

      delay(20);
      }
    motorset_claw(0);
    taskDelete(claw_task);

  }

void clawpresets(){
  if(joystickGetDigital(1,7,JOY_UP)){claw_target_global = CLAW_CLOSED;}
    else if(joystickGetDigital(1,7,JOY_DOWN)){claw_target_global = CLAW_MAX;}
    else if(joystickGetDigital(1,7,JOY_LEFT)){claw_target_global = CLAW_45;}
    else if(joystickGetDigital(1,7,JOY_RIGHT)){claw_target_global = CLAW_PARALLEL;}

    else if (joystickGetDigital(2,7,JOY_DOWN)){claw_target_global = CLAW_CLOSED;}
    else if(joystickGetDigital(2,7,JOY_DOWN)){claw_target_global = CLAW_MAX;}
    else if(joystickGetDigital(2,7,JOY_LEFT)){claw_target_global = CLAW_45;}
    else if(joystickGetDigital(2,7,JOY_RIGHT)){claw_target_global = CLAW_PARALLEL;}

    else{}
}
