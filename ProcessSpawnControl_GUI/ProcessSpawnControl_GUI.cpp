#include "ProcessSpawnControl_GUI.h"
#include "gui/guiMainFrame.h"

GuiApp::GuiApp()
{

}

GuiApp::~GuiApp()
{

}

bool GuiApp::OnInit()
{
    frame = new guiMainFrame((wxWindow*)NULL);
    frame->Show();
    SetTopWindow(frame);
    return true;
}
IMPLEMENT_APP(GuiApp)