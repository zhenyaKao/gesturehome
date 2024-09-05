#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef enum { NONE, UP_DOWN, LEFT_RIGHT, FLIP } Direction;

struct posData {
  double x_axis;
  double y_axis;
  double z_axis;
};

struct event {
  time_t timestamp;
  int count;
  Direction dir;
};

extern struct posData prevData;
extern unsigned int x_movement;
extern unsigned int z_movement;

#endif // COMMON_H
