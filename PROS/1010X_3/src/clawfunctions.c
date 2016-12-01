#include "main.h"

void drive_clawcontrol (void *ignore)
{
  int clawpos;
  int power_L;
  int power_R;

  int clawdiff;
  int lastdiff;

  float k_proportion = 0.18;
  int proportion;

  float k_integral = 0;
  int integral_activezone = 100;
  int integral;

  float k_derivative = 0;
  int derivative;
  int deaccel_delay = 100;

  clawtarget = analogRead(potclaw);

  bool p_or_d = true;
  int timeoutlcd = 50;
  lcdClear(uart1);

  while(true){

    if(p_or_d == true){
        if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
          k_proportion = k_proportion + 0.01;
          lcdSetText(uart1, 1, "wait");
              delay(timeoutlcd);
    }
        else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        k_proportion = k_proportion - 0.01;
        lcdSetText(uart1, 1, "wait");
              delay(timeoutlcd);
    }
        else if (lcdReadButtons(uart1) == LCD_BTN_CENTER){
        p_or_d = false;
        lcdSetText(uart1, 1, "wait");
        delay(500);

          }
        else {}
    }
    else{
        if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
          k_derivative = k_derivative + 0.1;
          lcdSetText(uart1, 1, "wait");
              delay(timeoutlcd);
    }
        else if (lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        k_derivative = k_derivative - 0.1;
        lcdSetText(uart1, 1, "wait");
              delay(timeoutlcd);
    }
          else if (lcdReadButtons(uart1) == LCD_BTN_CENTER){
            p_or_d = true;
            lcdSetText(uart1, 1, "wait");
            delay(500);

          }
      }

    lcdPrint(uart1, 1, "kp = %f", k_proportion);
    lcdPrint(uart1, 2, "kd = %f", k_derivative);



    //set value
    clawpos = analogRead(potclaw);

    //find error
    clawdiff = clawtarget - clawpos;

    //calculate P
    proportion = clawdiff;

    //intergral cap+calcualte I
    if(abs(clawdiff) < integral_activezone){
    integral = integral + (clawdiff);}
    else{integral = 0;}

    //calculate D
    derivative =  clawdiff - lastdiff;
    lastdiff = clawdiff;

    //calculate power values
    power_L = (derivative*k_derivative) + (integral*k_integral)+(proportion*k_proportion);
    power_R = (derivative*k_derivative) + (integral*k_integral)+(proportion*k_proportion);
/*
    if(joystickGetDigital(1,5,JOY_UP)){
      motorSet(ClawL, ClawL_Dir*127);
      motorSet(ClawR, ClawR_Dir*127);
      clawtarget = analogRead(potclaw);}

    else if(joystickGetDigital(1,5,JOY_DOWN)){
      motorSet(ClawL, ClawL_Dir*-127);
      motorSet(ClawR, ClawR_Dir*-127);
      clawtarget = analogRead(potclaw);}

    else {
      motorSet(ClawL, ClawL_Dir*power_L);
      motorSet(ClawR, ClawR_Dir*power_R);
        }
    */

int joystickclawrange = 30;

if(joystickGetDigital(1,5,JOY_UP)){
  motorSet(ClawL, ClawL_Dir*127);
  motorSet(ClawR, ClawR_Dir*127);
delay(deaccel_delay);
  clawtarget = analogRead(potclaw);}

else if(joystickGetDigital(1,5,JOY_DOWN)){
  motorSet(ClawL, ClawL_Dir*-127);
  motorSet(ClawR, ClawR_Dir*-127);
  delay(deaccel_delay);
  clawtarget = analogRead(potclaw);}

else if (joystickGetAnalog(2, 2) > joystickclawrange){
  motorSet(ClawL, ClawL_Dir*joystickGetAnalog(2, 2));
  motorSet(ClawR, ClawR_Dir*joystickGetAnalog(2, 2));
  delay(deaccel_delay);
  clawtarget = analogRead(potclaw);}
else if (joystickGetAnalog(2, 2) < -joystickclawrange){
  motorSet(ClawL, ClawL_Dir*joystickGetAnalog(2, 2));
  motorSet(ClawR, ClawR_Dir*joystickGetAnalog(2, 2));
  delay(deaccel_delay);
  clawtarget = analogRead(potclaw);}
else {
  motorSet(ClawL, ClawL_Dir*power_L);
  motorSet(ClawR, ClawR_Dir*power_R);
}
//lcdPrint(uart1, 1, "claw=%d" , clawpos);

  //delay
    delay(20);
    }
  }

void clawpresets(){
    if(joystickGetDigital(1,7,JOY_UP)){
      clawtarget = CLAW_MAX;}
    else if(joystickGetDigital(1,7,JOY_DOWN)){
      clawtarget = CLAW_CLOSED;}
    else if (joystickGetDigital(1,7,JOY_LEFT)){
      clawtarget = CLAW_SEMI_OPEN;
    }
    else if(joystickGetDigital(1,7,JOY_RIGHT)){}
    else{}
  }
