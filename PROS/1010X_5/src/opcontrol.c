
#include "main.h"
#include "arm.h"
#include "claw.h"
#include "util.h"
#include "lcdfunctions.h"

void operatorControl() {

	lcdClear(uart1);
	TaskHandle opcontrollcd_task = taskCreate(opcontrollcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	TaskHandle claw_task = taskCreate (clawtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	TaskHandle arm_task = taskCreate (armtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	while (true) {

		delay(20);

		motorset_drive(joystickGetAnalog(1, 3), joystickGetAnalog(1,2));

		//armpresets();
		//clawpresets();


/*
		if(joystickGetDigital(1, 5, JOY_UP)){motorset_claw(127);}

		else if(joystickGetDigital(1, 5, JOY_DOWN)){
		  motorset_claw(-127); //cloase


		}

		else if(joystickGetDigital(2, 6, JOY_DOWN)){
		  motorset_claw(-127); //cloase

		}

		else if(joystickGetDigital(2, 6, JOY_UP)){
		  motorset_claw(127); //cloas
		}
		  else{
		      motorset_claw(0);}
*/

if(joystickGetDigital(1, 7, JOY_DOWN)){
	motorSet(winch, -127*winch_Dir);
}

else if(joystickGetDigital(1, 7, JOY_LEFT))
{
motorSet(winch, 127*winch_Dir);
	}

else if(joystickGetDigital(2, 7, JOY_LEFT))
{
motorSet(winch, 127*winch_Dir);
	}
else if(joystickGetDigital(2, 7, JOY_DOWN))
{
motorSet(winch, -127*winch_Dir);
	}

else {motorSet(winch, 0);}

		}
}
