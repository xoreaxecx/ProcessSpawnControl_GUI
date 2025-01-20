///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	this->SetBackgroundColour( wxColour( 40, 40, 40 ) );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_panel5 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_splitter = new wxSplitterWindow( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER|wxSP_LIVE_UPDATE );
	m_splitter->SetSashGravity( 1 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( MainFrame::m_splitterOnIdle ), NULL, this );
	m_splitter->SetMinimumPaneSize( 50 );

	m_procWindow = new wxScrolledWindow( m_splitter, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxBORDER_SIMPLE|wxCLIP_CHILDREN );
	m_procWindow->SetScrollRate( 5, 5 );
	m_procWindow->SetBackgroundColour( wxColour( 40, 40, 40 ) );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );


	m_procWindow->SetSizer( bSizer3 );
	m_procWindow->Layout();
	bSizer3->Fit( m_procWindow );
	m_logPanel = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxBORDER_SIMPLE );
	m_logPanel->SetBackgroundColour( wxColour( 60, 60, 60 ) );

	wxGridBagSizer* gbSizer9;
	gbSizer9 = new wxGridBagSizer( 0, 0 );
	gbSizer9->SetFlexibleDirection( wxBOTH );
	gbSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_clearLog_btn = new wxButton( m_logPanel, wxID_ANY, wxT("Clear log"), wxDefaultPosition, wxDefaultSize, 0 );
	m_clearLog_btn->SetLabelMarkup( wxT("Clear log") );
	m_clearLog_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_clearLog_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_clearLog_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_clearLog_btn->SetMinSize( wxSize( -1,20 ) );

	gbSizer9->Add( m_clearLog_btn, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxLEFT|wxRIGHT, 5 );

	m_autoscroll_chb = new wxCheckBox( m_logPanel, wxID_ANY, wxT("Autoscroll"), wxDefaultPosition, wxDefaultSize, 0 );
	m_autoscroll_chb->SetValue(true);
	m_autoscroll_chb->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_autoscroll_chb->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_autoscroll_chb->SetMinSize( wxSize( -1,20 ) );

	gbSizer9->Add( m_autoscroll_chb, wxGBPosition( 0, 2 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxLEFT|wxRIGHT, 5 );

	m_procCount_text = new wxStaticText( m_logPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL|wxBORDER_SIMPLE );
	m_procCount_text->Wrap( -1 );
	m_procCount_text->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_procCount_text->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_procCount_text->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_procCount_text->SetMinSize( wxSize( 30,20 ) );

	gbSizer9->Add( m_procCount_text, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxRIGHT, 2 );

	m_log = new wxRichTextCtrl( m_logPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_READONLY );
	m_log->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_log->SetForegroundColour( wxColour( 221, 221, 221 ) );
	m_log->SetBackgroundColour( wxColour( 190, 190, 190 ) );

	gbSizer9->Add( m_log, wxGBPosition( 1, 0 ), wxGBSpan( 1, 3 ), wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );


	gbSizer9->AddGrowableCol( 1 );
	gbSizer9->AddGrowableRow( 1 );

	m_logPanel->SetSizer( gbSizer9 );
	m_logPanel->Layout();
	gbSizer9->Fit( m_logPanel );
	m_splitter->SplitHorizontally( m_procWindow, m_logPanel, 400 );
	bSizer4->Add( m_splitter, 1, wxEXPAND, 2 );


	m_panel5->SetSizer( bSizer4 );
	m_panel5->Layout();
	bSizer4->Fit( m_panel5 );
	gbSizer1->Add( m_panel5, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 0 );

	m_controlPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE );
	m_controlPanel->SetBackgroundColour( wxColour( 40, 40, 40 ) );

	wxGridBagSizer* gbSizer5;
	gbSizer5 = new wxGridBagSizer( 0, 0 );
	gbSizer5->SetFlexibleDirection( wxBOTH );
	gbSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_start_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Start"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_start_btn->SetLabelMarkup( wxT("Start") );
	m_start_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_start_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_start_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_start_btn->SetMinSize( wxSize( -1,50 ) );

	bSizer2->Add( m_start_btn, 0, wxALL|wxEXPAND, 5 );

	m_stop_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stop_btn->SetLabelMarkup( wxT("Stop") );
	m_stop_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_stop_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_stop_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_stop_btn->Enable( false );
	m_stop_btn->SetMinSize( wxSize( -1,50 ) );

	bSizer2->Add( m_stop_btn, 0, wxALL|wxEXPAND, 5 );

	m_clearArgs_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	m_clearArgs_btn->SetLabelMarkup( wxT("Clear") );
	m_clearArgs_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_clearArgs_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_clearArgs_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_clearArgs_btn->SetToolTip( wxT("Clear paths and args") );
	m_clearArgs_btn->SetMinSize( wxSize( -1,25 ) );

	bSizer2->Add( m_clearArgs_btn, 0, wxALL|wxEXPAND, 5 );

	m_target_filePicker = new wxFilePickerCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_SMALL|wxBORDER_NONE );
	m_target_filePicker->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_target_filePicker->SetToolTip( wxT("Target path") );
	m_target_filePicker->DragAcceptFiles( true );

	bSizer2->Add( m_target_filePicker, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	m_targetArgs_text = new wxTextCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_targetArgs_text->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_targetArgs_text->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_targetArgs_text->SetBackgroundColour( wxColour( 190, 190, 190 ) );

	bSizer2->Add( m_targetArgs_text, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_parent_filePicker = new wxFilePickerCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_SMALL|wxBORDER_NONE );
	m_parent_filePicker->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_parent_filePicker->SetToolTip( wxT("Parent path") );
	m_parent_filePicker->DragAcceptFiles( true );

	bSizer2->Add( m_parent_filePicker, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );

	m_parentArgs_text = new wxTextCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_parentArgs_text->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_parentArgs_text->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_parentArgs_text->SetBackgroundColour( wxColour( 190, 190, 190 ) );

	bSizer2->Add( m_parentArgs_text, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_parentPID_text = new wxTextCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_parentPID_text->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_parentPID_text->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_parentPID_text->SetBackgroundColour( wxColour( 190, 190, 190 ) );

	m_parentPID_text->SetValidator( wxTextValidator( wxFILTER_NUMERIC, &parentPID_valVar ) );

	bSizer2->Add( m_parentPID_text, 0, wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_asExplorer_chb = new wxCheckBox( m_controlPanel, wxID_ANY, wxT("as Explorer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_asExplorer_chb->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_asExplorer_chb->SetForegroundColour( wxColour( 210, 210, 210 ) );
	m_asExplorer_chb->SetToolTip( wxT("Run target with Explorer permissions") );

	bSizer2->Add( m_asExplorer_chb, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_controlAll_chb = new wxCheckBox( m_controlPanel, wxID_ANY, wxT("control all"), wxDefaultPosition, wxDefaultSize, 0 );
	m_controlAll_chb->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_controlAll_chb->SetForegroundColour( wxColour( 210, 210, 210 ) );
	m_controlAll_chb->SetToolTip( wxT("Suspend all spawned processes") );

	bSizer2->Add( m_controlAll_chb, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_stayOnTop_chb = new wxCheckBox( m_controlPanel, wxID_ANY, wxT("stay on top"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stayOnTop_chb->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_stayOnTop_chb->SetForegroundColour( wxColour( 210, 210, 210 ) );

	bSizer2->Add( m_stayOnTop_chb, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gbSizer5->Add( bSizer2, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	wxGridBagSizer* gbSizer3;
	gbSizer3 = new wxGridBagSizer( 0, 0 );
	gbSizer3->SetFlexibleDirection( wxBOTH );
	gbSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_exclusions_filePicker = new wxFilePickerCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_SMALL|wxFLP_USE_TEXTCTRL );
	m_exclusions_filePicker->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_exclusions_filePicker->SetToolTip( wxT("Exclusions path") );
	m_exclusions_filePicker->DragAcceptFiles( true );

	gbSizer3->Add( m_exclusions_filePicker, wxGBPosition( 0, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_loadExc_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Load"), wxDefaultPosition, wxDefaultSize, 0 );
	m_loadExc_btn->SetLabelMarkup( wxT("Load") );
	m_loadExc_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_loadExc_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_loadExc_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );

	gbSizer3->Add( m_loadExc_btn, wxGBPosition( 1, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_addExc_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	m_addExc_btn->SetLabelMarkup( wxT("Add") );
	m_addExc_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_addExc_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_addExc_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_addExc_btn->SetToolTip( wxT("Add exclusion") );
	m_addExc_btn->SetMinSize( wxSize( 60,-1 ) );

	gbSizer3->Add( m_addExc_btn, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP, 5 );

	m_delExc_btn = new wxButton( m_controlPanel, wxID_ANY, wxT("Del"), wxDefaultPosition, wxDefaultSize, 0 );
	m_delExc_btn->SetLabelMarkup( wxT("Del") );
	m_delExc_btn->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_delExc_btn->SetForegroundColour( wxColour( 220, 220, 220 ) );
	m_delExc_btn->SetBackgroundColour( wxColour( 100, 100, 100 ) );
	m_delExc_btn->SetToolTip( wxT("Delete exclusion") );
	m_delExc_btn->SetMinSize( wxSize( 60,-1 ) );

	gbSizer3->Add( m_delExc_btn, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxLEFT|wxRIGHT|wxTOP, 5 );

	m_exclusion_text = new wxTextCtrl( m_controlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	m_exclusion_text->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_exclusion_text->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_exclusion_text->SetBackgroundColour( wxColour( 190, 190, 190 ) );
	m_exclusion_text->SetToolTip( wxT("Process name") );

	gbSizer3->Add( m_exclusion_text, wxGBPosition( 3, 0 ), wxGBSpan( 1, 2 ), wxEXPAND|wxLEFT|wxRIGHT, 5 );

	m_exclusions_listBox = new wxListBox( m_controlPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_HSCROLL|wxLB_SINGLE );
	m_exclusions_listBox->Append( wxT("explorer.exe") );
	m_exclusions_listBox->Append( wxT("msmpeng.exe") );
	m_exclusions_listBox->Append( wxT("taskmgr.exe") );
	m_exclusions_listBox->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );
	m_exclusions_listBox->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_exclusions_listBox->SetBackgroundColour( wxColour( 190, 190, 190 ) );
	m_exclusions_listBox->SetMaxSize( wxSize( 150,-1 ) );

	gbSizer3->Add( m_exclusions_listBox, wxGBPosition( 4, 0 ), wxGBSpan( 1, 2 ), wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 5 );


	gbSizer3->AddGrowableRow( 4 );

	gbSizer5->Add( gbSizer3, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );


	gbSizer5->AddGrowableRow( 1 );

	m_controlPanel->SetSizer( gbSizer5 );
	m_controlPanel->Layout();
	gbSizer5->Fit( m_controlPanel );
	gbSizer1->Add( m_controlPanel, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxEXPAND, 0 );


	gbSizer1->AddGrowableCol( 0 );
	gbSizer1->AddGrowableRow( 0 );

	this->SetSizer( gbSizer1 );
	this->Layout();


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::Cleanup ) );
	m_clearLog_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::ClearLog_click ), NULL, this );
	m_start_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Start_click ), NULL, this );
	m_stop_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Stop_click ), NULL, this );
	m_clearArgs_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Clear_click ), NULL, this );
	m_target_filePicker->Connect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetTargetDropPath ), NULL, this );
	m_parent_filePicker->Connect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetParentDropPath ), NULL, this );
	m_stayOnTop_chb->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::AlwaysOnTop_Check ), NULL, this );
	m_exclusions_filePicker->Connect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetExclusionsDropPath ), NULL, this );
	m_loadExc_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::LoadExclusions_click ), NULL, this );
	m_addExc_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddExclusion_click ), NULL, this );
	m_delExc_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteExclusion_click ), NULL, this );
	m_exclusion_text->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::AddExclusion_enter ), NULL, this );
	m_exclusions_listBox->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( MainFrame::Exclusions_doubleClick ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::Cleanup ) );
	m_clearLog_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::ClearLog_click ), NULL, this );
	m_start_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Start_click ), NULL, this );
	m_stop_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Stop_click ), NULL, this );
	m_clearArgs_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::Clear_click ), NULL, this );
	m_target_filePicker->Disconnect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetTargetDropPath ), NULL, this );
	m_parent_filePicker->Disconnect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetParentDropPath ), NULL, this );
	m_stayOnTop_chb->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::AlwaysOnTop_Check ), NULL, this );
	m_exclusions_filePicker->Disconnect( wxEVT_DROP_FILES, wxDropFilesEventHandler( MainFrame::SetExclusionsDropPath ), NULL, this );
	m_loadExc_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::LoadExclusions_click ), NULL, this );
	m_addExc_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::AddExclusion_click ), NULL, this );
	m_delExc_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::DeleteExclusion_click ), NULL, this );
	m_exclusion_text->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrame::AddExclusion_enter ), NULL, this );
	m_exclusions_listBox->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( MainFrame::Exclusions_doubleClick ), NULL, this );

}
