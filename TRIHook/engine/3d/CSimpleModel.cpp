#include "CSimpleModel.h"

void* CSimpleModel::getTexture()
{
    return hook::StaticThunk<0x551780>::Call<void*>(this);
}

unsigned short* CSimpleModel::getFaceList()
{
    return this->triIndices;
}

int CSimpleModel::getVertexCount() const
{
    return this->vertCount;
}

int CSimpleModel::getFaceCount() const
{
    return this->triCount;
}
