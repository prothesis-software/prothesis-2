#include "prothesis_app.hpp"
#include "main_frame.hpp"

IMPLEMENT_APP(ProthesisApp)

// Entry point for our program
bool ProthesisApp::OnInit() {
  MainFrame *main_frame = new MainFrame(NULL, wxID_ANY,
                                        _("Prothesis v2.0.0"),
                                        wxDefaultPosition,
                                        wxSize(-1, -1));
  SetTopWindow(main_frame);
  main_frame->Show();
  return true;
}

ProthesisApp::~ProthesisApp() {
  // wxLogDebug("ProthesisApp::~ProthesisApp()");
}
