#include "main.h"

void initializeIO() {}

void initialize() {

  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, 1);

  encoder_R = encoderInit(encoder_R_TOP, encoder_R_BOT, 1);
  encoder_L = encoderInit(encoder_L_TOP, encoder_L_BOT, 0);
  encoder_ARM = encoderInit(encoder_ARM_TOP, encoder_ARM_BOT, 1);
  encoder_CLAW = encoderInit(encoder_CLAW_TOP, encoder_CLAW_BOT, 0);

  gyro =  gyroInit (gyroport, 196);

  lcdClear(uart1);
  lcdSetText(uart1, 1, "CALIBRATE:");
  lcdSetText(uart1, 2, "DO NOT MOVE");

  /*
  analogCalibrate (accel_x);
  analogCalibrate (accel_y);
  analogCalibrate (gyroport);
  */

  lcdClear(uart1);
  lcdSetText(uart1, 1, "Ready");
  delay(60);


}
