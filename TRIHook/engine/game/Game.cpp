#include "Game.h"
#include "..\engine_common.h"
#include "..\engine_gfx.h"

void CGame::setGameRes()
{
    //CLevelIndicator::Done();
    //if (gOldUiFlag || !useDirect3D)
    //{
    //    if (currentBoard)
    //        APIselectCard(currentBoard);
        if ((gamePIXY != PIXY || bitsPerPixel != gameBPP) && !setScreenResolution(gamePIXX, gamePIXY, gameBPP))
        {
            gamePIXX = 640;
            gamePIXY = 480;
            if (!setScreenResolution(640, 480, gameBPP))
            {
                GTFO("CGame::setGameRes - Unable to set the video mode to %dx%dx%d", gamePIXX, gamePIXY, gameBPP);
            }
        }
    //    CMini3D::setAcceleration();
    //}
    //killFonts();
    //initFonts();
    //gMediumFont->setAcceleration(true);
}