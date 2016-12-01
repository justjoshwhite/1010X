#include "main.h"
#include <math.h>

void drive_armcontrol (void *ignore)
{
  int armheight_L;
  int armheight_R;
  float power_L;
  float power_R;
  int armskew;
  float k_skew = 0.0;

  int armdiff_L;
  int armdiff_R;
  int lastdiff_L;
  int lastdiff_R;

  float k_proportion = 0.15;
  int proportion_L;
  int proportion_R;

  float k_integral = 0;
  int integral_activezone = 100;
  int integral_L;
  int integral_R;

  float k_derivative = 0;
  int derivative_L;
  int derivative_R;

  int deaccel_delay = 100;
  int joystickarmrange = 30;

  armtarget_L = 4095 - analogRead(potarmL);
  armtarget_R = analogRead(potarmR);
  lcdClear(uart1);
//bool p_or_d = true;
//int timeoutlcd = 50;

  while(true){
/*
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

*/

    //set value
    armheight_L = 4095-analogRead(potarmL);
    armheight_R = analogRead(potarmR);

    //find error
    armdiff_L = armtarget_L - armheight_L;
    armdiff_R = armtarget_R - armheight_R;

    //calculate P
    proportion_L = armdiff_L;
    proportion_R = armdiff_R;

    //intergral cap+calcualte I
    if(abs(armdiff_L) < integral_activezone){
    integral_L = integral_L + (armdiff_L);}
    else{integral_L = 0;}

    if(abs(armdiff_R) < integral_activezone){
      integral_R = integral_R + (armdiff_R);}
    else{integral_R = 0;}

    //calculate D
    derivative_L =  armdiff_L - lastdiff_L;
    lastdiff_L = armdiff_L;
    derivative_R =  armdiff_R - lastdiff_R;
    lastdiff_R = armdiff_R;

    //calcualte power values
    power_L = (derivative_L*k_derivative) + (integral_L*k_integral)+(proportion_L*k_proportion);
    power_R = (derivative_R*k_derivative) + (integral_R*k_integral)+(proportion_R*k_proportion);

  armskew = ((analogRead(potarmR))-(4095-analogRead(potarmL))) + OFFSET_ARM;
    // (R - L) + OFF SET


    if(joystickGetDigital(1,6,JOY_UP)){

      motorSet(ArmLT, (ArmLT_Dir*127)+(armskew*k_skew));
      motorSet(ArmLB, (ArmLB_Dir*127)+(armskew*k_skew));
      motorSet(ArmRT, (ArmRT_Dir*127)-(armskew*k_skew));
      motorSet(ArmRB, (ArmRB_Dir*127)-(armskew*k_skew));
      delay(deaccel_delay);
      armtarget_L = 4095-analogRead(potarmL);
      armtarget_R = analogRead(potarmR);}

    else if(joystickGetDigital(1,6,JOY_DOWN)){

      motorSet(ArmLT, (ArmLT_Dir*-127)-(armskew*k_skew));
      motorSet(ArmLB, (ArmLB_Dir*-127)-(armskew*k_skew));
      motorSet(ArmRT, (ArmRT_Dir*-127)+(armskew*k_skew));
      motorSet(ArmRB, (ArmRB_Dir*-127)+(armskew*k_skew));
      delay(deaccel_delay);
      armtarget_L = 4095 - analogRead(potarmL);
      armtarget_R = analogRead(potarmR);}

      else if (joystickGetAnalog(2, 3) > joystickarmrange){
        motorSet(ArmLT, (ArmLT_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmLB, (ArmLB_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmRT, (ArmRT_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmRB, (ArmRB_Dir*joystickGetAnalog(2, 3)));
        delay(deaccel_delay);
        armtarget_L = 4095 - analogRead(potarmL);
        armtarget_R = analogRead(potarmR);}
      else if (joystickGetAnalog(2, 3) < -joystickarmrange){
        motorSet(ArmLT, (ArmLT_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmLB, (ArmLB_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmRT, (ArmRT_Dir*joystickGetAnalog(2, 3)));
        motorSet(ArmRB, (ArmRB_Dir*joystickGetAnalog(2, 3)));
        delay(deaccel_delay);
        armtarget_L = 4095 - analogRead(potarmL);
        armtarget_R = analogRead(potarmR);}

    else {
        motorSet(ArmLT, ArmLT_Dir*power_L);
        motorSet(ArmLB, ArmLB_Dir*power_L);
        motorSet(ArmRT, ArmRT_Dir*power_R);
        motorSet(ArmRB, ArmRB_Dir*power_R);

        }

//lcdPrint(uart1, 1, "PL=%d TL =%d", armheight_L, armtarget_L);
//lcdPrint(uart1, 2, "PR=%d TR =%d", armheight_R, armtarget_R);
  //delay
    delay(25);
    }
  }

void armpresets(){
    if(joystickGetDigital(1,8,JOY_UP)){
      armtarget_L = ARM_MAX_L;
      armtarget_R = ARM_MAX_R;}
    else if(joystickGetDigital(1,8,JOY_DOWN)){
      armtarget_L = ARM_GROUND_L;
      armtarget_R = ARM_GROUND_R;}
    else if (joystickGetDigital(1,8,JOY_LEFT)){
      armtarget_L = ARM_MID_L;
      armtarget_R = ARM_MID_R;}
    else if(joystickGetDigital(1,8,JOY_RIGHT)){
    //  armtarget_L = ;
    //  armtarget_R = ;
    }
    else{
    }
  }
