#include "main.h"
#include "API.h"

int motorcap(int value){
  if(value > 127)
  		return 127;
  	else if (value < -127)
  		return -127;
    else
      return value;
  }

void clawopen(int claw, int arm)
{
clawtarget = claw;
armtargetL = arm;
armtargetR = arm+300;
}
