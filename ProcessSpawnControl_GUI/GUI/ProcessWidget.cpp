#include "../ProcessSpawnControl_GUI.h"
#include "../Imports.h"
#include <wx/clipbrd.h>

ProcessWidget::ProcessWidget(wxWindow* parent, ProcInfo proc) : wxBoxSizer(wxVERTICAL)
{
	m_parent = parent;
	_proc = proc;

	wxGridBagSizer* proc_sizer;
	proc_sizer = new wxGridBagSizer(0, 0);
	proc_sizer->SetFlexibleDirection(wxBOTH);
	proc_sizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	proc_panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1, 1), wxBORDER_RAISED);
	proc_panel->Hide();
	proc_panel->SetInitialSize();
	proc_panel->SetBackgroundColour(wxColour(150, 150, 150));
	
	btn_close = new wxButton(proc_panel, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0);
	btn_close->SetLabelMarkup(wxT("X"));
	btn_close->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	btn_close->SetBackgroundColour(wxColour(255, 0, 0));
	btn_close->SetMinSize(wxSize(20, 20));
	proc_sizer->Add(btn_close, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALIGN_RIGHT | wxRIGHT | wxTOP, 2);

	copy_btn = new wxButton(proc_panel, wxID_ANY, wxT("COPY INFO"), wxDefaultPosition, wxDefaultSize, 0);
	copy_btn->SetLabelMarkup(wxT("COPY INFO"));
	copy_btn->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	copy_btn->SetBackgroundColour(wxColour(200, 200, 200));
	copy_btn->SetMinSize(wxSize(75, 20));
	proc_sizer->Add(copy_btn, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxTOP, 2);

	kill_btn = new wxButton(proc_panel, wxID_ANY, wxT("KILL"), wxDefaultPosition, wxDefaultSize, 0);
	kill_btn->SetLabelMarkup(wxT("KILL"));
	kill_btn->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	kill_btn->SetBackgroundColour(wxColour(255, 200, 200));
	kill_btn->SetMinSize(wxSize(60, 20));
	proc_sizer->Add(kill_btn, wxGBPosition(3, 2), wxGBSpan(1, 1), wxALIGN_RIGHT | wxBOTTOM | wxRIGHT, 2);

	ignore_btn = new wxButton(proc_panel, wxID_ANY, wxT("IGNORE"), wxDefaultPosition, wxDefaultSize, 0);
	ignore_btn->SetLabelMarkup(wxT("IGNORE"));
	ignore_btn->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	ignore_btn->SetBackgroundColour(wxColour(240, 240, 140));
	ignore_btn->SetMinSize(wxSize(60, 20));
	proc_sizer->Add(ignore_btn, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 2);

	run_btn = new wxButton(proc_panel, wxID_ANY, wxT("RUN"), wxDefaultPosition, wxDefaultSize, 0);
	run_btn->SetLabelMarkup(wxT("RUN"));
	run_btn->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
	run_btn->SetBackgroundColour(wxColour(150, 245, 140));
	run_btn->SetMinSize(wxSize(60, 20));
	proc_sizer->Add(run_btn, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxBOTTOM | wxLEFT, 2);

	pin_checkbox = new wxCheckBox(proc_panel, wxID_ANY, wxT("pin"), wxDefaultPosition, wxDefaultSize, 0);
	pin_checkbox->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));
	pin_checkbox->SetMinSize(wxSize(-1, 15));
	proc_sizer->Add(pin_checkbox, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxLEFT | wxTOP, 2);

	wxBoxSizer* info_sizer;
	info_sizer = new wxBoxSizer(wxVERTICAL);

	wxString proc_pid_str = proc.ProcessId != PID_DEFAULT ? wxString::Format(wxT("%d"), proc.ProcessId) : wxT("---");
	wxString proc_info = wxT("proc: (") + proc_pid_str + wxT(") ") + proc.PrintableName;
	proc_text = new wxTextCtrl(proc_panel, wxID_ANY, proc_info, wxDefaultPosition, wxDefaultSize, 0);
	proc_text->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));
	proc_text->SetBackgroundColour(wxColour(200, 200, 200));
	proc_text->Enable(false);
	proc_text->SetMaxSize(wxSize(-1, 20));
	info_sizer->Add(proc_text, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
	
	wxString args_info = wxT("cmd : ") + _proc.Command;
	args_text = new wxTextCtrl(proc_panel, wxID_ANY, args_info, wxDefaultPosition, wxDefaultSize, 0);
	args_text->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));
	args_text->SetBackgroundColour(wxColour(200, 200, 200));
	args_text->Enable(false);
	args_text->SetMaxSize(wxSize(-1, 20));
	info_sizer->Add(args_text, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);

	wxString parent_pid_str = proc.Parent.ProcessId != PID_DEFAULT ? wxString::Format(wxT("%d"), proc.Parent.ProcessId) : wxT("---");
	wxString parent_info = wxT("prnt: (") + parent_pid_str + wxT(") ") + proc.Parent.PrintableName;
	parent_text = new wxTextCtrl(proc_panel, wxID_ANY, parent_info, wxDefaultPosition, wxDefaultSize, 0);
	parent_text->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString));
	parent_text->SetBackgroundColour(wxColour(200, 200, 200));
	parent_text->Enable(false);
	parent_text->SetMaxSize(wxSize(-1, 20));
	info_sizer->Add(parent_text, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);

	proc_sizer->Add(info_sizer, wxGBPosition(1, 0), wxGBSpan(2, 3), wxEXPAND, 5);

	proc_sizer->AddGrowableCol(0);
	proc_sizer->AddGrowableCol(1);
	proc_sizer->AddGrowableCol(2);

	proc_panel->SetSizer(proc_sizer);
	proc_sizer->Fit(proc_panel);
	Add(proc_panel, 0, wxLEFT | wxRIGHT | wxEXPAND, 2);
	
	//btn_close->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ProcessWidget::delete_entry), NULL, this);
	run_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ProcessWidget::Run_click, this);
	kill_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ProcessWidget::Kill_click, this);
	btn_close->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ProcessWidget::DeleteEntry_click, this);
	copy_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ProcessWidget::CopyInfo_click, this);
	ignore_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &ProcessWidget::Ignore_click, this);
}

ProcessWidget::~ProcessWidget() {}

void ProcessWidget::HideSelf()
{
	proc_panel->Hide();
}

void ProcessWidget::ShowSelf()
{
	proc_panel->Show();
}

void ProcessWidget::ShrinkSelf()
{
	proc_panel->SetSize(wxSize(1, 1));
}

void ProcessWidget::SetInitSize()
{
	proc_panel->SetInitialSize();
}

void ProcessWidget::DeleteSelf(bool resume)
{
	if (!_proc.IsEmpty &&_proc.Handle && (_proc.Handle != INVALID_HANDLE_VALUE))
	{
		if (resume && !ProcessResumed)
		{
			Global::NtFuncs.ResumeProcess(_proc.Handle);
		}

		CloseHandle(_proc.Handle);
		_proc.Handle = NULL;
	}

	bool hasScrollBefore = m_parent->HasScrollbar(wxVERTICAL);
	wxApp* app = wxTheApp;
	app->ScheduleForDestruction(this->proc_panel);
	HideSelf();
	m_parent->FitInside();

	bool hasScrollAfter = m_parent->HasScrollbar(wxVERTICAL);
	if (hasScrollBefore && !hasScrollAfter)
	{
		m_parent->Refresh();
	}

	m_parent->GetSizer()->Remove(this);
	wxCommandEvent evt(wxEVT_CHANGE_SIZE, wxID_ANY);
	wxGetApp().frame->GetEventHandler()->AddPendingEvent(evt);
}

void ProcessWidget::DeleteEntry_click(wxCommandEvent& event)
{
	DeleteSelf();
}

void ProcessWidget::CopyInfo_click(wxCommandEvent& event)
{
	if (wxTheClipboard->Open())
	{
		wxString info = GetProcDescription(true);
		wxTheClipboard->SetData(new wxTextDataObject(info));
		wxTheClipboard->Close();
	}
	else
	{
		wxGetApp().frame->LogError(wxT("Can not open clipboard."));
	}
}

void ProcessWidget::Ignore_click(wxCommandEvent& event)
{
	wxGetApp().frame->AddExclusion(_proc.Name);
	ignore_btn->SetBackgroundColour(grey);
}

void ProcessWidget::Run_click(wxCommandEvent& event)
{
	run_btn->Enable(false);
	kill_btn->Enable(false);

	if (ProcessResumed)
	{
		if (Global::NtFuncs.SuspendProcess(_proc.Handle))
		{
			LogProcSuspended();
			ProcessResumed = false;
			run_btn->SetLabelMarkup(wxT("RUN"));
			run_btn->SetBackgroundColour(light_green);
			run_btn->Enable(true);
			kill_btn->Enable(true);
		}
		else
		{
			run_btn->SetBackgroundColour(grey);
			kill_btn->SetBackgroundColour(grey);
			LogErrorProcSuspended();
		}
	}
	else
	{
		if (Global::NtFuncs.ResumeProcess(_proc.Handle))
		{
			LogProcResumed();
			if (ProcPinned())
			{
				ProcessResumed = true;
				run_btn->SetLabelMarkup(wxT("SUSPEND"));
				run_btn->SetBackgroundColour(light_purple);
				run_btn->Enable(true);
				kill_btn->Enable(true);
			}
			else
			{
				DeleteSelf();
			}
		}
		else
		{
			run_btn->SetBackgroundColour(grey);
			kill_btn->SetBackgroundColour(grey);
			LogErrorProcResumed();
		}
	}
}

void ProcessWidget::Kill_click(wxCommandEvent& event)
{
	kill_btn->Enable(false);
	run_btn->Enable(false);

	if (KillProcess())
	{
		LogProcKilled();
		if (ProcPinned())
		{
			run_btn->SetBackgroundColour(grey);
			kill_btn->SetBackgroundColour(grey);
		}
		else
		{
			DeleteSelf();
		}
	}
	else
	{
		kill_btn->SetBackgroundColour(grey);
		run_btn->SetBackgroundColour(grey);
		LogErrorProcKilled();
	}
}

bool ProcessWidget::KillProcess()
{
	DWORD ec;
	if (!GetExitCodeProcess(_proc.Handle, &ec))
	{
		ec = 0;
	}

	BOOL ok = TerminateProcess(_proc.Handle, ec);
	return ok > 0;
}

bool ProcessWidget::ProcPinned()
{
	return pin_checkbox->GetValue();
}

void ProcessWidget::LogProcResumed()
{
	wxString message = wxT("Resumed: ") + GetProcDescription();
	wxGetApp().frame->LogMessage(message);
}

void ProcessWidget::LogErrorProcResumed()
{
	wxString message = wxT("Can not resume: ") + GetProcDescription();
	wxGetApp().frame->LogError(message);
}

void ProcessWidget::LogProcSuspended()
{
	wxString message = wxT("Suspended: ") + GetProcDescription();
	wxGetApp().frame->LogMessage(message);
}

void ProcessWidget::LogErrorProcSuspended()
{
	wxString message = wxT("Can not suspend: ") + GetProcDescription();
	wxGetApp().frame->LogError(message);
}

void ProcessWidget::LogProcKilled()
{
	wxString message = wxT("Killed: ") + GetProcDescription();
	wxGetApp().frame->LogMessage(message);
}

void ProcessWidget::LogErrorProcKilled()
{
	wxString message = wxT("Can not kill: ") + GetProcDescription();
	wxGetApp().frame->LogError(message);
}

wxString ProcessWidget::GetProcDescription(bool verbose)
{
	wxString proc_name = _proc.PrintableName.empty() ? wxT("---") : _proc.PrintableName;
	wxString proc_pid = _proc.IsEmpty ? wxT("---") : wxString::Format(wxT("%d"), _proc.ProcessId);
	if (!verbose)
	{
		return wxT("(") + proc_pid + wxT(") ") + proc_name;
	}

	wxString info = wxT("--------\nProcess: (") + proc_pid + wxT(") ") + proc_name;
	if (!_proc.Command.empty())
	{
		info += wxT("\nCMD    : ") + _proc.Command;
	}

	if (!_proc.Parent.IsEmpty)
	{
		wxString parent_name = _proc.Parent.PrintableName.empty() ? wxT("---") : _proc.Parent.PrintableName;
		wxString parent_pid = _proc.Parent.IsEmpty ? wxT("---") : wxString::Format(wxT("%d"), _proc.Parent.ProcessId);
		info += wxT("\nParent : (") + parent_pid + wxT(") ") + parent_name;
		if (!_proc.Parent.Command.empty())
		{
			info += wxT("\nCMD    : ") + _proc.Parent.Command;
		}
	}

	info += wxT("\n--------");
	return info;
}
