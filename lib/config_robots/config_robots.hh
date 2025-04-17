# ifndef CONFIG_ROBOTS
# define CONFIG_ROBOTS

#include <Arduino.h>

# define TEST_MODE
//# define PRINT_DISTANCES
# define EVITEMENT 

# ifdef TEST_MODE
# define GLOBAL_WAIT 2000
# endif
# ifndef TEST_MODE
# define GLOBAL_WAIT 90000
# endif

///////// define pin name /////////// 

const uint8_t sensorPinRight = A3; // time out 20
const uint8_t sensorPinMidel = A2;
const uint8_t sensorPinLeft = A1;
const uint8_t servoPin = 17; //A0
const uint8_t tirette = 11; // D11
const uint8_t bouton_equipe = 10; // D10 low = blue vers le haut, hight= jaune ( équipe bleu par default)

#define DIR_X 3 // moteur gauche
#define STEP_X 6 // moteur gauche
#define DIR_Y 4 //moteur droit
#define STEP_Y 7 //moteur droit
#define ENABLE 8 // pin enable des driver moteur droite et gauche

///////////// fin pin name ////////////

////// chose which pami you want to use /////////////

# define PAMI_1 // la superstar
//# define PAMI_2
//# define PAMI_3
//# define PAMI_4

///////// fin chose which pami you want to use /////////////

// position struct {x,y} in mm
typedef struct Point {
    float x; 
    float y; 
} Point;

extern Point waypoints[];
extern bool avoidance[];
extern uint32_t numPoints;
extern char equipe; // equipe bleu par default


#ifdef PAMI_1 // la superstar

#define X_POSITION_START_ 70.0
#define Y_POSITION_START_  1940
#define TETA_POSITION_START_ 0.0

#define MOTOR_RPM_ 50
#define MOTOR_ACCEL_ 1400
#define MOTOR_DECEL_ 3000
//#define MOTOR_DECEL_AVOIDEMENT 5000 // freinage brust s'il y a un obstacle
//#define MOTOR_DECEL_FINISH_ 500

#define MOTOR_ACCEL_DECEL_ROTATE_ 700 // 700

#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0

#define ADD_DELAY_START 0.0 // after the 85sec we add a extra delay to avoid all the pami to start at the same time. 
const int SUPERSTAR_FLOOR_THRESHOLD = 75; //The distance above which we consider there is no floor  // True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered

# endif

#ifdef PAMI_2 

#define X_POSITION_START_ 70.0
#define Y_POSITION_START_  1900
#define TETA_POSITION_START_ 0.0

#define MOTOR_RPM_ 100
#define MOTOR_ACCEL_ 1400
#define MOTOR_DECEL_ 300
//#define MOTOR_DECEL_AVOIDEMENT 5000 // freinage brust s'il y a un obstacle
//#define MOTOR_DECEL_FINISH_ 500

#define MOTOR_ACCEL_DECEL_ROTATE_ 700 // 700

#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0

#define ADD_DELAY_START 0.0 // after the 85sec we add a extra delay to avoid all the pami to start at the same time. 
const int SUPERSTAR_FLOOR_THRESHOLD = 75; //The distance above which we consider there is no floor  // True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered
# endif

#ifdef PAMI_3

#define X_POSITION_START_ 70.0
#define Y_POSITION_START_  1900
#define TETA_POSITION_START_ 0.0

#define MOTOR_RPM_ 100
#define MOTOR_ACCEL_ 1400
#define MOTOR_DECEL_ 300
//#define MOTOR_DECEL_AVOIDEMENT 5000 // freinage brust s'il y a un obstacle
//#define MOTOR_DECEL_FINISH_ 500

#define MOTOR_ACCEL_DECEL_ROTATE_ 700 // 700

#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0

#define ADD_DELAY_START 0.0 // after the 85sec we add a extra delay to avoid all the pami to start at the same time. 
const int SUPERSTAR_FLOOR_THRESHOLD = 75; //The distance above which we consider there is no floor  // True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered
# endif

#ifdef PAMI_4

#define X_POSITION_START_ 70.0
#define Y_POSITION_START_  1900
#define TETA_POSITION_START_ 0.0

#define MOTOR_RPM_ 100
#define MOTOR_ACCEL_ 1400
#define MOTOR_DECEL_ 300
//#define MOTOR_DECEL_AVOIDEMENT 5000 // freinage brust s'il y a un obstacle
//#define MOTOR_DECEL_FINISH_ 500

#define MOTOR_ACCEL_DECEL_ROTATE_ 700 // 700

#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0

#define ADD_DELAY_START 0.0 // after the 85sec we add a extra delay to avoid all the pami to start at the same time. 
const int SUPERSTAR_FLOOR_THRESHOLD = 75; //The distance above which we consider there is no floor  // True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered
# endif

# endif