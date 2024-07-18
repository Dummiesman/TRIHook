#pragma once
#include <trihook/trihook.h>
#include "SMaterial.h"
#include "3dstructs.h"

class CSimpleModel
{
private:
    int vertCount;
    int frameCount;
    SVertex* vertexBuffer;
    int triCount;
    unsigned short* triIndices;
    SMaterial material;
    int dword_74;
    int dword_78;
    int dword_7c;
    int dword_80;
    int dword_84;
    int dword_88;
public:
    void* getTexture();
    void* getVertexList();
    unsigned short* getFaceList();
    int getVertexCount() const;
    int getFaceCount() const;
};
ASSERT_SIZEOF(CSimpleModel, 0x8C);

