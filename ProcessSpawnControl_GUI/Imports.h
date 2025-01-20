#pragma once
#include <Windows.h>

typedef LONG(NTAPI* NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI* NtResumeProcess)(IN HANDLE ProcessHandle);

struct Ntdll
{
	NtSuspendProcess _suspend = NULL;
	NtResumeProcess _resume = NULL;
	bool Loaded = false;

	Ntdll();
	bool SuspendProcess(HANDLE hProcess);
	bool ResumeProcess(HANDLE hProcess);
};
