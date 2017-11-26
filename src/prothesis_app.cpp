#include "prothesis_app.hpp"
#include "main_frame.hpp"

IMPLEMENT_APP(ProthesisApp)

// Entry point for our program
bool ProthesisApp::OnInit() {
  // Create an instance of our frame, or window
  MainFrame *main_frame = new MainFrame(_("Prothesis v2"),
                                        wxDefaultPosition,
                                        wxSize(300, 200));

  SetTopWindow(main_frame);
  main_frame->Show();
  return true;
}

ProthesisApp::~ProthesisApp() {
  // TODO(egeldenhuys)
}
