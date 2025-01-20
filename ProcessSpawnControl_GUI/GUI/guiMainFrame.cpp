#include "guiMainFrame.h"
#include "../Global.h"
#include "../SpawnControl.h"
#include <fstream>
#include <codecvt>
#include <wx/stdpaths.h>

wxDEFINE_EVENT(wxEVT_CATCH_PROC, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_CHANGE_SIZE, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_HOTKEY_STOP, wxCommandEvent);

guiMainFrame::guiMainFrame( wxWindow* parent )
:
MainFrame( parent )
{
	IsRunning.store(false, std::memory_order_seq_cst);

	m_targetArgs_text->SetHint("Target args");
	m_parentArgs_text->SetHint("Parent args");
	m_parentPID_text->SetHint("Parent PID");

	wxIcon mainicon;
	if (mainicon.LoadFile(_T("IDI_PSC_ICON"), wxBITMAP_TYPE_ICO_RESOURCE))
	{
		if (mainicon.IsOk())
		{
			SetIcon(mainicon);
		}
	}

	SetHighPriority();
	EnableDragAndDropForAdmin();

	Bind(wxEVT_CATCH_PROC, &guiMainFrame::OnCatchProc, this);
	Bind(wxEVT_CHANGE_SIZE, &guiMainFrame::OnChangeSize, this);
	Bind(wxEVT_HOTKEY_STOP, &guiMainFrame::OnHotkey, this);
}

void guiMainFrame::Cleanup( wxCloseEvent& event )
{
	StopSpawnControl();
	RemoveLoader();
	event.Skip();
}

void guiMainFrame::ClearLog_click( wxCommandEvent& event )
{
	m_log->Clear();
}

void guiMainFrame::Start_click( wxCommandEvent& event )
{
	SetLaunchControlsEnabled(false);
	if (GetOptions(Options))
	{
		Global::CONTROL_ALL_MODE = Options.controlAll || !Options.needLoader;
		if (Options.needLoader)
		{
			Loader::OperationStatus status;
			status = Loader::Drop(Options.loaderPath);
			if (status != Loader::OperationStatus::SUCCESS)
			{
				CheckLoaderStatus(status);
				SetLaunchControlsEnabled(true);
				return;
			}

			DWORD pid = PID_DEFAULT;
			status = Loader::Run(&pid, Options);
			if (status != Loader::OperationStatus::SUCCESS)
			{
				CheckLoaderStatus(status);
				SetLaunchControlsEnabled(true);
				return;
			}

			HANDLE hTarget = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if (hTarget)
			{
				ProcInfo target = ProcInfo(pid, Options.targetName, Options.targetArgs, hTarget);
				target.IsSuspended = true;
				Global::processQueue.PushProc(target);
			}
			else
			{
				wxString err = wxT("Can not open target process with PID: ") + wxString::Format(wxT("%d"), pid);
				LogError(err);
				SetLaunchControlsEnabled(true);
				return;
			}
		}

		IsRunning.store(true, std::memory_order_seq_cst);
		Searcher = std::thread(&guiMainFrame::SearcherTask, this);
		Worker = std::thread(&guiMainFrame::WorkerTask, this);

		int timeoutCount = 0;
		while (!SpawnControl::ControlEnabled.load(std::memory_order_seq_cst));
		{
			Sleep(100);
			if (++timeoutCount > 50)
			{
				LogError(wxT("Spawn control start timeout expired."));
				SetLaunchControlsEnabled(true);
				return;
			}
		}

		HotKeyStop = std::thread(&guiMainFrame::HotKeyStopTask, this);
		m_stop_btn->Enable(true);
		LogMessage(wxT("=========================="), true, blue);
		LogMessage(wxT("Spawn control started.\nPress CTRL + ALT + Q to stop spawn control."));
	}
	else
	{
		SetLaunchControlsEnabled(true);
	}
}

void guiMainFrame::Stop_click( wxCommandEvent& event )
{
	StopSpawnControl();
}

void guiMainFrame::Clear_click( wxCommandEvent& event )
{
	m_target_filePicker->SetPath(wxString(L""));
	m_targetArgs_text->Clear();
	m_parent_filePicker->SetPath(wxString(L""));
	m_parentArgs_text->Clear();
	m_parentPID_text->Clear();
	m_asExplorer_chb->SetValue(false);
	m_controlAll_chb->SetValue(false);
}

void guiMainFrame::SetTargetDropPath( wxDropFilesEvent& event )
{
	m_target_filePicker->SetPath(event.m_files->ToStdWstring());
}

void guiMainFrame::SetParentDropPath( wxDropFilesEvent& event )
{
	m_parent_filePicker->SetPath(event.m_files->ToStdWstring());
}

void guiMainFrame::AlwaysOnTop_Check( wxCommandEvent& event )
{
	long flags = this->GetWindowStyleFlag();
	if (m_stayOnTop_chb->GetValue())
	{
		this->SetWindowStyleFlag(flags | wxSTAY_ON_TOP);
	}
	else
	{
		this->SetWindowStyleFlag(flags & ~wxSTAY_ON_TOP);
	}
}

void guiMainFrame::SetExclusionsDropPath( wxDropFilesEvent& event )
{
	m_exclusions_filePicker->SetPath(event.m_files->ToStdWstring());
}

void guiMainFrame::LoadExclusions_click( wxCommandEvent& event )
{
	if (!m_exclusions_filePicker->GetPath().IsEmpty())
	{
		std::wifstream  file(m_exclusions_filePicker->GetPath().ToStdWstring());
		if (file.good())
		{
			file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
			std::wstring line;
			while (std::getline(file, line))
			{
				wxString exclusion(line);
				AddExclusion(exclusion, false);
			}
		}
		else
		{
			LogError(wxT("Can not open file: " + m_exclusions_filePicker->GetPath()));
		}

		m_exclusions_filePicker->SetPath(wxString(L""));
	}
}

void guiMainFrame::AddExclusion_click( wxCommandEvent& event )
{
	wxString text = m_exclusion_text->GetValue();
	if (AddExclusion(text))
	{
		m_exclusion_text->Clear();
	}
}

void guiMainFrame::DeleteExclusion_click( wxCommandEvent& event )
{
	DeleteExclusion();
}

void guiMainFrame::AddExclusion_enter( wxCommandEvent& event )
{
	wxString text = m_exclusion_text->GetValue();
	if (AddExclusion(text))
	{
		m_exclusion_text->Clear();
	}
}

void guiMainFrame::Exclusions_doubleClick( wxCommandEvent& event )
{
	int idx = m_exclusions_listBox->GetSelection();
	if (idx != wxNOT_FOUND)
	{
		m_exclusions_listBox->Delete(idx);
	}
}


void guiMainFrame::OnChangeSize(wxCommandEvent& event)
{
	wxSizer* sz = m_procWindow->GetSizer();
	int count = sz->GetItemCount();
	m_procCount_text->SetLabelText(wxString::Format(wxT("%d"), count));
}

void guiMainFrame::SetLaunchControlsEnabled(bool enabled)
{
	enabled ? this->SetTitle(wxT("")) : this->SetTitle(wxT("RUNNING"));

	m_start_btn->Enable(enabled);
	m_clearArgs_btn->Enable(enabled);
	m_target_filePicker->Enable(enabled);
	m_targetArgs_text->Enable(enabled);
	m_parent_filePicker->Enable(enabled);
	m_parentArgs_text->Enable(enabled);
	m_parentPID_text->Enable(enabled);
	m_asExplorer_chb->Enable(enabled);
	m_controlAll_chb->Enable(enabled);
}

void guiMainFrame::LogAddProcItem(wxString procDesc)
{
	LogMessage(wxT("New suspended:"), true, green);
	LogMessage(procDesc);
}

void guiMainFrame::DeleteExclusion()
{
	if (m_exclusions_listBox->GetCount())
	{
		int idx = m_exclusions_listBox->GetSelection();
		if (idx == wxNOT_FOUND)
		{
			idx = m_exclusions_listBox->GetTopItem();
			if (idx != wxNOT_FOUND)
			{
				m_exclusions_listBox->Delete(idx);
			}
		}
		else
		{
			m_exclusions_listBox->Delete(idx);
		}
	}
}

void guiMainFrame::AddProcItem(ProcInfo proc)
{
	wxSizer* sz = m_procWindow->GetSizer();
	ProcessWidget* pw = new ProcessWidget(m_procWindow, proc);
	sz->Add(pw, 0, wxEXPAND | wxALL, 2);
	pw->ShrinkSelf();
	pw->ShowSelf();
	m_procWindow->FitInside();
	m_procWindow->FitInside();
	LogAddProcItem(pw->GetProcDescription(true));

	wxCommandEvent evt(wxEVT_CHANGE_SIZE, wxID_ANY);
	this->AddPendingEvent(evt);
}

bool guiMainFrame::AddExclusion(wxString exclusion, bool selectDuplicate)
{
	if (!exclusion.IsEmpty())
	{
		wxString ex = exclusion.Lower();
		int found = m_exclusions_listBox->FindString(ex, true);
		if (found == wxNOT_FOUND)
		{
			m_exclusions_listBox->Insert(ex, 0);
		}
		else if (selectDuplicate)
		{
			m_exclusions_listBox->Select(found);
		}

		return true;
	}

	return false;
}

void guiMainFrame::CheckLoaderStatus(Loader::OperationStatus status)
{
	wxString err = wxT("Loader error: ");
	switch (status)
	{
	case Loader::OperationStatus::ERR_RESOURCE:
		err += wxT("can not load resource.");
		break;
	case Loader::OperationStatus::ERR_DL_WRITE:
		err += wxT("can not write to file at path: ") + Options.loaderPath;
		break;
	case Loader::OperationStatus::ERR_SHELL_OPEN:
		err += wxT("can not open shell process.");
		break;
	case Loader::OperationStatus::ERR_DL_NOT_FOUND:
		err += wxT("can not access from path: ") + Options.loaderPath;
		break;
	case Loader::OperationStatus::ERR_DL_RUN:
		err += wxT("can not run from path: ") + Options.loaderPath;
		break;
	case Loader::OperationStatus::ERR_LOADER_PROCESS:
		err += wxT("can not create loader process.");
		break;
	case Loader::OperationStatus::ERR_DL_EC:
		err += wxT("can not receive exit code.");
		break;
	case Loader::OperationStatus::ERR_TIMEOUT:
		err += wxT("timeout expired.\nMay be caused by an antivirus.");
		break;
	case Loader::OperationStatus::ERR_INVALID_PID:
		err += wxT("invalid target PID received.");
		break;
	default:
		err += wxT("unknown error.");
		break;
	}
	LogError(err);
}

void guiMainFrame::CheckSpawnControlStatus(SpawnControl::OperationStatus status)
{
	wxString err = wxT("SpawnControl error: ");
	switch (status)
	{
	case SpawnControl::OperationStatus::ERR_COINIT:
		err += wxT("CoInitializeEx failed.");
		break;
	case SpawnControl::OperationStatus::ERR_COINIT_SEC:
		err += wxT("CoInitializeSecurity failed.");
		break;
	case SpawnControl::OperationStatus::ERR_CREATE_WBEMLOC:
		err += wxT("can not create IWbemLocator object.");
		break;
	case SpawnControl::OperationStatus::ERR_CONNECT:
		err += wxT("can not connect to ROOT\\CIMV2 WMI namespace.");
		break;
	case SpawnControl::OperationStatus::ERR_PROXY:
		err += wxT("can not set proxy blanket.");
		break;
	case SpawnControl::OperationStatus::ERR_CREATE_UNSECAP:
		err += wxT("can not create IUnsecuredApartment object.");
		break;
	case SpawnControl::OperationStatus::ERR_QUERY:
		err += wxT("ExecNotificationQueryAsync failed.");
		break;
	default:
		err += wxT("unknown error.");
		break;
	}
	LogError(err);
}

bool guiMainFrame::ContainExclusion(wxString procName)
{
	int found = m_exclusions_listBox->FindString(procName, true);
	return found != wxNOT_FOUND;
}

void guiMainFrame::LogMessage(wxString message, bool highlight, wxColour colour)
{
	m_log->MoveEnd();
	m_log->BeginParagraphSpacing(0, 0);

	if (highlight)
	{
		m_log->BeginTextColour(colour);
	}

	m_log->WriteText(message + wxT("\n"));

	if (highlight)
	{
		m_log->EndTextColour();
	}

	if (m_autoscroll_chb->GetValue())
	{
		m_log->ShowPosition(m_log->GetLastPosition());
	}

	m_log->EndParagraphSpacing();
}

bool guiMainFrame::GetOptions(StartupOptions& options)
{
	options = StartupOptions();
	wxString parentPID = m_parentPID_text->GetValue();
	if (!parentPID.IsEmpty())
	{
		long check_val;
		if (parentPID.ToLong(&check_val))
		{
			options.parentPID = parentPID;
		}
		else
		{
			wxString err = wxT("Invalid parent PID value: ") + parentPID;
			LogError(err);
			return false;
		}
	}

	wxString targetPath = m_target_filePicker->GetPath();
	if (!targetPath.IsEmpty())
	{
		if (wxFileExists(targetPath))
		{
			options.needLoader = true;
			options.targetPath = targetPath;
			wxFileName tp(targetPath);
			options.workingDir = tp.GetPath();
			options.targetName = tp.GetFullName();
			options.targetArgs = m_targetArgs_text->GetValue();
		}
		else
		{
			wxString err = wxT("Can not access target file: ") + targetPath;
			LogError(err);
			return false;
		}
	}

	wxString parentPath = m_parent_filePicker->GetPath();
	if (!parentPath.IsEmpty())
	{
		if (wxFileExists(parentPath))
		{
			options.parentPath = parentPath;
			options.parentArgs = m_parentArgs_text->GetValue();
			if (!options.parentPID.empty())
			{
				options.parentPID = wxT("");
				LogError(wxT("Parent PID is ignored."));
			}
		}
		else
		{
			wxString err = wxT("Can not access parent file: ") + parentPath;
			LogError(err);
			return false;
		}
	}

	options.asExplorer = m_asExplorer_chb->GetValue();
	options.controlAll = m_controlAll_chb->GetValue();
	wxFileName loaderPath (wxStandardPaths::Get().GetExecutablePath());
	options.loaderPath = loaderPath.GetPath() + wxT("\\DL.exe");

	return true;
}

void guiMainFrame::LogError(wxString err)
{
	m_log->MoveEnd();
	m_log->BeginParagraphSpacing(0, 0);
	m_log->BeginTextColour(red);
	m_log->WriteText(err + wxT("\n"));
	m_log->EndTextColour();
	if (m_autoscroll_chb->GetValue())
	{
		m_log->ShowPosition(m_log->GetLastPosition());
	}
	m_log->EndParagraphSpacing();
}

void guiMainFrame::StopSpawnControl()
{
	if (IsRunning.load(std::memory_order_seq_cst))
	{
		IsRunning.store(false, std::memory_order_seq_cst);
		SpawnControl::Stop();

		if (Worker.joinable())
		{
			Worker.join();
		}
		if (Searcher.joinable())
		{
			Searcher.join();
		}
		if (HotKeyStop.joinable())
		{
			HotKeyStop.join();
		}

		ClearProcItems();
		ClearProcQueue();
		SetLaunchControlsEnabled(true);
		m_stop_btn->Enable(false);
		LogMessage(wxT("Spawn control stopped."));
		LogMessage(wxT("==========================\n"), true, blue);
	}
}

void guiMainFrame::OnHotkey(wxCommandEvent& event)
{
	LogMessage(wxT("Stop hotkey pressed."));
	StopSpawnControl();
}

void guiMainFrame::OnCatchProc(wxThreadEvent& event)
{
	ProcInfo proc = event.GetPayload<ProcInfo>();
	if (!proc.IsEmpty)
	{
		
		if (proc.IsExclusion)
		{
			wxString pid = wxString::Format(wxT("%d"), proc.ProcessId);
			wxString message = wxT("Ignored: (") + pid + wxT(") ") + proc.PrintableName + wxT(" as exclusion.");
			LogMessage(message, true, yellow);
		}
		else if (!proc.IsSuspended)
		{
			if (proc.Handle == NULL)
			{
				wxString pid = wxString::Format(wxT("%d"), proc.ProcessId);
				wxString err = wxT("Can not open process for suspension: (") + pid + wxT(") ") + proc.PrintableName;
				LogError(err);
			}
			else
			{
				wxString pid = wxString::Format(wxT("%d"), proc.ProcessId);
				wxString err = wxT("Can not suspend: (") + pid + wxT(") ") + proc.PrintableName;
				LogError(err);
			}
		}
		else
		{
			wxSizer* sz = m_procWindow->GetSizer();
			int count = sz->GetItemCount();
			if (count >= 100)
			{
				StopSpawnControl();
				wxString err = wxT("Spawn control has been stopped due to the process limit being reached.");
				LogError(err);
			}
			else
			{
				AddProcItem(proc);
			}
		}
	}
}

void guiMainFrame::EnableDragAndDropForAdmin()
{
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x49 /*WM_COPYGLOBALDATA*/, MSGFLT_ADD);
}

void guiMainFrame::SetHighPriority()
{
	BOOL ok = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	if (ok)
	{
		LogMessage(wxT("High priority is set."));
	}
	else
	{
		LogError(wxT("Can not set high priority."));
	}
}

void guiMainFrame::WorkerTask()
{
	while (IsRunning.load(std::memory_order_seq_cst))
	{
		if (!Global::processQueue.Empty())
		{
			ProcInfo proc = Global::processQueue.PopProc();
			wxThreadEvent evt(wxEVT_CATCH_PROC, wxID_ANY);
			evt.SetPayload<ProcInfo>(proc);
			this->AddPendingEvent(evt);
		}

		Sleep(200);
	}
}

void guiMainFrame::SearcherTask()
{
	SpawnControl::OperationStatus status;
	status = SpawnControl::Start();
	if (status != SpawnControl::OperationStatus::SUCCESS)
	{
		ClearProcQueue();
		CheckSpawnControlStatus(status);
		SetLaunchControlsEnabled(true);
		return;
	}

	while (IsRunning.load(std::memory_order_seq_cst))
	{
		if (!SpawnControl::ControlEnabled.load(std::memory_order_seq_cst))
		{
			return;
		}

		Sleep(200);
	}
}

void guiMainFrame::HotKeyStopTask()
{
	if (::RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x51)) // CTRL + ALT + Q
	{
		MSG msg;
		while (IsRunning.load(std::memory_order_seq_cst))
		{
			if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_HOTKEY)
				{
					wxCommandEvent evt(wxEVT_HOTKEY_STOP, wxID_ANY);
					this->AddPendingEvent(evt);
				}
			}

			Sleep(200);
		}

		::UnregisterHotKey(NULL, 1);
	}
}

void guiMainFrame::ClearProcQueue()
{
	if (!Global::processQueue.Empty())
	{
		while (!Global::processQueue.Empty())
		{
			ProcInfo p = Global::processQueue.PopProc();
			Global::NtFuncs.ResumeProcess(p.Handle);
			CloseHandle(p.Handle);
		}
	}
}

void guiMainFrame::ClearProcItems()
{
	wxSizer* sz = m_procWindow->GetSizer();
	size_t count = sz->GetItemCount();
	if (count > 0)
	{
		wxSizerItemList items = sz->GetChildren();
		for (int i = count - 1; i >= 0; i--)
		{
			wxSizerItem* item = sz->GetItem(i);
			ProcessWidget* pw = (ProcessWidget*)item->GetSizer();
			pw->DeleteSelf(true);
		}
	}
}

void guiMainFrame::RemoveLoader()
{
	if (!Options.loaderPath.empty())
	{
		if (wxFileExists(Options.loaderPath))
		{
			wxRemoveFile(Options.loaderPath);
		}
	}
}
