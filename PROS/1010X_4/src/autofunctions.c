#include "main.h"
#include "autofunctions.h"
#include "clawarmextern.h"
#include <math.h>
#include <stdlib.h>


int motorcap_int (int value){
  if (value >= 127)
    return 127;
  else if (value <= -127)
    return -127;
  else
    return value;
  }

//1  = forward
//2  = right
//3 = back
//4 = left
//5 = Forward-Right
//6 = Backward-Right
//7 = Backward-Left
//8 = Forward-Left

// deaccel_dist is 1-fractoin (i.e 0.8)
void newdrive(int direction, int total_tics, int target_speed, int minpower, float ka, float accel_dist, float kd, float deaccel_dist, float kskew, int timeout){
  int encoder_average = 0;
  int power_FL;
  int power_FR;
  int power_BL;
  int power_BR;
  int accel_adjust;

  int tics_FL;
  int tics_FR;
  int tics_BL;
  int tics_BR;

  int ime_value_BL;
  int ime_value_BR;

  int timestart = millis();

  encoderReset(encoderFL);
  encoderReset(encoderFR);
  imeReset(ime_BL);
  imeReset(ime_BR);

  int target_speed_original = target_speed;

  delay(50);

  while((encoder_average < total_tics) && ( (millis() - timestart) < timeout)){

    encoderReset(encoderFL);
    encoderReset(encoderFR);
    imeReset(ime_BL);
    imeReset(ime_BR);

    delay(30);

    if(encoder_average < total_tics*accel_dist)
      {target_speed = ((total_tics*accel_dist) - encoder_average)*ka;}
    else if(encoder_average > total_tics*deaccel_dist)
        {target_speed = ((encoder_average - (total_tics*deaccel_dist))*kd);}
    else
        {target_speed = target_speed_original;}

    imeGet(ime_BL, &ime_value_BL);
    imeGet(ime_BR, &ime_value_BR);

    tics_FL = abs(encoderGet(encoderFL));
    tics_FR = abs(encoderGet(encoderFR));
    tics_BL = abs(ime_value_BL*(360/261.333));
    tics_BR = abs(ime_value_BR*(360/261.333));

    encoder_average = encoder_average + ((tics_FL + tics_FR + tics_BL + tics_BR)/4);

    int error_FL = target_speed - tics_FL;
    int error_FR = target_speed - tics_FR;
    int error_BL = target_speed - tics_BL;
    int error_BR = target_speed - tics_BR;

    lcdPrint(uart1, 1, "tFL%d tFR%d", tics_FL, tics_FR);
    lcdPrint(uart1, 2, "tBL%d tBR%d", tics_BL, tics_BR);


    switch (direction) {
      case 1: //forward - north
        power_FL = ((minpower + (error_FL*kskew)));
        power_FR = ((minpower + (error_FR*kskew)));
        power_BL = ((minpower + (error_BL*kskew)));
        power_BR = ((minpower + (error_BR*kskew)));

      break;
      case 2://right - east
        power_FL = (minpower + (error_FL*kskew));
        power_FR = (-1*(minpower + (error_FR*kskew)));
        power_BL = (-1*(minpower + (error_BL*kskew)));
        power_BR = ((minpower + (error_BR*kskew)));
      break;
      case 3://backwards - south
        power_FL = -1*(minpower + (error_FL*kskew));
        power_FR = -1*(minpower + (error_FR*kskew));
        power_BL = -1*(minpower + (error_BL*kskew));
        power_BR = -1*(minpower + (error_BR*kskew));
      break;
      case 4://left - west
        power_FL = -1*(minpower + (error_FL*kskew));
        power_FR = (minpower + (error_FR*kskew));
        power_BL = (minpower + (error_BL*kskew));
        power_BR = -1*(minpower + (error_BR*kskew));
      break;
      case 5://forward right - northeast
        power_FL = (minpower + (error_FL*kskew));
        power_FR = 0*(minpower + (error_FR*kskew));
        power_BL = 0*(minpower + (error_BL*kskew));
        power_BR = (minpower + (error_BR*kskew));
      break;
      case 6://backwards right - south east
        power_FL = 0*(minpower + (error_FL*kskew));
        power_FR = -1*(minpower + (error_FR*kskew));
        power_BL = -1*(minpower + (error_BL*kskew));
        power_BR = 0*(minpower + (error_BR*kskew));
      break;
      case 7:// backwards left - south west
        power_FL = -1*(minpower + (error_FL*kskew));
        power_FR = 0*(minpower + (error_FR*kskew));
        power_BL = 0*(minpower + (error_BL*kskew));
        power_BR = -1*(minpower + (error_BR*kskew));
      break;
      case 8: // forwards left - northwest
        power_FL = 0*(minpower + (error_FL*kskew));
        power_FR = (minpower + (error_FR*kskew));
        power_BL = (minpower + (error_BL*kskew));
        power_BR = 0*(minpower + (error_BR*kskew));
      break;
      default:
      power_FL = 127;
      power_BL = 127;
      power_BR = 127;
      power_FR = 127;
      break;
      }
    motorSet(DriveFL, DriveFL_Dir*power_FL);
    motorSet(DriveFR, DriveFR_Dir*power_FR);
    motorSet(DriveBL, DriveBL_Dir*power_BL);
    motorSet(DriveBR, DriveBR_Dir*power_BR);
  }

  motorSet(DriveFL, 0);
  motorSet(DriveFR, 0);
  motorSet(DriveBL, 0);
  motorSet(DriveBR, 0);
}

void newturn(int direction, int target_degrees, int target_speed, int minpower, float ka, float accel_dist, float kd, float deaccel_dist, float kskew, int timeout){
  int current_degrees = 0;
  int power_FL;
  int power_FR;
  int power_BL;
  int power_BR;
  int accel_adjust;

  int ime_value_BL;
  int ime_value_BR;

  int timestart = millis();

  gyroReset(gyro);
  int target_speed_original = target_speed;

  while((current_degrees < target_degrees) && ((millis()-timestart) < timeout)) {
      encoderReset(encoderFL);
      encoderReset(encoderFR);
      imeReset(ime_BL);
      imeReset(ime_BR);

      delay(30);

      current_degrees = current_degrees+abs(gyroGet(gyro));

      if(current_degrees < target_degrees*accel_dist)
        {target_speed = ((target_degrees*accel_dist) - current_degrees)*-ka;}
      else if(current_degrees > target_degrees*deaccel_dist)
        {target_speed = ((current_degrees - (target_degrees*deaccel_dist))*-kd);}
      else {
        target_speed = target_speed_original;}

      imeGet(ime_BL, &ime_value_BL);
      imeGet(ime_BR, &ime_value_BR);

      int tics_FL = abs(encoderGet(encoderFL));
      int tics_FR = abs(encoderGet(encoderFR));
      int tics_BL = abs(ime_value_BL*(360/261.333));
      int tics_BR = abs(ime_value_BR*(360/261.333));

      int error_FL = target_speed - tics_FL;
      int error_FR = target_speed - tics_FR;
      int error_BL = target_speed - tics_BL;
      int error_BR = target_speed - tics_BR;

      power_FL = direction*(minpower + (error_FL*kskew));
      power_FR = -direction*(minpower + (error_FR*kskew));
      power_BL = direction*(minpower + (error_BL*kskew));
      power_BR = -direction*(minpower + (error_BR*kskew));

      motorSet(DriveFL, DriveFL_Dir*power_FL);
      motorSet(DriveFR, DriveFR_Dir*power_FR);
      motorSet(DriveBL, DriveBL_Dir*power_BL);
      motorSet(DriveBR, DriveBR_Dir*power_BR);

    }
    motorSet(DriveFL, 0);
    motorSet(DriveFR, 0);
    motorSet(DriveBL, 0);
    motorSet(DriveBR, 0);
}

void checkdump(int clawrelease){

  int ultra_limit = 40;

  if (ultrasonicGet(ultrasonic) > ultra_limit){
      newdrive(EAST, 150, DEFAULT_drive_target_speed, DEFAULT_drive_minpower, DEFAULT_drive_ka, DEFAULT_drive_accel_dist, DEFAULT_drive_kd, DEFAULT_drive_deaccel_dist, DEFAULT_drive_kskew, DEFAULT_drive_timeout);}

  arm_target_L = ARM_MAX_L;
  arm_target_R = ARM_MAX_R;
  while(((abs(analogRead(potarmL)+potarmL_direction)+abs(analogRead(potarmR)+potarmR_direction))/2) < clawrelease){ delay(50);}
  claw_target = CLAW_PARALLEL;
  while (abs(analogRead(potclaw)+potclaw_direction) < CLAW_PARALLEL) {delay(50);}
  delay(100);
  arm_target_L = ARM_GROUND_L;
  arm_target_R = ARM_GROUND_R;
  claw_target = CLAW_MAX;
  newdrive(WEST, 150, DEFAULT_drive_target_speed, DEFAULT_drive_minpower, DEFAULT_drive_ka, DEFAULT_drive_accel_dist, DEFAULT_drive_kd, DEFAULT_drive_deaccel_dist, DEFAULT_drive_kskew, DEFAULT_drive_timeout);
  delay(100);
}
