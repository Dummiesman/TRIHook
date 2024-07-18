#include "C3DModel.h"

int C3DModel::getPartCount() const
{
    return this->numModels;
}

CSimpleModel* C3DModel::getPart(int num)
{
    if (num < 0 || num >= getPartCount()) 
    {
        //GTFO()
        return nullptr;
    }
    return this->modelPtrs[num];
}
