#include "Imports.h"

Ntdll::Ntdll()
{
	HMODULE hNtdll = GetModuleHandleW(L"ntdll");
	if (hNtdll != NULL)
	{
		_suspend = (NtSuspendProcess)GetProcAddress(hNtdll, "NtSuspendProcess");;
		_resume = (NtResumeProcess)GetProcAddress(hNtdll, "NtResumeProcess");;
	}

	Loaded = (_suspend != NULL && _resume != NULL);
}

bool Ntdll::SuspendProcess(HANDLE hProcess)
{
	LONG ok = -1;
	if (Loaded)
		ok = _suspend(hProcess);

	return ok == 0;
}

bool Ntdll::ResumeProcess(HANDLE hProcess)
{
	LONG ok = -1;
	if (Loaded)
		ok = _resume(hProcess);

	return ok == 0;
}
