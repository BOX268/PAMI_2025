#include "config_robots.hh"

char equipe = 'B'; // équipe bleu par default

#ifdef PAMI_1 // la superstar

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {10, 0},
    {11,0}
};

bool avoidance[] = {true,true};
uint32_t numPoints = 2;

# endif
