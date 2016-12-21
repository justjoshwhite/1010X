#include "main.h"
#include "util.h"
#include "autofunctions.h"

void nolag(){

  int tics = 3;
  int move_power = 20;
  int hold_power = 16;

  int timeout = 1000;
  int start_time = millis();
  int net_time;

  encoderReset(encoder_L);
  encoderReset(encoder_R);

  bool L_done = false;
  bool R_done = false;

  int powerL;
  int powerR;

  while(!L_done || !R_done){

    net_time = millis() - start_time;
    if(net_time > timeout){break;}

    if(tics < encoderGet(encoder_L)){
      powerL = move_power;}
    else{
      powerL = hold_power;
      L_done = true;}

    if(tics < encoderGet(encoder_R)){
      powerR = move_power;}
    else{
      powerR = hold_power;
      R_done = true;}

      motorset_drive(powerL, powerR);
      delay(20);
    }
  }


void drive(int direction, int target, int timeout){

  int maxpower = 127;
  int minpower = 40;
  int netpower = maxpower - minpower;

  float kdrift_encoder = 0.1;
  float kdrift_gyro = 0.1;

  float kaccel = 0.1;
  float kdeaccel = 0.1;
  float boost;


  int breakpower = 18;

  encoderReset(encoder_L);
  encoderReset(encoder_R);
  gyroReset(gyro);

  int encoderaverage = 0;

  int start_time = millis();
  int net_time;

  nolag();

  while(abs(encoderaverage) < target && net_time < timeout){

    lcdPrint(uart1, 1, "enL=%d", encoderGet(encoder_L));
    lcdPrint(uart1, 2, "enR=%d", encoderGet(encoder_R));

    net_time  = millis() - start_time;

    encoderaverage = (encoderGet(encoder_L)+encoderGet(encoder_R)/2);

    int gyro_error = gyroGet(gyro); //clockwise -- subtract from L side

    int encoder_error = encoderGet(encoder_L) - encoderGet(encoder_R); //subtract from L side

    //accel/deaccel constants

    if(encoderaverage < target*kaccel){
      boost = (encoderaverage)/(target*kaccel);}
    else if (encoderaverage > (target - target*kdeaccel)){
      boost = (encoderaverage)/(target - target*kdeaccel);}
    else{
      boost = 1;}

    int power_L = motorcap(minpower + boost*netpower) - encoder_error*kdrift_encoder;
    int power_R = motorcap(minpower + boost*netpower) + encoder_error*kdrift_encoder;

    //int power_L = motorcap(minpower + boost*netpower) - gyro_error*kdrift_gyro;
    //int power_R = motorcap(minpower + boost*netpower) + gyro_error*kdrift_gyro;

    motorset_drive(direction*power_L, direction*power_R);
    delay(20);
    }
    //brake
    motorset_drive(-direction*breakpower, -direction*breakpower);

  }

void pointturn(int direction, int target, int timeout){

  int maxpower = 127;
  int minpower = 40;
  int netpower = maxpower - minpower;

  float kaccel = 0.1;
  float kdeaccel = 0.1;
  float boost;
}
