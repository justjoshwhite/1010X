#include "main.h"

//1 = forwards
//2 = right
//3 = back
//4 = left
//5 = Forward-Right
//6 = Backward-Right
//7 = Backward-Left
//8 = Forward-Left
void drivestraight(int direction, int total_tics, int target_speed, int power_default){

int total_dist = 0;
float kp = 0.5;
int power_FL;
int power_FR;
int power_BL;
int power_BR;
int last_tics_FL = 0;
int last_tics_FR = 0;
int last_tics_BL = 0;
int last_tics_BR = 0;

int ime_value_BL;
int ime_value_BR;

encoderReset(encoderFL);
encoderReset(encoderFR);
imeReset(ime_BL);
imeReset(ime_BR);

while(total_dist < total_tics){

    imeGet(ime_BL, &ime_value_BL);
    imeGet(ime_BR, &ime_value_BR);

    int tics_FL = abs(encoderGet(encoderFL));
    int tics_FR = abs(encoderGet(encoderFR));
    int tics_BL = abs(ime_value_BL*(360/261.333));
    int tics_BR = abs(ime_value_BR*(360/261.333));

    int delta_tics_FL = tics_FL - last_tics_FL;
    int delta_tics_FR = tics_FR - last_tics_FR;
    int delta_tics_BL = tics_BL - last_tics_BL;
    int delta_tics_BR = tics_BR - last_tics_BR;

    last_tics_FL = tics_FL;
    last_tics_FR = tics_FR;
    last_tics_BL = tics_BL;
    last_tics_BR = tics_BR;

    int error_FL = target_speed - delta_tics_FL;
    int error_FR = target_speed - delta_tics_FR;
    int error_BL = target_speed - delta_tics_BL;
    int error_BR = target_speed - delta_tics_BR;

total_dist =  abs(( encoderGet(encoderFL) + encoderGet(encoderFR) + (imeGet(ime_BL, &tics_BL)*(360/261.333)) + (imeGet(ime_BR, &tics_BR)*(360/261.333)))/4);

lcdPrint(uart1, 1, "DBL=%d", error_BL);
lcdPrint(uart1, 2, "DFR=%d", error_FL);

switch (direction) {
  case 1: //forward - north
    power_FL = (power_default + (error_FL*kp));
    power_FR = (power_default + (error_FR*kp));
    power_BL = (power_default + (error_BL*kp));
    power_BR = (power_default + (error_BR*kp));

    power_FL = 127;
    power_BL = 127;
    power_BR = 127;
    power_FR = 127;
  break;
  case 2://right - east
    power_FL = (power_default + (error_FL*kp));
    power_FR = -1*(power_default + (error_FR*kp));
    power_BL = -1*(power_default + (error_BL*kp));
    power_BR = (power_default + (error_BR*kp));
  break;
  case 3://backwards - south
    power_FL = -1*(power_default + (error_FL*kp));
    power_FR = -1*(power_default + (error_FR*kp));
    power_BL = -1*(power_default + (error_BL*kp));
    power_BR = -1*(power_default + (error_BR*kp));
  break;
  case 4://left - west
    power_FL = -1*(power_default + (error_FL*kp));
    power_FR = (power_default + (error_FR*kp));
    power_BL = (power_default + (error_BL*kp));
    power_BR = -1*(power_default + (error_BR*kp));
  break;
  case 5://forward right - northeast
    power_FL = (power_default + (error_FL*kp));
    power_FR = 0*(power_default + (error_FR*kp));
    power_BL = 0*(power_default + (error_BL*kp));
    power_BR = (power_default + (error_BR*kp));
  break;
  case 6://backwards right - south east
    power_FL = 0*(power_default + (error_FL*kp));
    power_FR = -1*(power_default + (error_FR*kp));
    power_BL = -1*(power_default + (error_BL*kp));
    power_BR = 0*(power_default + (error_BR*kp));
  break;
  case 7:// backwards left - south west
    power_FL = -1*(power_default + (error_FL*kp));
    power_FR = 0*(power_default + (error_FR*kp));
    power_BL = 0*(power_default + (error_BL*kp));
    power_BR = -1*(power_default + (error_BR*kp));
  break;
  case 8: // forwards left - northwest
    power_FL = 0*(power_default + (error_FL*kp));
    power_FR = (power_default + (error_FR*kp));
    power_BL = (power_default + (error_BL*kp));
    power_BR = 0*(power_default + (error_BR*kp));
  break;
  default:
  break;
}

motorSet(DriveFL, DriveFL_Dir*power_FL);
motorSet(DriveFR, DriveFR_Dir*power_FR);
motorSet(DriveBL, DriveBL_Dir*power_BL);
motorSet(DriveBR, DriveBR_Dir*power_BR);

delay(30);
  }
motorSet(DriveFL, 0);
motorSet(DriveFR, 0);
motorSet(DriveBL, 0);
motorSet(DriveBR, 0);
}


void turnexact(int direction, int target_degrees, int target_speed, int power_default){

  int total_degrees = 0;
  float kp = 0.5;
  int power_FL;
  int power_FR;
  int power_BL;
  int power_BR;

  while(total_degrees < target_degrees){
      encoderReset(encoderFL);
      encoderReset(encoderFR);
      imeReset(ime_BL);
      imeReset(ime_BR);

      int tics_FL = abs(encoderGet(encoderFL));
      int tics_FR = abs(encoderGet(encoderFR));
      int tics_BL = abs(imeGet(ime_BL, &tics_BL)*(360/261.333));
      int tics_BR = abs(imeGet(ime_BR, &tics_BR)*(360/261.333));

      int error_FL = target_speed - tics_FL;
      int error_FR = target_speed - tics_FR;
      int error_BL = target_speed - tics_BL;
      int error_BR = target_speed - tics_BR;

      total_degrees = abs(gyroGet(gyro));

  power_FL = direction*(power_default + (error_FL*kp));
  power_FR = -direction*(power_default + (error_FR*kp));
  power_BL = direction*(power_default + (error_BL*kp));
  power_BR = -direction*(power_default + (error_BR*kp));

  motorSet(DriveFL, DriveFL_Dir*power_FL);
  motorSet(DriveFR, DriveFR_Dir*power_FR);
  motorSet(DriveBL, DriveBL_Dir*power_BL);
  motorSet(DriveBR, DriveBR_Dir*power_BR);

  delay(30);
}
motorSet(DriveFL, 0);
motorSet(DriveFR, 0);
motorSet(DriveBL, 0);
motorSet(DriveBR, 0);
}
