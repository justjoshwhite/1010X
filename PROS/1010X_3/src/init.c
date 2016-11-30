#include "main.h"


void initializeIO() {
}

void initialize() {

  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, 1);
  lcdSetText(uart1, 1, "LCD Init");
  delay(40);

  encoderFR = encoderInit(encoderFR_TOP, encoderFR_BOT, 1);
  encoderFL = encoderInit(encoderFL_TOP, encoderFL_BOT, 0);
  encoderBL = encoderInit(encoderBL_TOP, encoderBL_BOT, 1);
  encoderBR = encoderInit(encoderBR_TOP, encoderBR_BOT, 1);
  gyro =  gyroInit (gyroport, 196);
  analogCalibrate(accel_x);
  analogCalibrate(accel_y);
  analogCalibrate(gyroport);


  lcdClear(uart1);
  lcdSetText(uart1, 1, "Senseor Init");
  delay(600);


}
