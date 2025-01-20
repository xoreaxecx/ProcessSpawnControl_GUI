#pragma once
#include "Structs.h"

namespace Loader
{
	enum class OperationStatus
	{
		SUCCESS,
		ERR_RESOURCE,
		ERR_DL_WRITE,
		ERR_SHELL_OPEN,
		ERR_DL_NOT_FOUND,
		ERR_DL_RUN,
		ERR_LOADER_PROCESS,
		ERR_DL_EC,
		ERR_TIMEOUT,
		ERR_INVALID_PID
	};

	OperationStatus Drop(wxString loaderPath);
	OperationStatus Run(DWORD* targetPID, StartupOptions& args);
}
