#include "main.h"
#include "API.h"


void drivestraight(int direction, int totdist, int timeout, int acceldist, int deacceldist, int maxpower = 100, int minpower = 30, float kdrift = 0.5)
{
  encoderReset(encoderL);
  encoderReset(encoderR);
  int encoderaverage;
  long starttime = millis();
  int drift;
  int accel;
  int netpower = maxpower-minpower;

  while(encoderaverage < abs(totdist))
  {
    encoderaverage = abs((encoderGet(encoderL)+encoderGet(encoderR))/2);
    drift = encoderGet(encoderL)-encoderGet(encoderR);

    if(abs(encoderaverage) <= acceldist)
      {accel = abs(encoderaverage/acceldist)*netpower;} //accel - fraction of value
    else if (abs(encoderaverage) >= deacceldist)
      {accel = ((totdist-abs(encoderaverage))/(totdist-deacceldist))*netpower;}//deaccel - fraction of value
    else
      {accel = netpower;}

int powerL = direction*motorcap(minpower+accel)-(kdrift*drift);
int powerR = direction*motorcap(minpower+accel)+(kdrift*drift);

motorSet(DriveBL, DriveBL_Dir*powerL);
motorSet(DriveFL, DriveFL_Dir*powerL);
motorSet(DriveFR, DriveFR_Dir*powerR);
motorSet(DriveBR, DriveBR_Dir*powerR);

    long currenttime = millis();
    if((currenttime-starttime)>timeout)
      {break;}
  delay(25);

    }
}

void turnexact(int direction, int tardegrees, int timeout, int accelang, int deaccelang, int maxpower = 100, int kturn = 0.5){

gyroReset(gyro1);
int curdegrees;
int motorpower;
long starttime = millis();

while (abs(curdegrees) < tardegrees){
  curdegrees = abs(gyroGet(gyro1));

  if(curdegrees <= accelang)
  {motorpower = maxpower*(curdegrees/accelang);}
  else if(curdegrees >= deaccelang)
  {motorpower = maxpower*((tardegrees-curdegrees)/(tardegrees-deaccelang));}
  else
  {motorpower = maxpower;}

  int powerL = -direction*motorpower*kturn;
  int powerR = direction*motorpower*kturn;
//go fuck yourself
  motorSet(DriveBL, DriveBL_Dir*powerL);
  motorSet(DriveFL, DriveFL_Dir*powerL);
  motorSet(DriveFR, DriveFR_Dir*powerR);
  motorSet(DriveBR, DriveBR_Dir*powerR);

  long currenttime = millis();
  if((currenttime-starttime) > timeout)
    {break;}
delay(25);
  }
}
