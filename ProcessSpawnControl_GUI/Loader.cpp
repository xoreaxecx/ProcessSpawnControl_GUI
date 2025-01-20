#include "gui/guiMainFrame.h"
#include "Loader.h"
#include "resource.h"

namespace Loader
{
    OperationStatus Drop(wxString loaderPath)
    {
        OperationStatus result = OperationStatus::SUCCESS;

        if (!wxFileExists(loaderPath))
        {
            HRSRC hRes = NULL;
            HGLOBAL hMemory = NULL;
            PBYTE data = NULL;
            size_t dataSz = 0;
            HMODULE hModule = GetModuleHandleW(NULL);

            hRes = FindResourceW(hModule, MAKEINTRESOURCEW(IDR_BIN1), L"BIN");
            if (hRes != NULL)
            {
                hMemory = LoadResource(hModule, hRes);
                dataSz = SizeofResource(hModule, hRes);
                if (hMemory != NULL)
                {
                    data = (PBYTE)LockResource(hMemory);
                }
            }

            if (data == NULL || dataSz == 0)
            {
                result = OperationStatus::ERR_RESOURCE;
            }
            else
            {
                FILE* file;
                errno_t err = _wfopen_s(&file, loaderPath.wc_str(), L"wb");
                if (file == NULL || err)
                {
                    result = OperationStatus::ERR_DL_WRITE;
                }
                else
                {
                    fwrite(data, sizeof(data[0]), dataSz, file);
                    fclose(file);
                }
            }
        }

        return result;
    }

    OperationStatus RunAsOwnSub(LPWSTR loaderCommand, LPWSTR workingDir, HANDLE& hProcess, DWORD& pid)
    {
        OperationStatus status = OperationStatus::SUCCESS;
        STARTUPINFOW si;
        PROCESS_INFORMATION pi;

        SecureZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        SecureZeroMemory(&pi, sizeof(pi));

        if (CreateProcessW(NULL, loaderCommand, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, workingDir, &si, &pi))
        {
            hProcess = pi.hProcess;
            pid = pi.dwProcessId;
            CloseHandle(pi.hThread);
        }
        else
        {
            status = OperationStatus::ERR_LOADER_PROCESS;
        }

        return status;
    }

    OperationStatus RunAsExplorer(LPWSTR loaderCommand, LPWSTR workingDir, HANDLE& hProcess, DWORD& pid)
    {
        OperationStatus status = OperationStatus::SUCCESS;

        DWORD shellPID = 0;
        GetWindowThreadProcessId(GetShellWindow(), &shellPID);
        HANDLE hShell = OpenProcess(PROCESS_CREATE_PROCESS, FALSE, shellPID);
        if (hShell == NULL)
        {
            return OperationStatus::ERR_SHELL_OPEN;
        }

        SIZE_T size = 0;
        //get required size
        InitializeProcThreadAttributeList(NULL, 1, 0, &size);

        STARTUPINFOEX si = { sizeof(si) };
        SecureZeroMemory(&si, sizeof(si));
        si.StartupInfo.cb = sizeof(STARTUPINFOEX);
        char* siBuff = new char[size] { 0 };
        si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)siBuff;
        //allocate buffer with required size
        InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, &size);
        //add parent attribute
        UpdateProcThreadAttribute(si.lpAttributeList,
            0,
            PROC_THREAD_ATTRIBUTE_PARENT_PROCESS,
            &hShell,
            sizeof(hShell),
            NULL,
            NULL);

        PROCESS_INFORMATION pi;
        RtlSecureZeroMemory(&pi, sizeof(pi));

        BOOL created = CreateProcessW(NULL,
            loaderCommand,
            NULL,
            NULL,
            FALSE,
            NORMAL_PRIORITY_CLASS | EXTENDED_STARTUPINFO_PRESENT,
            NULL,
            workingDir,
            (STARTUPINFO*)&si,
            &pi);
        
        if (created)
        {
            hProcess = pi.hProcess;
            pid = pi.dwProcessId;
            CloseHandle(pi.hThread);
        }
        else
        {
            status = OperationStatus::ERR_LOADER_PROCESS;
        }

        CloseHandle(hShell);
        DeleteProcThreadAttributeList(si.lpAttributeList);
        delete[] si.lpAttributeList;
        return status;
    }

    std::wstring GetCommand(StartupOptions& args)
    {
        std::wstring cmd = args.loaderPath.ToStdWstring() + L" -tp \"" + args.targetPath.ToStdWstring() + L"\"";
        if (!args.targetArgs.empty())
        {
            cmd += L" -ta \"" + args.targetArgs.ToStdWstring() + L"\"";
        }
        if (!args.parentPath.empty())
        {
            cmd += L" -pp \"" + args.parentPath.ToStdWstring() + L"\"";
        }
        if (!args.parentArgs.empty())
        {
            cmd += L" -pa \"" + args.parentArgs.ToStdWstring() + L"\"";
        }
        if (!args.parentPID.empty())
        {
            cmd += L" -pi \"" + args.parentPID.ToStdWstring() + L"\"";
        }

        return cmd;
    }

    OperationStatus Run(DWORD* targetPID, StartupOptions& args)
    {
        OperationStatus status = OperationStatus::SUCCESS;
        HANDLE hLoader = NULL;
        DWORD pidLoader = PID_DEFAULT;
        std::wstring command = GetCommand(args);
        
        if (!wxFileExists(args.loaderPath))
        {
            status = OperationStatus::ERR_DL_NOT_FOUND;
        }
        else
        {
            if (args.asExplorer)
            {
                status = RunAsExplorer(const_cast<LPWSTR>(command.c_str()), const_cast<LPWSTR>(args.workingDir.wc_str()), hLoader, pidLoader);
            }
            else
            {
                status = RunAsOwnSub(const_cast<LPWSTR>(command.c_str()), const_cast<LPWSTR>(args.workingDir.wc_str()), hLoader, pidLoader);
            }

            if (status != OperationStatus::SUCCESS || hLoader == NULL || pidLoader == PID_DEFAULT)
            {
                status = OperationStatus::ERR_LOADER_PROCESS;
            }
            else
            {
                WaitForSingleObject(hLoader, 10000);
                if (GetExitCodeProcess(hLoader, targetPID) == FALSE)
                {
                    CloseHandle(hLoader);
                    status = OperationStatus::ERR_DL_EC;
                }
                else if (*targetPID == STILL_ACTIVE)
                {
                    HANDLE hStillRunning = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pidLoader);
                    if (hStillRunning)
                    {
                        CloseHandle(hStillRunning);
                        CloseHandle(hLoader);
                        status = OperationStatus::ERR_TIMEOUT;
                    }
                }
            }
        }

        if (status == OperationStatus::SUCCESS && *targetPID == PID_DEFAULT)
        {
            status = OperationStatus::ERR_INVALID_PID;
        }

        return status;
    }
}
