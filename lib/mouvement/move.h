#ifndef MOVE_H
#define MOVE_H
#include"Arduino.h"
//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>
//#include <freertos/timers.h>  // Si vous utilisez des timers FreeRTOS
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <math.h>
#include <cmath>
#include <string>

# define PAMI_1
//# define PAMI_2
//# define PAMI_3
//# define PAMI_4

#define MOTOR_STEPS 200
#define MOTOR_X_RPM 100
#define MOTOR_Y_RPM 100
#define MOTOR_RPM 100
#define DIR_X 3 // moteur gauche
#define STEP_X 6 // moteur gauche
#define DIR_Y 4 //moteur droit
#define STEP_Y 7 //moteur droit

// changer cette valeur à 1 a l'air de casser le calcul de distance et la puissance des moteurs
#define MICROSTEPS 16

#define MOTOR_ACCEL 1400
#define MOTOR_DECEL 4000
#define MOTOR_DECEL_FINISH 500

#define MOTOR_ACCEL_DECEL_ROTATE 700 // 700

# ifdef PAMI_1
#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0
# endif
# ifdef PAMI_2
#define COEF_ROTATE 494
#define COEF_STRAIGHT 1.0
# endif
# ifdef PAMI_3
#define COEF_ROTATE 497
#define COEF_STRAIGHT 1.0
# endif
# ifdef PAMI_4
#define COEF_ROTATE 500
#define COEF_STRAIGHT 1.0
# endif

  // 1 


extern BasicStepperDriver stepperR;
extern BasicStepperDriver stepperL;
//extern SyncDriver controller(stepperR, stepperL);

void straight(float distance_);
void rotate (float angle);
void go_to(float go_x, float go_y);
void configureMotors();
void debug_position();
void evitement_droit();
void evitement_gauche();
void position();
bool moving();
void stop();

void SetRPM(int rpm);

extern float x_position ;
extern float y_position ;
extern float teta_actuelle;

extern long int total_Steps_R;
extern long int total_Steps_L;

extern int evitement;

//extern float x_goal_position ;
//extern float y_goal_position ;

#endif