#pragma once
#include <cmath>
#include <engine\math\CVector.h>

static void sinCos(float& outSin, float& outCos, float& n)
{
    outSin = sinf(n);
    outCos = cosf(n);
}