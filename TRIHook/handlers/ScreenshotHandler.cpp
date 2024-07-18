#include "ScreenshotHandler.h"
#include <engine\engine_gfx.h>
#include <engine\engine_3d.h>
#include <engine\engine_time.h>
#include "CallbacksHandler.h"
#include <thirdparty\pngplusplus\png.hpp>
#include <thread>


void ScreenshotHandler::PostInit()
{

}

void saveThread(const char* path, png::image< png::rgb_pixel >  image)
{
    image.write(path);
}

void ScreenshotHandler::screenShot()
{
    // perf logging
    hook_output("screenShot init");
    auto time_start = getTime();

    // 
    // find a suitable filename
    char fileBuf[256] = { 0 };
    int tryNum = 0;
    
    while (true) 
    {
        sprintf(fileBuf, "Screenshot_%06d.png", tryNum++);
        auto existingFile = fopen(fileBuf, "rb");
        if (existingFile == nullptr)
        {
            break;
        }
        fclose(existingFile);
    }

    auto dtime = getTime();
    hook_output("  find filename (%i)", TIME_TO_MS(dtime - time_start));

    // create image
    png::image< png::rgb_pixel > image(PIXX.get(), PIXY.get());

    dtime = getTime();
    hook_output("  create image (%i)", TIME_TO_MS(dtime - time_start));

    // TODO: merge into engine_gfx
    int** rowTable = (int**)0x813E5C;
    int red_scale2 = *(int*)0x81F768;
    int green_scale2 = *(int*)0x81F774;
    int blue_scale2 = *(int*)0x81F780;

    int red_shift2 = *(int*)0x81F764;
    int green_shift2 = *(int*)0x81F770;
    int blue_shift2 = *(int*)0x81F77C;

    int bpp = bitsPerPixel.get();
    if (bpp != 32)
    {
        hook_output("TODO: 16 bit screenies");
        return;
    }

    // read in pixels to image
    CMini3D::lockFrame();

    dtime = getTime();
    hook_output("  CMini3D::lockFrame (%i)", TIME_TO_MS(dtime - time_start));
    
    for (int y = 0; y < PIXY.get(); y++)
    {
        auto row = rowTable[y];
        for (int x = 0; x < PIXX.get(); x++)
        {
            int pixel = row[x];
            char red = red_scale2 * (pixel >> red_shift2);
            char green = green_scale2 * (pixel >> green_shift2);
            char blue = blue_scale2 * (pixel >> blue_shift2);
            
            image[y][x] = png::rgb_pixel(red, green, blue);
        }
    }

    dtime = getTime();
    hook_output("  fill pixels array (%i)", TIME_TO_MS(dtime - time_start));

    // finish off
    CMini3D::unlockFrame();

    dtime = getTime();
    hook_output("  CMini3D::unlockFrame() (%i)", TIME_TO_MS(dtime - time_start));

    image.write(fileBuf);

    dtime = getTime();
    hook_output("  image write (%i)", TIME_TO_MS(dtime - time_start));
}

bool ScreenshotHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO2;
}

void ScreenshotHandler::Install(GameType gameType)
{
    // Kill the swap space warning
    if (gameType == GameType::Game_EVO2)
    {
        CallbacksHandler::RegisterEnginePostInitCallback(PostInit);

        InstallCallback("screenShot",
            &screenShot, {
                cb::call(0x460A55),
                cb::call(0x462CD4),
            }
        );
    }
}
