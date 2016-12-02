#ifndef MAIN_H_
// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define MAIN_H_
#include <API.h>
// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

//drive motors
#define DriveBL 1
  #define DriveBL_Dir -1
#define DriveFL 2
  #define DriveFL_Dir 1
#define DriveFR 9
  #define DriveFR_Dir -1
#define DriveBR 10
  #define DriveBR_Dir 1

//Intake motors
#define ClawL 8
  #define ClawL_Dir -1
#define ClawR 3
  #define ClawR_Dir 1

//Arm motors
#define ArmLT 7
  #define ArmLT_Dir 1
#define ArmLB 6
  #define ArmLB_Dir 1
#define ArmRT 4
  #define ArmRT_Dir -1
#define ArmRB 5
  #define ArmRB_Dir 1

//analog sensors
#define accel_x 3
#define accel_y 4
#define gyroport 5
#define potarmR 6
#define potarmL 7
#define potclaw 8

//digital sensors
#define encoderFR_TOP 5
#define encoderFR_BOT 6

#define encoderFL_TOP 1
#define encoderFL_BOT 2

#define encoderBR_TOP 11
#define encoderBR_BOT 12

#define encoderBL_TOP 7
#define encoderBL_BOT 8

#define ime_BL 1
#define ime_BR 0

Encoder encoderFL;
Encoder encoderFR;
Encoder encoderBL;
Encoder encoderBR;
Gyro gyro;
Ultrasonic ultrasonic;

#define ARM_MAX_R 1000
#define ARM_MAX_L 1000
#define ARM_GROUND_R 245
#define ARM_GROUND_L 260
#define ARM_MID_R 2560
#define ARM_MID_L 2780
#define ARM_REALMAX_L 3470
#define ARM_REALMAX_R 3370

#define OFFSET_ARM 50
//L-R
void drive_armcontrol(void *ignore);
void armpresets();


#define CLAW_MAX 3030
#define CLAW_CLOSED 275
#define CLAW_SEMI_OPEN 1100
#define CLAW_REALMAX 3360
void clawpresets();
void drive_clawcontrol(void *ignore);

void drive_lcd_task(void *ignore);
/*
//drive_pid globals
  //varibles
extern int drive_armheight_L;
extern int drive_armheight_R;
extern int armtarget_L;
extern int armtarget_R;
extern int arm_skew;

  //constants
extern float arm_k_skew = 0.5;
extern float arm_k_proportion = 0.15;
extern float arm_k_integral = 0;
extern int arm_integral_activezone = 100;
extern float arm_k_derivative = 0;
extern int arm_deaccel_delay = 100;
extern int arm_joystickrange = 30;


//claw_pid globals
  //varible
extern int claw_pos;
extern int clawtarget;
  //constants
extern float claw_k_proportion = 0.18;
extern float claw_k_integral = 0;
extern float claw_integral_activezone = 100;
extern float claw_k_derivative = 0;
extern int claw_deaccel_delay = 100;
extern int claw_joystickrange = 30;
*/

/*
//globals
//drive_pid globals
  //varibles
 int drive_armheight_L;
 int drive_armheight_R;
 int armtarget_L;
 int armtarget_R;
 int arm_skew;

  //constants
 float arm_k_skew = 0.5;
 float arm_k_proportion = 0.15;
 float arm_k_integral = 0;
 int arm_integral_activezone = 100;
 float arm_k_derivative = 0;
 int arm_deaccel_delay = 100;
 int arm_joystickrange = 30;


//claw_pid globals
  //varible
 int claw_pos;
 int clawtarget;
  //constants
 float claw_k_proportion = 0.18;
 float claw_k_integral = 0;
 float claw_integral_activezone = 100;
 float claw_k_derivative = 0;
 int claw_deaccel_delay = 100;
 int claw_joystickrange = 30;


*/

//#define AUTO_DEBUG
// A function prototype looks exactly like its declaration, but with a semicolon instead of
// actual code. If a function does not match a prototype, compile errors will occur.

// Prototypes for initialization, operator control and autonomous
void autonomous();
void initializeIO();
void initialize();
void operatorControl();

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
