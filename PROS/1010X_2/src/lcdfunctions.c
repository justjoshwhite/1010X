#include "main.h"
#include "API.h"


void autoselect(){
lcdSetBacklight(uart1, true);
while(true)
  switch (myauto){
    case(1):
      lcdPrint(uart1, 1, "Auto 1");
      lcdPrint(uart1, 2, "1010X");
      if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
        myauto = 1;}
      else if(lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        myauto = 2;}
      else {}
    break;
    case(2):
      lcdPrint(uart1, 1, "Auto 1");
      lcdPrint(uart1, 2, "1010X");
      if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
        myauto = 1;}
      else if(lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        myauto = 3;}
      else {}
    break;
    case(3):
      lcdPrint(uart1, 1, "Auto 1");
      lcdPrint(uart1, 2, "1010X");
      if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
        myauto = 2;}
      else if(lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        myauto = 4;}
      else {}
    break;
    case(4):
      lcdPrint(uart1, 1, "Auto 1");
      lcdPrint(uart1, 2, "1010X");
      if(lcdReadButtons(uart1) == LCD_BTN_LEFT){
        myauto = 3;}
      else if(lcdReadButtons(uart1) == LCD_BTN_RIGHT){
        myauto = 4;}
      else {}
    break;
  }
}
