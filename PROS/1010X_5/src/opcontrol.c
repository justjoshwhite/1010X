
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

		armpresets();
		clawpresets();


		}
}
