#include "TestHooks.h"
#include "ScreenshotHandler.h"
#include <engine\engine_common.h>
#include <engine\engine_physics.h>

static hook::Type<int> componentList_selColR = 0x679CD8;
static hook::Type<int> componentList_selColG = 0x679CD8+4;
static hook::Type<int> componentList_selColB = 0x679CD8+8;

void HSVtoRGB(float& fR, float& fG, float& fB, float fH, float fS, float fV) {
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;

    if (0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    }
    else if (1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    }
    else if (2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    }
    else if (3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    }
    else if (4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    }
    else if (5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    }
    else {
        fR = 0;
        fG = 0;
        fB = 0;
    }

    fR += fM;
    fG += fM;
    fB += fM;
}

void __cdecl TestHooks::componentList_paint3d()
{
    // rainbow!
   // float t = (float)(getTime() % 1180000) / 1180000.0f;
   // float r, g, b;
   // HSVtoRGB(r, g, b, t * 360.0f, 1.0f, 1.0f);
   // componentList_selColR.set((int)(r * 255));
   // componentList_selColG.set((int)(g * 255));
   // componentList_selColB.set((int)(b * 255));

    // call original
    hook::StaticThunk<0x5A6B40>::Call<void>(this);
}

void TestHooks::processCheatCode_Shared()
{
    if (Keyboard::checkKeyPressed(DIK_F5))
    {
        float gravity = 32.174f;
        if (gEdTools.get()->inputFloat("Set Gravity\n(NOTE: In EVO2 vehicle gravity is 175% of this value)", &gravity, FALSE, 0.0f, 0.0f, true) == TRUE)
        {
            setGravity(gravity);
        }
    }
}

void TestHooks::processCheatCode_EVO()
{
    processCheatCode_Shared();
    if (Keyboard::checkKeyPressed(DIK_F10))
    {
        Keyboard::clearKeyPressed(DIK_F10);
        hook::StaticThunk<0x502020>::Call<void>(); // testing menu
    }

    if (Keyboard::checkKeyPressed(DIK_F9))
    {
        // lets try some string input??
        char buf[128];
        BOOL res = gEdTools.get()->inputString("Lets try string input?", buf, sizeof(buf), false);
        if (!res)
        {
            gEdTools.get()->genericDialog("Cancelled", "The operation was cancelled", 0xFFFFFFFF);
        }
        else {
            char buf2[1024];
            sprintf(buf2, "Entered  text was:%s", buf);
            gEdTools.get()->genericDialog("SUCCESS", buf2, 0xFFFFFFFF);
        }
    }
    if (Keyboard::checkKeyPressed(DIK_F8))
    {
        char path_buf[MAX_PATH];
        BOOL res = gEdTools.get()->pickFile("Pick truck", "TRUCK", "*.TRK", path_buf, false);
        if (res == TRUE)
        {
            gEdTools.get()->messageDialogF("Chosen Path:%s", path_buf);
        }
    }
    if (Keyboard::checkKeyPressed(DIK_F7))
    {
        char path_buf[20];
        BOOL res = gEdTools.get()->saveDialog("Save Dialog Test", "TRUCK", ".TRK", path_buf, false);
        if (res == TRUE)
        {
            gEdTools.get()->messageDialogF("Chosen Path:%s", path_buf);
        }
        else {
            gEdTools.get()->messageDialogF("%s", "Save cancelled.");
        }
    }

    //call original
    hook::StaticThunk<0x471B40>::Call<void>();
}

void TestHooks::processCheatCode_EVO2()
{
    processCheatCode_Shared();
    if (Keyboard::checkKeyPressed(DIK_F12))
    {
        Keyboard::clearKeyPressed(DIK_F12);
        ScreenshotHandler::screenShot();
    }

    if (Keyboard::checkKeyPressed(DIK_F10))
    {
        Keyboard::clearKeyPressed(DIK_F10);
        hook::StaticThunk<0x521A10>::Call<void>(); // testing menu
    }
    if (Keyboard::checkKeyPressed(DIK_F9))
    {
        // lets try some string input??
        char buf[128];
        BOOL res = gEdTools.get()->inputString("Lets try string input?", buf, sizeof(buf), false);
        if (!res)
        {
            gEdTools.get()->genericDialog("Cancelled", "The operation was cancelled", 0xFFFFFFFF);
        }
        else {
            char buf2[1024];
            sprintf(buf2, "Entered  text was:%s", buf);
            gEdTools.get()->genericDialog("SUCCESS", buf2, 0xFFFFFFFF);
        }
    }
    if (Keyboard::checkKeyPressed(DIK_F8))
    {
        char path_buf[MAX_PATH];
        BOOL res = gEdTools.get()->pickFile("Pick truck", "TRUCK", "*.TRK", path_buf, false);
        if (res == TRUE)
        {
            gEdTools.get()->messageDialogF("Chosen Path:%s", path_buf);
        }
    }
    if (Keyboard::checkKeyPressed(DIK_F7))
    {
        char path_buf[20];
        BOOL res = gEdTools.get()->saveDialog("Save Dialog Test", "TRUCK", ".TRK", path_buf, false);
        if (res == TRUE)
        {
            gEdTools.get()->messageDialogF("Chosen Path:%s", path_buf);
        }
        else {
            gEdTools.get()->messageDialogF("%s", "Save cancelled.");
        }
    }

    //call original
    hook::StaticThunk<0x48B250>::Call<void>();
}

bool TestHooks::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO2 || gameType == GameType::Game_EVO;
}

void TestHooks::Install(GameType gameType)
{
#if defined(TRIHOOK_ENABLE_INCOMPLETE_FEATURES)
    if (gameType == GameType::Game_EVO2)
    {
        InstallCallback("processCheatCode",
            &processCheatCode_EVO2, {
                cb::call(0x4638DC),
            }
        );
        InstallVTableHook("componentList_paint3d", &componentList_paint3d, { 0x6675F8 });

    }
    else if (gameType == GameType::Game_EVO)
    {
        InstallCallback("processCheatCode",
            &processCheatCode_EVO, {
                cb::call(0x44F6C5),
            }
        );
    }
#endif
}
