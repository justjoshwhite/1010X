
#include "main.h"
#include "lcdfunctions.h"
#include "autofunctions.h"
#include "util.h"

void autonomous() {

  TaskHandle autolcd_task = taskCreate(autolcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

switch (myauto) {

  case 0:

  while (true){delay(30);}

  break;

  case 1:

    //nolag(10, 23, 15);
    //motorset_drive(15, 15);
    //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
    //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.05, 0.05);
    turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.05, 0.05);

  break;

  case 2:
  //nolag(10, 23, 15);
  //motorset_drive(15, 15);
  //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
  //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.1, 0.1);
  turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.1, 0.1);

  break;

  case 3:
  //nolag(10, 23, 15);
  //motorset_drive(15, 15);
  //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
  //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.2, 0.2);
  turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.2, 0.2);

  break;

  case 4:
  //nolag(10, 23, 15);
  //motorset_drive(15, 15);
  //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
  //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.3, 0.3);
  turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.3, 0.3);

  break;

  case 5:
  //nolag(10, 23, 15);
  //motorset_drive(15, 15);
  //drive_encoder(FORWARD, 1600, 10000, 127, 40, 0.1, 0.25, 0.25);
  //drive_gyro(FORWARD, 2000, 10000, 100, 40, 3.5, 0.5, 0.5);
  turn_gyro(CLOCKWISE, 900, 10000, 127, 40, 0.5, 0.5);

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
  delay(20000);

}
