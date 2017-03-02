
#include "main.h"
#include "lcdfunctions.h"
#include "autofunctions.h"
#include "util.h"
#include "claw.h"
#include "arm.h"

#define DUMP_HIEGHT 600
void autonomous() {

  TaskHandle autolcd_task = taskCreate(autolcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle claw_task = taskCreate(clawtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle arm_task = taskCreate(armtask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

int motor_count= 1; // For motor test (auto -2)

switch (myauto) {
case -2: // MOTOR TEST


  delay(5);
  lcdPrint(uart1, 1, "MOTOR TEST START");
  delay(1000);

  while(motor_count <= 10){

    lcdPrint(uart1, 1, "MOTOR %d", motor_count);
    delay(500);
    motorSet(motor_count, 90);
    delay(250);
    motorSet(motor_count, 0);
    delay(500);
    motor_count = motor_count + 1;

  }

  lcdPrint(uart1, 1, "MOTOR TEST FINISH");
  delay(1000);

break;


case -1: //Old Programming skills


break;

case 0:// new programming skills

  delay(5);
  arm_target_global = 25;
  drive_encoder(-1, 800, 4000, 127, 60, 10, 0, 0.3);
  claw_target_global = 650;
  arm_target_global = 0;
  delay(1500);
  claw_target_global = 620;
  drive_encoder(1, 170, 4000, 127, 60, 10, 0, 0.3);
  claw_target_global = 750;
  //lock_encoder(1000, 8);
  delay(750);
    //fence dump 1
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100);//adjust for fence timing
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1200
    delay(1400);

  arm_target_global = 0;
  claw_target_global = 525;
  //lock_encoder(2500, 3);
  delay(2500);
  drive_stop(-1, 2, 127, 10);
  drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
  delay(500);
  claw_target_global = 725;
  delay(1000);
    //fence dump 2
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);

  arm_target_global = 0;
  claw_target_global = 525;
  delay(2500);
  //lock_encoder(2500, 3);
  drive_stop(-1, 2, 127, 10);
  drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
  delay(1000);
  claw_target_global = 725;
  delay(1000);
    //fence dump 3
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0);// was 1300
    delay(1400);

//tuned
  arm_target_global = 0;
  claw_target_global = 580;
  delay(1500);
  drive_stop(-1, 2, 127, 10);
  drive_encoder(1, 150, 4000, 90, 60, 5, 0.1, 0.2);
  delay(500);
  turn_pid(1, 140, 127, 7, 0, 22, 0, 750);
  drive_stop(1, 0, 127, 10);
  // possible switch to drive encoder;







break;
case 1: // AUTO 1 - CUBE LEFT


break;

case 2: // CUBE R


break;

case 3:// HANG -L


break;

case 4: // Hang - R

break;

case 5: //non hang L

break;

case 6: // nonhang R

break;

case 7: // none

break;
case 8:
break;

default:
break;
      }



}
