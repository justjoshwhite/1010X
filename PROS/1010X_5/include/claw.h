#ifndef CLAW_H_
#define CLAW_H_

#include "main.h"
#include "pid.h"

PID_terms pid_claw;

int claw_target_global;
int claw_pos_global;

void clawpresets();
void clawtask(void*ignore);

#define CLAW_DELAY 200

#define CLAW_CLOSED 880
#define CLAW_V 800 //semi closed
#define CLAW_45 650
#define CLAW_PARALLEL 390
#define CLAW_MAX 0

TaskHandle claw_task;

#endif
