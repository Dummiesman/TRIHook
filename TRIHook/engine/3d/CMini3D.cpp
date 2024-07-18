#include "CMini3D.h"

#if defined(TRIHOOK_GAME_EVO)
declfield(CMini3D::tempVertexBuffer)(0xAECF54);
#elif defined(TRIHOOK_GAME_EVO_ED)
declfield(CMini3D::tempVertexBuffer)(0xCAE454);
#endif

#if defined(TRIHOOK_GAME_EVO)
VertexVNT* CMini3D::getTempVertexBuffer()
{
    return CMini3D::tempVertexBuffer.get();
}

void CMini3D::unlockFrame()
{
    hook::StaticThunk<0x481030>::Call<void>();
}

void CMini3D::lockFrame()
{
    hook::StaticThunk<0x481020>::Call<void>();
}

void CMini3D::polyList(SD3DTLVertex const* vertices, int vertexCount, unsigned short* polys, int polyCount)
{
    hook::StaticThunk<0x482C60>::Call<void>(vertices, vertexCount, polys, polyCount);
}

float CMini3D::getPixelHeight(float realHeight, BOOL a2)
{
    int I_height = hook::StaticThunk<0x483FA0>::Call<int>(realHeight, a2);
    return COERCE_FLOAT(I_height);
}

void CMini3D::disableBlend()
{
    hook::StaticThunk<0x4823C0>::Call<void>();
}

void CMini3D::enableBlend()
{
    hook::StaticThunk<0x4823B0>::Call<void>();
}

void CMini3D::setPolyType(int type)
{
    hook::StaticThunk<0x4821C0>::Call<void>(type);
}

void CMini3D::clear()
{
    hook::StaticThunk<0x567830>::Call<void>();
}

void CMini3D::setWindow(float x1, float y1, float x2, float y2)
{
    hook::StaticThunk<0x481720>::Call<void>(x1, y1, x2, y2);
}
#elif defined(TRIHOOK_GAME_EVO2)
VertexVNT* CMini3D::getTempVertexBuffer()
{
    return nullptr;
}

void CMini3D::unlockFrame()
{
    hook::StaticThunk<0x495DA0>::Call<void>();
}

void CMini3D::lockFrame()
{
    hook::StaticThunk<0x495D90>::Call<void>();
}

void CMini3D::clear()
{
    hook::StaticThunk<0x495DB0>::Call<void>();
}

void CMini3D::setWindow(float x1, float y1, float x2, float y2)
{
    hook::StaticThunk<0x4969B0>::Call<void>(x1, y1, x2, y2);
}
#elif defined(TRIHOOK_GAME_EVO_ED)
VertexVNT* CMini3D::getTempVertexBuffer()
{
    return CMini3D::tempVertexBuffer.get();
}

void CMini3D::unlockFrame()
{
    hook::StaticThunk<0x4BFB30>::Call<void>();
}

void CMini3D::lockFrame()
{
    hook::StaticThunk<0x4BFB20>::Call<void>();
}

void CMini3D::setWindow(float x1, float y1, float x2, float y2)
{
    hook::StaticThunk<0x4C0220>::Call<void>(x1, y1, x2, y2);
}
#endif
