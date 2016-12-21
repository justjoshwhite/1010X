
#include "main.h"
#include "arm.h"
#include "claw.h"
#include "util.h"

void operatorControl() {

	lcdClear(uart1);

	TaskHandle claw_task = taskCreate (clawtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	TaskHandle arm_task = taskCreate (armtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	while (true) {

		delay(20);

		motorset_drive(joystickGetAnalog(1, 3), joystickGetAnalog(1,2));

		armpresets();
		clawpresets();

		lcdPrint(uart1, 1, "armpos: %d", arm_pos_global);
		lcdPrint(uart1, 2, "clawpos: %d", claw_pos_global);

		}
}
