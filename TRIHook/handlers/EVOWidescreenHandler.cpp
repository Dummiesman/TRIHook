#include "EVOWidescreenHandler.h"
#include <engine/engine_3d.h>

const char* resolutionFormat = "Resolution\t%dx%d";

const int numResolutions = 22;
const int resolutions[][2] = {
    {320,240},
    {640,480},
    {800,600},
    {1024,768},
    {1280,720},
    {1280,800},
    {1280,1024},
    {1360,768},
    {1366,768},
    {1440,900},
    {1536,864},
    {1600,900},
    {1680,1050},
    {1920,1080},
    {1920,1200},
    {2048,1152},
    {2048,1536},
    {2560,1080},
    {2560,1440},
    {2560,1600},
    {3440,1440},
    {3840,2160}
};

//hook::Type<C3DModel*> needleModel_EVO1 = 0xB9E540;
void overlay_test()
{
    //auto needleModel = needleModel_EVO1.get();
    auto vb = CMini3D::getTempVertexBuffer();

    // draw speedo

    // draw tacho
}

void EVOWidescreenHandler::initFonts()
{
#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2)
    auto font = new CBitFont();
    gSmallLCDFont.set(font);

    int pixy = PIXY.get();
    if (pixy <= 300)
    {
        //fnto_200
        font->init("fnto_200.RAW", 132, 220, 255);
        font->setYCharOffset(3, 32, 126);
        font->setUnkThing(4, 1, 1);
    }
    else if (pixy <= 400)
    {
        //fnto_400
        font->init("fnto_400.RAW", 132, 432, 255);
        font->setYCharOffset(6, 32, 126);
        font->setUnkThing(4, 1, 1);
    }
    else
    {
        //4x4font
        font->init("4x4font.raw", 256, 256, 0);
        font->setYCharOffset(3, 32, 126);
        font->setUnkThing(6, 2, 1);
    }

    if (pixy >= 384)
    {
        font->fontIsAntiAliased();
    }

    gSmallFont.set(font);
    gMediumFont.set(font);
    gLargeFont.set(font);
    gEPfont.set(font);
    gEdFont.set(font);

    //TODO: gMediumOSFont
#endif
}

static void drawResolutionSelector()
{
    int selectedOption = 0;
    CPickList list = CPickList();

    for (int i = 0; i < numResolutions; i++)
    {
        char buf[32];
        sprintf(buf, "%i x %i", resolutions[i][0], resolutions[i][1]);
        list.addItem(buf);

        if (resolutions[i][0] == PIXX.get() && resolutions[i][1] == PIXY.get())
            selectedOption = i;
    }
    selectedOption = list.drawWindow("Choose Resolution", selectedOption, 0);

    if (selectedOption >= 0)
    {
        gamePIXX.set(resolutions[selectedOption][0]);
        gamePIXY.set(resolutions[selectedOption][1]);
    }
}

#if defined(TRIHOOK_GAME_EVO) 
const int afterAddr = 0x47C8F1;
#elif defined(TRIHOOK_GAME_EVO2)
const int afterAddr = 0x492216;
#else
const int afterAddr = 0x00;
#endif
static _declspec(naked) void jptHook()
{
    // lets not muck up the stack, call a separate function
    drawResolutionSelector();
    __asm jmp[afterAddr];
}

bool EVOWidescreenHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2;
}

void __cdecl EVOWidescreenHandler::setWindowHook()
{
    // set the window proportional to our aspect ratio
    // this fixes the flickering background
    float aspect = (float)PIXX.get() / (float)PIXY.get();
    float threeFourFactor = aspect / 1.33333334f;
    CMini3D::setWindow(0, 0, 640.0f * threeFourFactor, 480.0f);
}

void __cdecl EVOWidescreenHandler::setSizeHook()
{
    // TRYING to fucking center this goddamn bullshit
    // oops, language.
    hook::StaticThunk<0x563640>::Call<void>(this); //singleplayerui setup

    float aspect = (float)PIXX.get() / (float)PIXY.get();
    float threeFourFactor = aspect / 1.33333334f;
    int xLoc = (int)((threeFourFactor - 1) * 320.0f);

    //hook::StaticThunk<0x429000>::Call<void>(this, (int)(640 * threeFourFactor), 480); //CComponent:setSize
    hook::StaticThunk<0x429520>::Call<void>(this, xLoc, 0); //CContainer:setLocation
    //hook::StaticThunk<0x4295B0>::Call<void>(this, xLoc, 0, xLoc + 640, 480); //CContainer::setLayout
}

void EVOWidescreenHandler::Install(GameType gameType)
{
    if (HookConfig::GetBool("Rendering", "EnableAdditionalResolutions", true))
    {
        // initFonts throws an error if one of the old preset resolutions wasn't chosen
        // so we get to rewrite it!
        if (gameType == GameType::Game_EVO)
        {
#if defined(TRIHOOK_ENABLE_INCOMPLETE_FEATURES)
            // still experimental in EVO1 as the tach is in the wrong spot
            InstallCallback("initFonts",
                &initFonts, {
                    cb::call(0x412B48),
                    cb::call(0x412B77),
                    cb::call(0x44ECA5),
                    cb::call(0x44ED45),
                    cb::call(0x474205),
                }
            );

            mem::write(0x47C364, &jptHook); // change jump from CPickList option handler
#endif
        }
        else if (gameType == GameType::Game_EVO2)
        {
            InstallCallback("setWindow adjustment", &setWindowHook, { 
                 cb::call(0x56E2A6),
                 cb::call(0x56E3C9), 
                 cb::call(0x5689CA),
                 cb::call(0x568A16),
                 cb::call(0x568A51),
                 cb::call(0x568AF8),
                 cb::call(0x568B6A),
                 cb::call(0x568C1D)
                }
            );
            //InstallCallback("set me later", &setSizeHook, { cb::call(0x55ECF5) });

            InstallCallback("initFonts",
                &initFonts, {
                    cb::call(0x415038),
                    cb::call(0x415067),
                    cb::call(0x462E24),
                    cb::call(0x48E10A),
                }
            );

            mem::write(0x491CD4, &jptHook); // change jump from CPickList option handler

            mem::write(0x49238A + 1, resolutionFormat); // remove "slow/slower/fastest"
            mem::write(0x492378 + 1, resolutionFormat); // remove "slow/slower/fastest"
            mem::write(0x491F34 + 1, resolutionFormat); // remove "slow/slower/fastest"
        }
    }
}