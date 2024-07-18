#pragma once
#include <trihook/trihook.h>
#include "3dstructs.h"

class CMini3D
{
private:
#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO_ED)
    static hook::Type<SD3DTLVertex*> tempVertexBuffer;
#endif
public:
    static VertexVNT* getTempVertexBuffer();
    static void unlockFrame();
    static void lockFrame();
    static void clear();
    static void polyList(SD3DTLVertex const* vertices, int vertexCount, unsigned short* polys, int polyCount);
    static float getPixelHeight(float realHeight, BOOL a2);
    static void disableBlend();
    static void enableBlend();
    static void setPolyType(int type);
    static void setWindow(float x1, float y1, float x2, float y2);
};

