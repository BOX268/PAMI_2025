#include "config_robots.hh"

char equipe = 'B'; // équipe bleu par default

#ifdef PAMI_1 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {2500, 1300},
    {1850,800},
    {1600,800},
    
    
};

bool avoidance[] = {false,false,false};
float rpms[] = {100, MOTOR_RPM_, MOTOR_RPM_};
uint32_t numPoints = 3;

# endif 

#ifdef PAMI_2 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {2600,1880},
    {2600,1500},
    {1500,800},
    //{1900,200},
    //{500,200},
    
};

bool avoidance[] = {false,false,false};
float rpms[] = {MOTOR_RPM_,MOTOR_RPM_,50};

uint32_t numPoints = 3;

# endif 

#ifdef PAMI_3

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {230, 1715},
    {780, 1350},
    {1300,1350},
    {1300,1360},
    
};

bool avoidance[] = {false,true,true,true};
float rpms[] = {MOTOR_RPM_, MOTOR_RPM_, MOTOR_RPM_, MOTOR_RPM_};

uint32_t numPoints = 4;

# endif



#ifdef PAMI_4 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {500,1600 },
    {650,1170},
   { 1840,1170},
    {1860,1350},
  
};

bool avoidance[] = {false,true,true,true};
float rpms[] = {MOTOR_RPM_, MOTOR_RPM_, MOTOR_RPM_, MOTOR_RPM_};
uint32_t numPoints = 4;

# endif