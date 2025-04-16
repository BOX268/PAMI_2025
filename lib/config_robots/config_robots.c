#include "config_robots.hh"

char equipe = 'B'; // équipe bleu par default

#ifdef PAMI_1 // la superstar

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {1300, 1900},
    {1300, 1800},
    {1200,200},
    {900,200},
    {1200,400}
};

bool avoidance[] = {false,false,false,false,true};
uint32_t numPoints = 2;

# endif

#ifdef PAMI_2 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {300,1820 },
    {550,1520},
   { 950,1520},
   
  
};

bool avoidance[] = {true,true,false,};
uint32_t numPoints = 3;

# endif

#ifdef PAMI_3

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {230, 1715},
    {700, 1350},
    {1300,1350},
   
    
};

bool avoidance[] = {false,false,false};
uint32_t numPoints = 3;

# endif



#ifdef PAMI_4 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {450,1600 },
    {550,1170},
   { 1800,1170},
    {1900,1350},
  
};

bool avoidance[] = {true,true,true,true};
uint32_t numPoints = 4;

# endif