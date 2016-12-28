#include "main.h"
#include "util.h"
#include "autofunctions.h"

void nolag(int demo_tics, int demo_movepower, int demo_holdpower){

  int tics = demo_tics;
  int move_power = demo_movepower;
  int hold_power = demo_holdpower;

  int timeout = 5000;
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

    if(tics < abs(encoderGet(encoder_L))){
      powerL = move_power;}
    else{
      powerL = hold_power;
      L_done = true;}

    if(tics < abs(encoderGet(encoder_R))){
      powerR = move_power;}
    else{
      powerR = hold_power;
      R_done = true;}

      motorset_drive(powerL, powerR);
      delay(20);
    }

  /*
  while(net_time < timeout){

    net_time = millis() - start_time;
    //if(net_time > timeout){break;}

    if(tics < abs(encoderGet(encoder_L))){
      powerL = move_power;}
    else{
      powerL = hold_power;
      L_done = true;}

    if(tics < abs(encoderGet(encoder_R))){
      powerR = move_power;}
    else{
      powerR = hold_power;
      R_done = true;}

      motorset_drive(powerL, powerR);
      delay(20);
      }
    */
  }

void drive_encoder(int direction, int target, int timeout, int maxpower, int minpower, float kdrift_encoder, float kaccel, float kdeaccel){

  int netpower = maxpower - minpower;

  float boost;

  int breakpower = 20;

  encoderReset(encoder_L);
  encoderReset(encoder_R);
  gyroReset(gyro);

  int encoderaverage = 0;

  int start_time = millis();
  int net_time;

  //  nolag();

  while(abs(encoderaverage) < target && net_time < timeout){

    //lcdPrint(uart1, 1, "enL=%d", encoderGet(encoder_L));
    //lcdPrint(uart1, 2, "enR=%d", encoderGet(encoder_R));

    net_time  = millis() - start_time;

    encoderaverage = (encoderGet(encoder_L)+encoderGet(encoder_R)/2);

    //int gyro_error = gyroGet(gyro); //clockwise -- subtract from L side

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

void drive_gyro(int direction, int target, int timeout, int maxpower, int minpower, float kdrift_gyro, float kaccel, float kdeaccel){

    int netpower = maxpower - minpower;

    float boost;

    int breakpower = 15;

    encoderReset(encoder_L);
    encoderReset(encoder_R);
    gyroReset(gyro);

    int encoderaverage = 0;

    int start_time = millis();
    int net_time = 0;

    //  nolag();

    while(abs(encoderaverage) < target && net_time < timeout){

      //lcdPrint(uart1, 1, "enL=%d", encoderGet(encoder_L));
      //lcdPrint(uart1, 2, "enR=%d", encoderGet(encoder_R));

      net_time  = millis() - start_time;

      encoderaverage = (encoderGet(encoder_L)+encoderGet(encoder_R)/2);

      float gyro_error = gyro_read(gyro, 300); //clockwise -- subtract from L side

      //int encoder_error = encoderGet(encoder_L) - encoderGet(encoder_R); //subtract from L side

      //accel/deaccel constants
      if(encoderaverage < target*kaccel){

        boost = (encoderaverage)/(target*kaccel);}
      else if (encoderaverage > (target - (target*kdeaccel))){
        boost = ((target-encoderaverage)/(target*kdeaccel));}
      else{
        boost = 1;}

      int power_L = motorcap(minpower + boost*netpower) + gyro_error*kdrift_gyro;
      int power_R = motorcap(minpower + boost*netpower) - gyro_error*kdrift_gyro;

      //int power_L = motorcap(minpower + boost*netpower) - gyro_error*kdrift_gyro;
      //int power_R = motorcap(minpower + boost*netpower) + gyro_error*kdrift_gyro;

      motorset_drive(direction*power_L, direction*power_R);
      delay(20);
      }
      //brake
      motorset_drive(-direction*breakpower, -direction*breakpower);

    }



void turn_gyro(int direction, int target, int timeout, int maxpower, int minpower, float kaccel, float kdeaccel){

  int netpower = maxpower - minpower;
  float boost = 0;

  int start_time = millis();
  int net_time = 0;


  int breakpower = 15;
  //encoderReset(encoder_L);
  //encoderReset(encoder_R);
  gyroReset(gyro);

  int gyroaverage = abs(gyro_read(gyro, 300));

  while(gyroaverage < target && net_time < timeout){

      net_time  = millis() - start_time;

      gyroaverage = abs(gyro_read(gyro, 300));

      if(gyroaverage < target*kaccel){
        boost = (gyroaverage)/(target*kaccel);}
      else if (gyroaverage > (target - target*kdeaccel)){
        boost = (target - gyroaverage)/(target*kdeaccel);}
      else{
        boost = 1;}

        int power_L = motorcap(minpower + boost*netpower);
        int power_R = motorcap(minpower + boost*netpower);

        //int power_L = motorcap(minpower + boost*netpower) - gyro_error*kdrift_gyro;
        //int power_R = motorcap(minpower + boost*netpower) + gyro_error*kdrift_gyro;

        motorset_drive(direction*power_L, -direction*power_R);
        delay(20);
        }
    motorset_drive(direction*breakpower, -direction*breakpower);
}
