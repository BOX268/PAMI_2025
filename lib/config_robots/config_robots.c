#include "config_robots.hh"

char equipe = 'B'; // équipe bleu par default

#ifdef PAMI_1 // la superstar

// waypoints and avoidance need to have the same length
Point waypoints[] = {
    {1300, 0},
    {1300, 50}
};

bool avoidance[] = {false, false};
uint32_t numPoints = 2;

# endif
