#pragma once

#include "resource.h"
#include "GUI/guiMainFrame.h"

#ifndef GuiApp_H
#define GuiApp_H

#include <wx/wx.h>

class GuiApp : public wxApp {
public:
	GuiApp();
	virtual ~GuiApp();
	virtual bool OnInit();
	guiMainFrame* frame;
};

DECLARE_APP(GuiApp)

#endif