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
    {1300, 1900},
    {1300, 1800},
    {1200,200},
    {900,200},
    {1200,400}
};

bool avoidance[] = {false,false,false,false,true};
uint32_t numPoints = 2;

# endif

#ifdef PAMI_3

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

#ifdef PAMI_4

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

