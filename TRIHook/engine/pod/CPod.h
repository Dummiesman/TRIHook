#pragma once
#include <cstdio>
#include <trihook/trihook.h>

class CPod
{
public:
	CPod();
	virtual ~CPod();
	
	virtual void __cdecl mountDefaultPodFiles();
	virtual int __cdecl getFileInfo(void* info);
	virtual	int __cdecl mountPodVolume(const char* name, char* returnErrMsg);
	virtual	void __cdecl unmountPodVolume(const char* name);
	virtual void __cdecl remountAllPods();
};