#include "config_robots.hh"

char equipe = 'B'; // équipe bleu par default

#ifdef PAMI_1 // la superstar

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {300, 1940},
    {500, 1900},
    {1300,1900},
    {1300,1800},
    
};

bool avoidance[] = {false,false,false,false,};
uint32_t numPoints = 4;

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
    {1300,1360},
    
};

bool avoidance[] = {true,true,true,true};
uint32_t numPoints = 4;

# endif



#ifdef PAMI_4 

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {450,1600 },
    {550,1170},
   { 1840,1170},
    {1860,1350},
    
    
  
};

bool avoidance[] = {true,true,true,true};
uint32_t numPoints = 4;

# endif