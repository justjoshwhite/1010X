
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

  drive_stop(-1, 0, 127, 10, 1000);
/*
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
*/

break;


case -1: //Modified Programming skills

  delay(5);
  arm_target_global = 25;
  drive_encoder(-1, 850, 4000, 127, 60, 10, 0, 0.3);// was 800
  claw_target_global = 650;
  arm_target_global = 0;
  delay(1500);
  claw_target_global = 580;
  drive_encoder(1, 250, 2000, 127, 60, 10, 0, 0.3);
  claw_target_global = 780;

  delay(750);
    //fence dump 1
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(200);//adjust for fence timing
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1200
    delay(1400);

  arm_target_global = 0;
  claw_target_global = 525;
  //lock_encoder(2500, 3);
  delay(2500);
    drive_stop(-1, 2, 127, 10, 1000);
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
    delay(500);
  drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
  delay(500);
  claw_target_global = 750;
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
    drive_stop(-1, 5, 127, 10, 1000);
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
    delay(500);
  drive_encoder(1, 1200, 4000, 127, 60, 10, 0, 0.3);
  delay(500);
  claw_target_global = 750;
  delay(1200);
    //fence dump 3
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0);// was 1300
    delay(1400);

    //tuned
  arm_target_global = 0;
  claw_target_global = 630;
  delay(1500);
    drive_stop(-1, 0, 127, 10, 1000);
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
    delay(500);
  drive_encoder(1, 100, 4000, 90, 40, 5, 0, 0.4);
  delay(1000);
  turn_pid(1, 140, 127, 7, 0, 22, 0, 1000);
  delay(1000);
  drive_stop(1, 0, 127, 10, 5000);

  //drive_encoder(1, 2300, 5000, 90, 60, 10, 0, 0.2);
  // possible switch to drive encoder;

  claw_target_global = 700;
  drive_encoder(-1, 100, 4000, 90, 60, 5, 0.1, 0.2);
  delay(200);
  arm_target_global = 38;
  delay(700);
  turn_pid(-1, 140, 127, 7, 0, 22, 0, 1000);
  delay(1000);
  //drive_encoder(1, 100, 4000, 90, 60, 10, 0.1, 0.2);
  //delay(1000);

    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(500); //tune for dump
    drive_encoder(-1, 300, 4000, 127, 60, 10, 0, 0);// was 1300
    delay(1400);

  //go for back cube + star
  arm_target_global = 0;
  claw_target_global = 580;
  delay(1500);
    turn_pid(1, 35, 127, 7, 0, 22, 0, 1000);
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
    //delay(500);
  drive_encoder(1, 1300, 4000, 127, 60, 10, 0, 0.3);
  delay(500);
  claw_target_global = 750;
  delay(1000);
    //fence dump
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);

    //turn for center

    arm_target_global = 0;
    claw_target_global = 580;
    delay(1500);
      drive_stop(-1, 0, 127, 10, 1000);
      //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
      delay(500);
    drive_encoder(1, 120, 800, 127, 60, 10, 0, 0.3);
    delay(500);
    turn_pid(-1, 80, 127, 7, 0, 22, 0, 1000);
    delay(700);
    drive_encoder(1, 1000, 800, 127, 60, 10, 0, 0.3);
    claw_target_global = 750;
    delay(1000);
    arm_target_global = 38;
    delay(100);
    turn_pid(1, 85, 127, 7, 0, 22, 0, 1000);
    delay(100);

    //dump middle cube
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(600); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);

    //for back three
    arm_target_global = 0;
    claw_target_global = 580;
    delay(1500);
      drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
      delay(500);
    drive_encoder(1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(500);
    claw_target_global = 750;
    delay(1000);

    //dump back three
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(600); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);

    //go for hang
    arm_target_global = 35;
    claw_target_global = 580;
    delay(1500);
    drive_encoder(1, 200, 4000, 127, 60, 10, 0, 0.3);
    delay(1000);
    turn_pid(-1, 150, 127, 7, 0, 22, 0, 1000);
    delay(1000);
    drive_encoder(-1, 1500, 4000, 127, 60, 10, 0, 0.3);
    delay(1000);
    drive_encoder(1, 50, 4000, 70, 60, 10, 0, 0.3);
    delay(500);
    drive_encoder(-1, 60, 4000, 70, 60, 10, 0, 0.3);
    delay(1000);

    arm_target_global = 145;
    delay(1500);
    drive_encoder(1, 30, 4000, 127, 60, 10, 0, 0.3);
    delay(700);
    arm_target_global = -10;
    claw_hang(30, -40);
    drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
    delay(10000);



break;

case 0:// mew programming skills

delay(5);
arm_target_global = 105;
claw_release2(95, 570, 5000);//was 580
drive_encoder(-1, 450, 4000, 127, 60, 11, 0, 0.3);// was 800 // kp was 10
delay(1500);

arm_target_global = 0;
delay(1500);

drive_encoder(1, 1800, 4000, 127, 60, 10, 0, 0.3);
claw_target_global = 800;
delay(700);
arm_target_global = 70;
delay(700);
drive_encoder(-1, 1350, 4000, 127, 60, 10, 0, 0.3);
delay(500);
//turn to dump
turn_pid(-1, 110, 127, 7, 0, 22, 0, 750);
delay(1000);

  // dump 1
  arm_target_global = 130;
  claw_release2(100, 600, 5000);
  delay(100);//adjust for fence timing
  drive_stop(-1, 0, 127, 14, 3500); // was 10 // 12.5
  //drive_encoder(-1, 1500, 3000, 127, 60, 10, 0, 0.3);// was 1200
  delay(1400);

//preload run 1
arm_target_global = 0;
claw_target_global = 525;
//lock_encoder(2500, 3);
delay(2500);
  drive_stop(-1, 2, 127, 10, 1000);
  //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
  delay(500);
drive_encoder(1, 1000, 4000, 127, 60, 8, 0, 0.3); // was 10
delay(500);
claw_target_global = 750;
delay(1000);
  //fence dump
  arm_target_global = 130;
  claw_release2(90, 600, 5000);
  delay(720); //tune for dump
  drive_stop(-1, 0, 127, 12.5, 3500); // was 8 /10
  //drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
  delay(1400);

//preload run 2
arm_target_global = 0;
claw_target_global = 525;
delay(2500);
  drive_stop(-1, 5, 127, 10, 1000);
  //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
  delay(500);
drive_encoder(1, 1100, 4000, 127, 60, 8, 0, 0.3);// was 10
delay(500);
claw_target_global = 750;
delay(1200);
  //fence dump
  arm_target_global = 130;
  claw_release2(90, 600, 5000);
  delay(600); //tune for dump
  drive_stop(-1, 0, 127, 12.5, 3500);//was 8 / 10
  //drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0);// was 1300
  delay(1400);

  //turn
arm_target_global = -10;
claw_target_global = 630;
delay(1500);
  drive_stop(-1, 0, 127, 10, 1000);
  //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
  delay(500);
drive_encoder(1, 120, 4000, 90, 40, 5, 0, 0.4);
delay(1000);
turn_pid(1, 133, 127, 7, 0, 22, 0, 1000);// was 140
delay(1000);
drive_encoder(1, 1600, 5000, 127, 60, 8, 0, 0.2);
// possible switch to drive encoder;

//3S fence dump
claw_target_global = 800;
delay(900);
arm_target_global = 38;
delay(700);
turn_pid(-1, 140, 127, 7, 0, 22, 0, 1000);
delay(1000);
//drive_encoder(1, 100, 4000, 90, 60, 10, 0.1, 0.2);
//delay(1000);

  arm_target_global = 130;
  claw_release2(90, 600, 5000);
  delay(1000); //tune for dump
  drive_stop(-1, 0, 127, 10, 1000);// was 1300
  delay(1000);

//center cube
arm_target_global = 70;
delay(1000);
turn_pid(-1, 20, 127, 5, 0, 16, 0, 1000);// was 7, 18 // further reduced
arm_target_global = 0;
claw_target_global = 520;
delay(1500);
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
  //delay(500);
drive_encoder(1, 400, 4000, 127, 60, 8, 0, 0.3);
delay(500);
claw_target_global = 790;
delay(1100);
  //fence dump
arm_target_global = 42;
delay(1000);
  turn_pid(1, 20, 127, 7, 0, 22, 0, 1000);
  arm_target_global = 130;
  claw_release2(90, 600, 5000);
  delay(700); //tune for dump
  drive_stop(-1, 0, 127, 8, 1000);
  //drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
  delay(1400);

  //move to side
  arm_target_global = -10; // was 0
  claw_target_global = 710;
  delay(1500);

  drive_encoder(1, 400, 2000, 127, 60, 10, 0, 0.3);
  delay(500);
  turn_pid(1, 130, 127, 7, 0, 22, 0, 1000);
  delay(700);
  drive_encoder(1, 1400, 2000, 127, 60, 8, 0, 0.3);//was 10 // was 1500
  turn_pid(-1, 110, 127, 7, 0, 22, 0, 1000);

  claw_target_global = 410;
  delay(1000);
  drive_encoder(1, 500, 2000, 127, 60, 8, 0, 0.3); // was 8
  delay(100);
  claw_target_global = 750;
  turn_pid(-1, 0, 127, 7, 0, 0, 0, 1200);//LOCK // noi kd was 22
  delay(200);
  drive_encoder(-1, 100, 2000, 127, 60, 8, 0, 0.3); // was 8
  claw_target_global = 400;
  delay(1000);
  drive_encoder(1, 100, 2000, 127, 60, 8, 0, 0.3); // was 8
  claw_target_global = 800;
  turn_pid(-1, 0, 127, 7, 0, 0, 0, 1200); //LOCK// no kd was 22
  delay(300);
  arm_target_global = 38;
  delay(100);
  //turn_pid(-1, 20, 127, 7, 0, 22, 0, 1000);
  delay(100);

  //dump cube + star
  arm_target_global = 130;
  claw_release2(90, 600, 5000);
  delay(200); //tune for dump
  drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
  delay(1400);

  //go for hang
  arm_target_global = 35;
  claw_target_global = 580;
  drive_stop(-1, 0, 127, 10, 2000);
  delay(1500);
  drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
  delay(1000);

  turn_pid(-1, 130, 127, 7, 0, 22, 0, 1200);
  delay(1000);
  drive_stop(-1, 0, 127, 10, 1750);
  delay(1000);
  drive_encoder(1, 400, 4000, 127, 60, 10, 0, 0.3);
  delay(1000);

  turn_pid(-1, 130, 127, 7, 0, 22, 0, 1200);
  delay(1000);
  drive_stop(-1, 0, 127, 10, 1750);
  delay(1000);
  drive_encoder(1, 400, 4000, 127, 60, 10, 0, 0.3);
  delay(1000);

  turn_pid(-1, 75, 127, 7, 0, 22, 0, 1200);
  delay(1000);
  drive_encoder(-1, 500, 4000, 127, 60, 10, 0, 0.3);
    delay(1000);
  drive_encoder(1, 50, 4000, 70, 60, 10, 0, 0.3);
  delay(500);
  drive_encoder(-1, 60, 4000, 70, 60, 10, 0, 0.3);
  delay(1000);

  arm_target_global = 145;
  delay(1500);
  drive_encoder(1, 30, 4000, 127, 60, 10, 0, 0.3);
  delay(700);
  arm_target_global = -10;
  claw_hang(30, -40);
  drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
  delay(10000);





break;
case 1: // AUTO 1 - CUBE LEFT

  delay(5);

  arm_target_global = 50;
  claw_release2(10, 600, 2500);
  drive_encoder(-1, 2150, 4000, 127, 60, 10, 0, 0.2);
  delay(100);
  turn_pid(-1, 50, 127, 7, 0, 22, 0, 750);
  //delay(500);
  arm_target_global = 0;
  claw_target_global = 570;
  delay(750);
  drive_encoder(1, 100, 1000, 127, 60, 10, 0, 0.2);
  claw_target_global = 790;

  delay(750);
    //fence dump 1
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(700);//adjust for fence timing
    drive_encoder(-1, 200, 1000, 127, 60, 10, 0, 0.3);// was 1200
    delay(900);

  arm_target_global = 0;
  claw_target_global = 500;
  //lock_encoder(2500, 3);
  delay(1500);
    //drive_stop(-1, 2, 127, 10);
    //drive_stop(-1, 0, 127, 10, 600); // taken out
    //drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
    //delay(200);
  drive_encoder(1, 1350, 4000, 127, 60, 10, 0, 0.3);
  //delay(500);
  claw_target_global = 750;
  delay(1000);
  arm_target_global = 20;
  delay(750);
    //fence dump 2
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);


    arm_target_global = 0;
    claw_target_global = 500;
    //lock_encoder(2500, 3);
    delay(2500);
      //drive_stop(-1, 2, 127, 10);
      drive_encoder(-1, 100, 800, 127, 60, 10, 0, 0.3);
      delay(500);
    drive_encoder(1, 1000, 4000, 127, 60, 10, 0, 0.3);
    delay(500);
    claw_target_global = 750;
    delay(1000);
      //fence dump 2
      arm_target_global = 130;
      claw_release2(90, 600, 5000);
      delay(100); //tune for dump
      drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
      delay(1400);

break;

case 2: // CUBE R


break;

case 3:// BACK -L
delay(5);
arm_target_global = 105;
claw_release2(95, 570, 5000);//was 580
drive_encoder(-1, 450, 4000, 127, 60, 11, 0, 0.3);// was 800 // kp was 10
delay(1500);

arm_target_global = 0;
delay(1500);

drive_encoder(1, 1700, 4000, 127, 60, 10, 0, 0.3);
claw_target_global = 800;
delay(700);
arm_target_global = 70;
delay(700);
drive_encoder(-1, 1250, 4000, 127, 60, 10, 0, 0.3);
delay(500);
//turn to dump
turn_pid(1, 110, 127, 7, 0, 22, 0, 750);
delay(1000);

  // dump 1
  arm_target_global = 130;
  claw_release2(100, 600, 5000);
  delay(100);//adjust for fence timing
  drive_stop(-1, 0, 127, 12.5, 3500);
  //drive_encoder(-1, 1500, 3000, 127, 60, 10, 0, 0.3);// was 1200
  delay(1400);


/* // old back L code
  delay(5);
  arm_target_global = 25;
  claw_release2(10, 600, 2500);
  delay(1000);
  arm_target_global = 0;
  delay(700);
  drive_encoder(1, 1500, 4000, 127, 60, 10, 0, 0.3);
  claw_target_global = 780;
  delay(700);
  arm_target_global = 20;
  delay(700);
  drive_encoder(-1, 1600, 4000, 127, 60, 10, 0, 0.3);
  delay(500);

  turn_pid(1, 130, 127, 7, 0, 22, 0, 750);
  delay(500);

  delay(1000);
    //fence dump 2
    arm_target_global = 130;
    claw_release2(90, 600, 5000);
    delay(100); //tune for dump
    drive_encoder(-1, 1300, 4000, 127, 60, 10, 0, 0.3);// was 1300
    delay(1400);
*/

break;

case 4: // Back -  R

delay(5);
arm_target_global = 105;
claw_release2(95, 570, 5000);//was 580
drive_encoder(-1, 450, 4000, 127, 60, 11, 0, 0.3);// was 800 // kp was 10
delay(1500);

arm_target_global = 0;
delay(1500);

drive_encoder(1, 1700, 4000, 127, 60, 10, 0, 0.3);
claw_target_global = 800;
delay(700);
arm_target_global = 70;
delay(700);
drive_encoder(-1, 1250, 4000, 127, 60, 10, 0, 0.3);
delay(500);
//turn to dump
turn_pid(-1, 110, 127, 7, 0, 22, 0, 750);
delay(1000);

  // dump 1
  arm_target_global = 130;
  claw_release2(100, 600, 5000);
  delay(100);//adjust for fence timing
  drive_stop(-1, 0, 127, 10, 3500);
  //drive_encoder(-1, 1500, 3000, 127, 60, 10, 0, 0.3);// was 1200
  delay(1400);


break;

case 5:

break;

case 6:

break;

case 7:

break;
case 8:
break;

default:
break;
      }



}
