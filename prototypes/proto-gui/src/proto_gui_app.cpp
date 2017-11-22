#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "proto_gui_app.hpp"
#include "welcome_frame.hpp"

IMPLEMENT_APP(ProtoGuiApp)

// Entry point
bool ProtoGuiApp::OnInit() 
{
	// Create an instance of our frame, or window 
        WelcomeFrame *MainWin = new WelcomeFrame(_("Hello World!"), wxDefaultPosition, wxSize(300, 200));
	MainWin->Show(true); // show the window 
	SetTopWindow(MainWin); // and finally, set it as the main window 
	return true;
} 
