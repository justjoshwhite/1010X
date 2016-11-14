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
