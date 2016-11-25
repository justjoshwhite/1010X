/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	while (1) {

int FLpower = joystickGetAnalog(1, 3) + joystickGetAnalog(1, 4) + joystickGetAnalog(1, 1);
int FRpower = joystickGetAnalog(1, 3) - joystickGetAnalog(1, 4) - joystickGetAnalog(1, 1);
int BLpower = joystickGetAnalog(1, 3) - joystickGetAnalog(1, 4) + joystickGetAnalog(1, 1);
int BRpower = joystickGetAnalog(1, 3) + joystickGetAnalog(1, 4) - joystickGetAnalog(1, 1);

		motorSet(DriveFL, DriveFL_Dir*FLpower);
		motorSet(DriveFR, DriveFR_Dir*FRpower);
		motorSet(DriveBL, DriveBL_Dir*BLpower);
		motorSet(DriveBR, DriveBR_Dir*BRpower);

		//Arm
		if(joystickGetDigital(1, 6, JOY_UP)){
			motorSet(ArmLT, ArmLT_Dir*127);
			motorSet(ArmLB, ArmLB_Dir*127);
			motorSet(ArmRT, ArmRT_Dir*127);
			motorSet(ArmRB, ArmRB_Dir*127);
		}
		else if (joystickGetDigital(1, 6, JOY_DOWN)){
			motorSet(ArmLT, ArmLT_Dir*-127);
			motorSet(ArmLB, ArmLB_Dir*-127);
			motorSet(ArmRT, ArmRT_Dir*-127);
			motorSet(ArmRB, ArmRB_Dir*-127);
		}
		else {
			motorSet(ArmLT,0);
			motorSet(ArmLB,0);
			motorSet(ArmRT,0);
			motorSet(ArmRB,0);
		}

		//Claw
		if(joystickGetDigital(1, 5, JOY_UP)){
			motorSet(ClawL, ClawL_Dir*127);
			motorSet(ClawR, ClawR_Dir*127);
		}
		else if (joystickGetDigital(1, 5, JOY_DOWN)){
			motorSet(ClawL, ClawL_Dir*-127);
			motorSet(ClawR, ClawR_Dir*-127);
		}
		else {
			motorSet(ClawL,0);
			motorSet(ClawR,0);
		}
		delay(20);
	}
}
