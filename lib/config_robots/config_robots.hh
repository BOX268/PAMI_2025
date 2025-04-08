# ifndef CONFIG_ROBOTS
# define CONFIG_ROBOTS

#include <Arduino.h>

# define TEST_MODE

# ifdef TEST_MODE
# define GLOBAL_WAIT 2000
# endif
# ifndef TEST_MODE
# define GLOBAL_WAIT 90000
# endif

//# define PRINT_DISTANCES


///////// define pin name /////////// 

const uint8_t sensorPinRight = A4;
const uint8_t sensorPinMidel = A2;
const uint8_t sensorPinLeft = A1;
const uint8_t servoPin = 17;
const uint8_t tirette = 11;
const uint8_t bouton_equipe = 10; // low = blue vers le haut, hight= jaune ( équipe bleu par default)

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
# define SUPERSTAR // faut supprimer ça plus tard

///////// fin chose which pami you want to use /////////////

# define time_evitement_depart 1/portTICK_PERIOD_MS /// ????? 

// position struct
typedef struct Point {
    float x;
    float y;
} Point;

extern Point waypoints[];
extern bool avoidance[];
extern uint32_t numPoints;
extern char equipe; // equipe bleu par default


#ifdef PAMI_1 // la superstar

#define X_POSITION_START_ 0.0 
#define Y_POSITION_START_  0.0
#define TETA_POSITION_START_ 0.0

#define MOTOR_X_RPM_ 100
#define MOTOR_Y_RPM_ 100
#define MOTOR_ACCEL_ 1400
#define MOTOR_DECEL_ 4000
#define MOTOR_DECEL_FINISH_ 500

#define MOTOR_ACCEL_DECEL_ROTATE_ 700 // 700

#define COEF_ROTATE 493 // 1=493 2 =498 3=495 4=487
#define COEF_STRAIGHT 1.0

#define ADD_DELAY_START 0.0 // after the 85sec we add a extra delay to avoid all the pami to start at the same time. 
const int SUPERSTAR_FLOOR_THRESHOLD = 75; //The distance above which we consider there is no floor  // True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered

# endif


#ifdef PAMI_2

float x_goal = 2500; // 1=2500 2=500 3=2400  4=500
float y_goal = 1220; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 2970;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 1280; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 1100 ; //1=1100 2=200 3=600 4=100
int time_start = 1000; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif

#ifdef PAMI_3

float x_goal = 550; // 1=2500 2=500 3=2400  4=500
float y_goal = 1350; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 150;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 1650; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 700; //1=1100 2=200 3=600 4=100
int time_start = 0; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif

/* ORIGINAL CODE USED FOR CUP
#ifdef PAMI_4

float x_goal = 500; // 1=2500 2=500 3=2400  4=500
float y_goal = 420; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 30;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 480; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 300 ; //1=1100 2=200 3=600 4=100
int time_start = 3000; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif
*/
/*
#ifdef PAMI_4

float x_goal = 1000; // 1=2500 2=500 3=2400  4=500
float y_goal = 0; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 1000;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 100; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 0 ; //1=1100 2=200 3=600 4=100
int time_start = 0; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif
*/

#ifdef PAMI_4

float x_goal = 1300; // 1=2500 2=500 3=2400  4=500
float y_goal = 0; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 1300;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 50; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 0 ; //1=1100 2=200 3=600 4=100
int time_start = 0; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif



# endif


