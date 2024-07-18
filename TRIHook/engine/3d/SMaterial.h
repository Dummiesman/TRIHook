#pragma once
#include <trihook/trihook.h>

struct SMaterial
{
    float kd;
    float ks;
    float power;
    int transparent;
    int reflective;
    int dword_14;
    char texture[64];
    int dword_58;
    int dword_5c;
};

ASSERT_SIZEOF(SMaterial, 0x60);