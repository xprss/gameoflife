#ifndef __SHLIB_H__
#define __SHLIB_H__
#include <stdio.h>
#include <stdlib.h>
#include "vec2.h"

int rnd(int, int);
vec2 rnd_vec2(int, int);
int clamp(int, int, int);
int msleep(long);

#endif
