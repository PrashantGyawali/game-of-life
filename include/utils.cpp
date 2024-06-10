#pragma once
#include "raylib.h"

inline int getRandomBoolean(int Chance)
{
    int value = GetRandomValue(0, 100);
    if(value<Chance)
    {
        return 1;
    }
    return 0;
}