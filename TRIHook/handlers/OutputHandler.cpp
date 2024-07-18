#include "OutputHandler.h"

LONG NTAPI VexHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
    PEXCEPTION_RECORD ExceptionRecord = ExceptionInfo->ExceptionRecord;

    switch (ExceptionRecord->ExceptionCode)
    {
    case DBG_PRINTEXCEPTION_C:

        if (ExceptionRecord->NumberParameters >= 2)
        {
            ULONG len = (ULONG)ExceptionRecord->ExceptionInformation[0];

            union {
                ULONG_PTR up;
                PCWSTR pwz;
                PCSTR psz;
            };

            up = ExceptionRecord->ExceptionInformation[1];

            HANDLE hOut = GetStdHandle(STD_ERROR_HANDLE);

            if (ExceptionRecord->ExceptionCode == DBG_PRINTEXCEPTION_C)
            {
                hook_output_raw("%s", psz);
            }

        }
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

bool OutputHandler::IsGameSupported(GameType gameType)
{
    return true;
}

void OutputHandler::Install(GameType gameType)
{
    AddVectoredExceptionHandler(TRUE, VexHandler);
}
