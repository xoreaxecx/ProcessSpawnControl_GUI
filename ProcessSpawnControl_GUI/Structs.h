#pragma once
#include <string>
#include <queue>
#include <Windows.h>
#include <wx/string.h>

#define PID_DEFAULT 0

struct StartupOptions
{
	bool needLoader;
	bool controlAll;
	bool asExplorer;
	wxString parentPID;
	wxString targetName;
	wxString targetPath;
	wxString targetArgs;
	wxString parentPath;
	wxString parentArgs;
	wxString loaderPath;
	wxString workingDir;

	StartupOptions()
	{
		needLoader = false;
		controlAll = false;
		asExplorer = false;
	}
};

struct ParentProcInfo
{
	bool IsEmpty;
	DWORD ProcessId;
	wxString Name;
	wxString PrintableName;
	wxString Command;
	ParentProcInfo() { ProcessId = PID_DEFAULT; IsEmpty = true; }
	ParentProcInfo(DWORD PID) { ProcessId = PID; IsEmpty = PID == PID_DEFAULT; }
	ParentProcInfo(DWORD PID, wxString name, wxString command)
	{
		IsEmpty = PID == PID_DEFAULT;
		ProcessId = PID;
		Name = name.Lower();
		PrintableName = name;
		Command = command;
	}
};

struct ProcInfo
{
	bool IsEmpty;
	bool IsSuspended;
	int IsExclusion;
	DWORD ProcessId;
	wxString Name;
	wxString PrintableName;
	wxString Command;
	HANDLE Handle;
	ParentProcInfo Parent;
	ProcInfo() { ProcessId = PID_DEFAULT; Handle = NULL; Parent = ParentProcInfo(); IsEmpty = true; IsSuspended = false; }
	ProcInfo(DWORD PID, wxString name, wxString command, HANDLE handle = NULL, ParentProcInfo parent = ParentProcInfo())
	{
		IsEmpty = PID == PID_DEFAULT;
		IsSuspended = false;
		IsExclusion = false;
		ProcessId = PID;
		Handle = handle;
		Name = name.Lower();
		PrintableName = name;
		Command = command;
		Parent = parent;
	}
};

struct StoredProc
{
	DWORD EventNumber;
	ProcInfo Proc;
	StoredProc(DWORD eventNumber, ProcInfo proc)
	{
		EventNumber = eventNumber;
		Proc = proc;
	}
};

struct ProcessQueue
{
	CRITICAL_SECTION _cs;
	std::queue<ProcInfo> _q;

	ProcessQueue()
	{
		InitializeCriticalSection(&_cs);
	}

	void Clear()
	{
		EnterCriticalSection(&_cs);
		_q = {};
		LeaveCriticalSection(&_cs);
	}

	void PushProc(ProcInfo proc)
	{
		EnterCriticalSection(&_cs);
		_q.push(proc);
		LeaveCriticalSection(&_cs);
	}

	ProcInfo PopProc()
	{
		ProcInfo proc;
		if (!_q.empty())
		{
			EnterCriticalSection(&_cs);
			proc = _q.front();
			_q.pop();
			LeaveCriticalSection(&_cs);
		}

		return proc;
	}

	DWORD Size()
	{
		return _q.size();
	}

	ProcInfo Front()
	{
		if (_q.empty())
			return ProcInfo();
		else
			return _q.front();
	}

	ProcInfo Back()
	{
		if (_q.empty())
			return ProcInfo();
		else
			return _q.back();
	}

	bool Empty()
	{
		return _q.empty();
	}
};
