#include "main.h"


void autoselector_code (void*ignore){

myauto = 1;
int lcd_delay = 200;
lcdClear(uart1);

while(true){
  if (isEnabled()){delay(50);}
  else if (!isEnabled()){
      lcdPrint(uart1, 1, "Auto %d", myauto);
      lcdSetText(uart1, 2, "");
      if(lcdReadButtons(uart1) == 1){
          myauto = myauto + 1;
          delay(lcd_delay);}
      else if(lcdReadButtons(uart1) == 4){
          myauto = myauto - 1;
          delay(lcd_delay);}
      }
      delay(30);
    }
}
