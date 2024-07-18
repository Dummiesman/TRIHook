#pragma once
#include "trihook/trihook.h"
#include <stdio.h>
#include <stdlib.h>
#define DIRECTINPUT_VERSION 0x0700

typedef HRESULT(WINAPI* LPFNDIRECTINPUTCREATE)(HINSTANCE, DWORD, LPVOID*, LPUNKNOWN);

EXTERN_C LPFNDIRECTINPUTCREATE lpDICreate;
EXTERN_C HRESULT DirectInputCreateImpl(HINSTANCE hinst, DWORD dwVersion, LPVOID* ppDI, LPUNKNOWN punkOuter);