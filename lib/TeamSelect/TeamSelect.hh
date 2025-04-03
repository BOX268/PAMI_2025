# ifndef TEAM_SELECT
# define TEAM_SELECT

# define SUPERSTAR

# define time_evitement_depart 1/portTICK_PERIOD_MS

// position struct
struct Point
{
	float x;
	float y;
};

/*
#ifdef PAMI_1

float x_goal = 1300; // 1=2500 2=500 3=2400  4=500
float y_goal = 0; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 1300;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 50; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 0 ; //1=1100 2=200 3=600 4=100
int time_start = 0; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

# endif

*/

#ifdef PAMI_1 // la superstar

// waypoints and avoidance need to have the same length

Point waypoints[] = 
{
	{1300, 0},
	{1300, 50}
};

bool avoidance[] = {false, false};

uint numPoints = 2;


// additional delay before the pami starts moving
int time_start = 0; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s


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

// no idea why this variable is defined here
int depart = 0 ;

# endif


