#include "main.h"

void autonomous() {

lcdClear(uart1);
lcdPrint(uart1, 1, "Auto %d Running", myauto);

switch (myauto) {
  case 1:
    drivestraight(NORTH, 3000, 25, 110);
  break;
  case 2:
    turnexact(1, 90, 50, 110);
  break;
  default:
  break;
  }
}
