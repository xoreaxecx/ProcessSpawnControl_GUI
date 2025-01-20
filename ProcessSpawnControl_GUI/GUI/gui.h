///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/scrolwin.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/filepicker.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/listbox.h>
#include "processWidget.h"
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel5;
		wxSplitterWindow* m_splitter;
		wxScrolledWindow* m_procWindow;
		wxPanel* m_logPanel;
		wxButton* m_clearLog_btn;
		wxCheckBox* m_autoscroll_chb;
		wxStaticText* m_procCount_text;
		wxRichTextCtrl* m_log;
		wxPanel* m_controlPanel;
		wxButton* m_start_btn;
		wxButton* m_stop_btn;
		wxButton* m_clearArgs_btn;
		wxFilePickerCtrl* m_target_filePicker;
		wxTextCtrl* m_targetArgs_text;
		wxFilePickerCtrl* m_parent_filePicker;
		wxTextCtrl* m_parentArgs_text;
		wxTextCtrl* m_parentPID_text;
		wxCheckBox* m_asExplorer_chb;
		wxCheckBox* m_controlAll_chb;
		wxCheckBox* m_stayOnTop_chb;
		wxFilePickerCtrl* m_exclusions_filePicker;
		wxButton* m_loadExc_btn;
		wxButton* m_addExc_btn;
		wxButton* m_delExc_btn;
		wxTextCtrl* m_exclusion_text;
		wxListBox* m_exclusions_listBox;

		// Virtual event handlers, override them in your derived class
		virtual void Cleanup( wxCloseEvent& event ) { event.Skip(); }
		virtual void ClearLog_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void Start_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void Stop_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void Clear_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetTargetDropPath( wxDropFilesEvent& event ) { event.Skip(); }
		virtual void SetParentDropPath( wxDropFilesEvent& event ) { event.Skip(); }
		virtual void AlwaysOnTop_Check( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetExclusionsDropPath( wxDropFilesEvent& event ) { event.Skip(); }
		virtual void LoadExclusions_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddExclusion_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteExclusion_click( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddExclusion_enter( wxCommandEvent& event ) { event.Skip(); }
		virtual void Exclusions_doubleClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxString parentPID_valVar;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,600 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER );

		~MainFrame();

		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 400 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitterOnIdle ), NULL, this );
		}

};

