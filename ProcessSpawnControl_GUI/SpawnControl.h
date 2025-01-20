#pragma once
#include "EventSink.h"
#include <atomic>

namespace SpawnControl
{
	enum class OperationStatus
	{
		SUCCESS,
		ERR_COINIT,
		ERR_COINIT_SEC,
		ERR_CREATE_WBEMLOC,
		ERR_CREATE_UNSECAP,
		ERR_CONNECT,
		ERR_PROXY,
		ERR_QUERY
	};

	extern std::atomic<bool> ControlEnabled;
	OperationStatus Start();
	void Stop();
}
