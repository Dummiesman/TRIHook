#pragma once
#include <trihook\trihook.h>
#include "CSimpleModel.h"
#include "..\math\CVector.h"

class C3DModel
{
private:
    int numModels;
    CSimpleModel* modelPtrs[100];
    char modelNames[100][32];
    bool modelVisibility[100];
    int gap_e78;
    CVector boundsMin;
    CVector boundsMax;
    CSimpleModel* mod_e94;
    CSimpleModel* mod_e98;
    int dword_e9c;
    int dword_ea0;
    int dword_ea4;
    int dword_ea8;
    int dword_eac;
    int dword_eb0;
    int dword_eb4;
    int dword_eb8;
    int dword_ebc;
    int dword_ec0;
    int dword_ec4;
    int dword_ec8;
    int dword_ecc;
    int dword_ed0;
    int dword_ed4;
    int dword_ed8;
    int dword_edc;
    int dword_ee0;
    int dword_ee4;
    int dword_ee8;
    int dword_eec;
    int dword_ef0;
    int dword_ef4;
    int dword_ef8;
    int dword_efc;
    int useSplit;
    float splitHeight;
    int IDopaqueL;
    int IDopaque;
    int IDtranspL;
    int IDtransp;
public:
    int getPartCount() const;
    CSimpleModel* getPart(int num);
};
ASSERT_SIZEOF(C3DModel, 0xF18);
