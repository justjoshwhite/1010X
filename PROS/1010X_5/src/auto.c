
#include "main.h"
#include "lcdfunctions.h"
#include "autofunctions.h"
#include "util.h"
#include "claw.h"
#include "arm.h"

void autonomous() {

  TaskHandle autolcd_task = taskCreate(autolcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle claw_task = taskCreate(clawtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle arm_task = taskCreate(armtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

switch (myauto) {

case 1:

  lcdPrint(uart1, 1, "Arm STart");
  delay(500);

  arm_target_global = 1000;
    lcdPrint(uart1, 1, "Arm UP");
  claw_release(100, 600);
    lcdPrint(uart1, 1, "Arm release");
  delay(4000);

  //turn_time(1, 100, 5, 500, 127, 5, 10);

break;

  case 2:
  drive_encoder(-1, 2000, 10000, 127, 50, 3, 0.2, 0.2);

  break;

  case 3:
turn_time(1, 100, 5, 500, 127, 5, 10);
  //drive_encoder(-1, 2000, 10000, 127, 50, 0.1, 0.2, 0.2);

  break;

  case 4:
    drive_encoder(-1, 2000, 10000, 127, 50, 3, 0.2, 0.2);

  break;

  case 5:
  drive_encoder(-1, 2000, 10000, 127, 50, 5, 0.3, 0.3);

  break;

  case 6:
  //nolag(10, 23, 15);
  //motorset_drive(15, 15);
  //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
  //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.15, 0.3);
  turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.1, 0.3);

  break;

  default:
  break;
      }

  //delay(20000);

}

/*
delay(1000);
claw_target_global = 140;
drive_gyro(-1, 1000, 10000, 127, 70, 2, 0.15, 0.3);
delay(2000);
claw_target_global = 200;
drive_gyro(1, 700, 10000, 127, 70, 2, 0.15, 0.3);
arm_target_global = 1000;
drive_gyro(-1, 1530, 10000, 127, 50, 2, 0.15, 0.3);
claw_release(140, 800);
delay(1000);
arm_pos_global = 0;
turn_gyro(-1, 30, 10000, 127, 50, 0.2, 0.2);
drive_gyro(1, 1500, 10000, 127, 50, 2, 0.15, 0.3);
claw_target_global = 190;
delay(2000);
arm_pos_global = 220;
turn_gyro(1, 20, 10000, 127, 50, 0.2, 0.2);
arm_pos_global = 1000;
drive_gyro(-1, 1200, 10000, 127, 50, 2, 0.15, 0.3);
claw_release(130, 800);
delay(2000);
arm_pos_global = 0;
delay(2000);
//forward for 2nd cube
drive_gyro(1, 1200, 10000, 127, 50, 2, 0.15, 0.3);
claw_target_global = 200;
delay(2000);
drive_gyro(-1, 1280, 10000, 127, 50, 2, 0.15, 0.3);
arm_pos_global = 950;
claw_release(130, 800);
delay(2000);
*/
