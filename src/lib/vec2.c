#include "../include/vec2.h"

vec2 i2v2(int i, int C)
{
    vec2 v2;
    v2.x = (int)i / C;
    v2.y = i % C;
    return v2;
}

int v22i(vec2 v, int C)
{
    return v.x * C + v.y;
}