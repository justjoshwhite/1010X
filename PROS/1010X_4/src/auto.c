#include "main.h"
#include "clawarmextern.h"
#include "LCDfunctions.h"
#include "autofunctions.h"
//#include "autoruns.h"

void autonomous() {

  TaskHandle armcontrol_auto = taskCreate(armcontrol, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle clawcontrol_auto = taskCreate(clawcontrol, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
//TaskHandle auto_lcd = taskCreate(autolcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

delay(250);

switch (myauto) {

  case 1:
  delay(250);

  claw_target = CLAW_PARALLEL;
  nolag(NORTH, 4, 25);
  newdrive(NORTH, 825, 30, 40, 15, 10, 10000);
  //drivehalt(NORTH, 750, 0.5);
  delay(750);
  nolag(WEST, 2, 30);
  newdrive(WEST, 800, 30, 40, 15, 10, 10000);
  //drivehalt(WEST, 1500, 0.5);
  arm_target_L = ARM_MID_L;
  arm_target_R = ARM_MID_R;
  delay(1000);
  arm_target_L = ARM_GROUND_L;
  arm_target_R = ARM_GROUND_R;
  claw_target = CLAW_MAX;
  delay(1000);
  newturn(CLOCKWISE, 900, 20, 40, 10, 8, 10000);
  nolag(NORTH, 4, 25);
  newdrive(NORTH, 200, 30, 40, 15, 10, 100000);
  drivehalt(NORTH, 750, 0.5);
  claw_target = CLAW_CLOSED;
  delay(1000);
  nolag(SOUTH, 4, 25);
  newdrive(SOUTH, 200, 30, 40, 15, 10, 100000);
  drivehalt(SOUTH, 750, 0.5);
  checkdump(2700, WEST);
  delay(500);








/*
    delay(250);
    claw_target = CLAW_PARALLEL;
    arm_target_L = ARM_LOWMID_L;
    arm_target_R = ARM_LOWMID_R;
    newdrive(NORTH, 850, DEFAULT_drive_target_speed, DEFAULT_drive_minpower, DEFAULT_drive_ka, DEFAULT_drive_accel_dist, DEFAULT_drive_kd, DEFAULT_drive_deaccel_dist, DEFAULT_drive_kskew, DEFAULT_drive_timeout);
    delay(500);
    newdrive(WEST, 900, 30, 40, 0.1, 0.5, 0.1, 0.5, DEFAULT_drive_kskew, DEFAULT_drive_timeout);
    delay(100);
    //newturn(CLOCKWISE, 10, DEFAULT_turn_target_speed, DEFAULT_turn_minpower, DEFAULT_turn_ka, DEFAULT_turn_accel_dist, DEFAULT_turn_kd, DEFAULT_turn_deaccel_dist, DEFAULT_turn_kskew, DEFAULT_turn_timeout);
    delay(500);
    newdrive(NORTH, 100, DEFAULT_drive_target_speed, DEFAULT_drive_minpower, DEFAULT_drive_ka, DEFAULT_drive_accel_dist, DEFAULT_drive_kd, DEFAULT_drive_deaccel_dist, DEFAULT_drive_kskew, DEFAULT_drive_timeout);
    arm_target_L = ARM_MID_L;
    arm_target_R = ARM_MID_R;
    delay(1500);
    arm_target_L = ARM_GROUND_L;
    arm_target_R = ARM_GROUND_R;
    claw_target = CLAW_MAX;
    newturn(COUNTER_CLOCKWISE, 300, DEFAULT_turn_target_speed, DEFAULT_turn_minpower, DEFAULT_turn_ka, DEFAULT_turn_accel_dist, DEFAULT_turn_kd, DEFAULT_turn_deaccel_dist, DEFAULT_turn_kskew, DEFAULT_turn_timeout);
    delay(10000);
*/

  break;
  case 2:
  lcdSetText(uart1, 1, "start");
  delay(500);
  nolag(NORTH, 5, 30);
  lcdSetText(uart1, 1, "nolag done");
  delay(500);
  newdrive(NORTH, 1200, 30, 45, 15, 10, 100000);
  lcdSetText(uart1, 1, "drive done");
  delay(500);
  //drivehalt(1500, 3);
  lcdSetText(uart1, 1, "halt done");
  delay(500);

  /*
    delay(500);
  newdrive(WEST, 900, DEFAULT_drive_target_speed, DEFAULT_drive_minpower, DEFAULT_drive_ka, DEFAULT_drive_accel_dist, DEFAULT_drive_kd, DEFAULT_drive_deaccel_dist, DEFAULT_drive_kskew, DEFAULT_drive_timeout);

*/
  break;
  case 3:
  //  drivehalt(1500, 3);


  break;
  case 4:
  //drivehalt(1500, 10);
  break;
  case 5:
//  drivehalt(1500, 0.5);
  break;
  case 6:
  break;
  case 7:
  case 8:
  break;

  default:
  break;
  }
}
