#pragma once

#include <wx/wx.h>
#include <wx/gbsizer.h>
#include "../Global.h"

class ProcessWidget : public wxBoxSizer
{
private:
    wxColour light_green = wxColour(150, 245, 140);
    wxColour light_purple = wxColour(240, 125, 240);
    wxColour grey = wxColour(150, 150, 150);
    bool ProcessResumed = false;
    ProcInfo _proc;
	wxWindow* m_parent;
    wxPanel* proc_panel;
    wxButton* btn_close;
    wxButton* copy_btn;
    wxButton* kill_btn;
    wxButton* ignore_btn;
    wxButton* run_btn;
    wxCheckBox* pin_checkbox;
    wxTextCtrl* proc_text;
    wxTextCtrl* args_text;
    wxTextCtrl* parent_text;
    bool ProcPinned();

protected:
    void DeleteEntry_click(wxCommandEvent& event);
    void CopyInfo_click(wxCommandEvent& event);
    void Ignore_click(wxCommandEvent& event);
    void Run_click(wxCommandEvent& event);
    void Kill_click(wxCommandEvent& event);
    void LogProcResumed();
    void LogErrorProcResumed();
    void LogProcSuspended();
    void LogErrorProcSuspended();
    void LogProcKilled();
    void LogErrorProcKilled();
    bool KillProcess();

public:
    ProcessWidget(wxWindow* parent, ProcInfo proc);
    ~ProcessWidget();
    void DeleteSelf(bool resume = false);
    void HideSelf();
    void ShowSelf();
    void ShrinkSelf();
    void SetInitSize();
    wxString GetProcDescription(bool verbose = false);
};
