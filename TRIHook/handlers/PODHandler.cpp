#include "PODHandler.h"
#include <engine/engine_pod.h>
#include <game/GameSettings.h>

#if defined(TRIHOOK_GAME_EVO)
const int NumDefaultPODFiles = 26;
const char* DefaultPODFiles[] = {"STARTUP.POD","DRIVER.POD","TRUCK.POD","SOUND.POD","UI.POD","AI.POD","LIFE.POD","PARTS.POD","SERIES.POD","UITRACK.POD","ENGLISH.POD","ZONA.POD","JYARD.POD","DEVIL.POD","SHRTAIR.POD","SHTBAJA.POD","ASPEN.POD","FM109.POD","MCROSS.POD","SHTARTC.POD","THEHILL.POD","SHTSWAM.POD","ISLAND2.POD","CON2.POD","CZ2000.POD","OILFLD.POD"};
#elif defined(TRIHOOK_GAME_EVO_ED)
const int NumDefaultPODFiles = 9;
const char* DefaultPODFiles[] = { "STARTUP.POD","DRIVER.POD","TRUCK.POD","SOUND.POD","AI.POD","LIFE.POD","PARTS.POD","SERIES.POD","EDITOR.POD" };
#elif defined(TRIHOOK_GAME_EVO2)
const int NumDefaultPODFiles = 50;
const char* DefaultPODFiles[] = { "AI.POD","ALASKA.POD","ASPEN.POD","AUTUMN.POD","BAJBEACH.POD","CASTLE.POD","CMAPS-PC.POD","CON2.POD","COSTRICA.POD","CZ2000.POD","DESERT.POD","DEVIL.POD","DRIVER.POD","DUST.POD","DVALLEY.POD","EGYPT.POD","ELNORTE.POD","ENGTXT.POD","FM109.POD","ISLAND2.POD","JYARD.POD","LIFE.POD","MCROSS.POD","MEDI.POD","MUSIC.POD","OBSPARK.POD","OILFLD.POD","PARTS.POD","PEAK.POD","PS2BIG.POD","QUARRY.POD","SERIES.POD","SHRTAIR.POD","SHTARTC.POD","SHTBAJA.POD","SHTSWAM.POD","SKULL.POD","SOUND.POD","STARTUP.POD","THAI.POD","THEHILL.POD","THERIVER.POD","TIBET.POD","TRIBAJA.POD","TRUCK.POD","UI.POD","VULTURE.POD","WASH.POD","YUKON.POD","ZONA.POD" };
#else
const int NumDefaultPODFiles = 0;
const char* DefaultPODFiles[1] = { "" };
#endif

#if defined(TRIHOOK_GAME_EVO2)
const int NumDisallowedPODNames = 28;
const char* DisallowedPODFiles[] = { "BASTXT.POD","CATTXT.POD","CHITXT.POD","CROTXT.POD","CZETXT.POD","DANTXT.POD","DUTTXT.POD","ENGTXT.POD","FINTXT.POD","FRETXT.POD","GERTXT.POD","GRETXT.POD","HUNTXT.POD","INDTXT.POD","ITATXT.POD","JPNTXT.POD","KORTXT.POD","NORTXT.POD","POLTXT.POD","PORTXT.POD","RUSTXT.POD","SLOTXT.POD","SLVTXT.POD","SPATXT.POD","SWETXT.POD","THATXT.POD","TURTXT.POD","ENGTXT.POD" };
#else
const int NumDisallowedPODNames = 0;
const char* DisallowedPODFiles[1] = { "" };
#endif

static char PODMountRoot[MAX_PATH] = { 0 };

bool isModPOD(const char* name) 
{
    for (int i = 0; i < NumDefaultPODFiles; i++) 
    {
        if (!_stricmp(DefaultPODFiles[i], name)) 
        {
            return false;
        }
    }
    return true;
}

bool allowedToMountPOD(const char* name)
{
    for (int i = 0; i < NumDisallowedPODNames; i++)
    {
        if (!_stricmp(DisallowedPODFiles[i], name))
        {
            return false;
        }
    }
    return true;
}

void __stdcall MountPOD(CPod* system, const char* name)
{
    // EVO2 handles this logging by default
    if (GAME_TYPE != GameType::Game_EVO2)
    {
        hook_output_raw("Mounting POD file: %s... ", name);
    }

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO_ED)
    char error[256];
    char msg_buf[512];
    
    int res = system->CPod::mountPodVolume(name, error);
    if (GAME_TYPE != GameType::Game_EVO2)
    {
        if (res == FALSE)
        {
            sprintf(msg_buf, "FAILED: %s %s", name, error);
            hook_output_raw("%s\n", msg_buf);
        }
        else
        {
            hook_output_raw("SUCCESS\n");
        }
    }
#else
    system->mountPodVolume(name);
#endif
}

bool checkext(const char* path,const char* ext)
{
    path = strrchr(path, '.');
    if (path != nullptr)
        return(_stricmp(path, ext) == 0);
    return false;
}

void mountPods(CPod* system, LPCSTR basePath, LPCSTR pathWithFilter, bool important)
{
    WIN32_FIND_DATA ffd;
    auto hFindFile = FindFirstFileA(pathWithFilter, &ffd);
    if (hFindFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            char fileName[MAX_PATH];
            sprintf(fileName, "%s%s", basePath, ffd.cFileName);
            bool matchesImportance = (fileName[0] == '!') == important;
            
            if (matchesImportance && checkext(fileName, ".POD") && allowedToMountPOD(fileName) && isModPOD(fileName))
            {
                MountPOD(system, fileName);
            }
        } while (FindNextFileA(hFindFile, &ffd));
        FindClose(hFindFile);
    }
}

void PODHandler::mountDefaultPodFiles()
{
    auto podSystem = reinterpret_cast<CPod*>(this);

    // build path for mounting files from
    CHAR pathBuf[MAX_PATH] = { 0 };
    GetCurrentDirectoryA(MAX_PATH, pathBuf);

    strcat(pathBuf, "\\");
    strcat(pathBuf, PODMountRoot);
    if (strlen(pathBuf) > 0 && pathBuf[strlen(pathBuf) - 1] != '\\')
        strcat(pathBuf, "\\");
    strcat(pathBuf, "*.POD");

    // build base path
    CHAR basePath[MAX_PATH] = { 0 };
    strcpy(basePath, PODMountRoot);
    if (strlen(basePath) > 0 && basePath[strlen(basePath) - 1] != '\\')
        strcat(basePath, "\\");

    hook_output("Mounting additional POD files from %s...", pathBuf);
    hook_output("basePath=%s", basePath);

    // Mount language
    if (GAME_TYPE == GameType::Game_EVO2)
    {
        char languageBuf[16] = { 0 };
        sprintf(languageBuf, "%sTXT.POD", GameSettings::GetLanguage());
        hook_output("Mounting language file: %s", languageBuf);
        MountPOD(podSystem, languageBuf);
    }
    
    // Mount important POD
    mountPods(podSystem, basePath, pathBuf, true);

    // Mount default PODs
    for (int i = 0; i < NumDefaultPODFiles; i++)
    {
        MountPOD(podSystem, DefaultPODFiles[i]);
    }

    // Mount non default POD
    mountPods(podSystem, basePath, pathBuf, false);
}

bool PODHandler::IsGameSupported(GameType gameType)
{
    return true;
}

void PODHandler::Install(GameType gameType)
{
    // POD Expander : Expand max number of POD
    int maxPod = HookConfig::GetInt("General", "MaxLoadedPODs", 100);
    byte maxPodByte = (maxPod > 255) ? 255 : maxPod;
    
    // POD Init Handler: Use all PODs in folder
    if (!HookConfig::GetBool("General", "UsePODIni", true)) 
    {
        auto mountRoot = HookConfig::GetString("General", "PODMountRoot", nullptr);
        if (mountRoot != nullptr)
        {
            strcpy(PODMountRoot, mountRoot);
        }

        if (gameType == GameType::Game_EVO)
        {
            InstallVTableHook("mountDefaultPodFiles", &mountDefaultPodFiles, { 0x5EE528 });
        }
        else if (gameType == GameType::Game_EVO2)
        {
            InstallVTableHook("mountDefaultPodFiles", &mountDefaultPodFiles, { 0x666DB8 });
        }
        else if (gameType == GameType::Game_EVO_ED)
        {
            InstallVTableHook("mountDefaultPodFiles", &mountDefaultPodFiles, { 0x65E578 });
        }
    }
}
