#include "EVOSoundHandler.h"

/*
* By default EVO1 & 2 only allocate 8 sound device structs
* This allocates 64 of them and redirects the memory
*/

const int NUM_DEVS = 64; // defaults to 8
const int DEV_MEM_SZ = 0x118;
char deviceList[NUM_DEVS * DEV_MEM_SZ] = { 0 };

bool EVOSoundHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO2 || gameType == GameType::Game_EVO || gameType == GameType::Game_EVO_ED;
}

void EVOSoundHandler::Install(GameType gameType)
{
    if (gameType == GameType::Game_EVO2)
    {
        // init device list: overwrite counter
        mem::write<byte>(0x5BF9FB + 2, NUM_DEVS);
        mem::write<byte>(0x5BFA02 + 2, NUM_DEVS);
        mem::write<byte>(0x5BFA2E + 2, NUM_DEVS);

        // write our new device list ptr
        mem::write(0x5BFA6B + 3, &deviceList); // getSoundDeviceInfo
        mem::write(0x5BFA0D + 1, &deviceList); // unk: sound init
        mem::write(0x5BF9DA + 1, &deviceList); // unk: sound init

        // and finally, in the function that assigns the device ptr
        mem::write(0x5BFCE6 + 2, &deviceList[0x100]);
        mem::write(0x5BFCF0 + 2, &deviceList[0x104]);
        mem::write(0x5BFD1C + 2, &deviceList[0x100]);
        mem::write(0x5BFD25 + 2, &deviceList[0x104]);
    }
    else if (gameType == GameType::Game_EVO)
    {
        // init device list: overwrite counter
        mem::write<byte>(0x55FB4B + 2, NUM_DEVS);
        mem::write<byte>(0x55FB52 + 2, NUM_DEVS);
        mem::write<byte>(0x55FB7E + 2, NUM_DEVS);

        // write our new device list ptr
        mem::write(0x55FBBB + 3, &deviceList); // getSoundDeviceInfo
        mem::write(0x55FB2A + 1, &deviceList); // sound init
        mem::write(0x55FB5D + 1, &deviceList); // sound init

        // and finally, in the function that assigns the device ptr
        mem::write(0x55FE36 + 2, &deviceList[0x100]);
        mem::write(0x55FE40 + 2, &deviceList[0x104]);
        mem::write(0x55FE6C + 2, &deviceList[0x100]);
        mem::write(0x55FE75 + 2, &deviceList[0x104]);
    }
    else if (gameType == GameType::Game_EVO_ED)
    {
        // init device list: overwrite counter
        mem::write<byte>(0x5B3C0B + 2, NUM_DEVS);
        mem::write<byte>(0x5B3C12 + 2, NUM_DEVS);
        mem::write<byte>(0x5B3C3E + 2, NUM_DEVS);

        // write our new device list ptr
        mem::write(0x5B3C7B + 3, &deviceList); // getSoundDeviceInfo
        mem::write(0x5B3BEA + 1, &deviceList); // unk: sound init
        mem::write(0x5B3C1D + 1, &deviceList); // unk: sound init

        // and finally, in the function that assigns the device ptr
        mem::write(0x5B3EF6 + 2, &deviceList[0x100]);
        mem::write(0x5B3F00 + 2, &deviceList[0x104]);
        mem::write(0x5B3F2C + 2, &deviceList[0x100]);
        mem::write(0x5B3F35 + 2, &deviceList[0x104]);
    }
}
