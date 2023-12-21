#include "../include/shlib.h"
#include <time.h>

int rnd(int min, int max)
{
    return (int)rand() % (max - min) + min;
}

vec2 rnd_vec2(int x, int y)
{
    vec2 v;
    v.x = rnd(0, y);
    v.y = rnd(0, x);
    return v;
}

int clamp(int min, int val, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res);

    return res;
}