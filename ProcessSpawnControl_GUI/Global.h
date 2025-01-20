#pragma once
#include "Imports.h"
#include "Structs.h"
namespace Global
{
	//application termination indicator
	//extern bool IsRunning;

	//process control mode
	extern bool CONTROL_ALL_MODE;

	//NtSuspendProcess and NtResumeProcess from Ntdll
	extern Ntdll NtFuncs;

	//queue for processes from WMI event
	extern ProcessQueue processQueue;

	//used to prevent relatives from being missed
	//when an event returns processes in the wrong order
	extern std::vector<StoredProc> storedProcs;
	extern DWORD eventCount;

	//list of subprocesses of the target process
	extern std::vector<ProcInfo> relatives;
}
