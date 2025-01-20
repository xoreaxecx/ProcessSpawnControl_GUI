#include "Global.h"

namespace Global
{
	//bool IsRunning = false;
	bool CONTROL_ALL_MODE = false;
	Ntdll NtFuncs;
	ProcessQueue processQueue;
	std::vector<StoredProc> storedProcs;
	DWORD eventCount = 0;
	std::vector<ProcInfo> relatives;
}
