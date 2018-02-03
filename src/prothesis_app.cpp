#include "prothesis_app.hpp"

#include <string>

#include "main_frame.hpp"

IMPLEMENT_APP(ProthesisApp)

// Entry point for our program
bool ProthesisApp::OnInit() {
#ifdef PROTHESIS_VERSION
  wxString title = "Prothesis " + std::string(PROTHESIS_VERSION);
#else
  wxString title = "Prothesis";
#endif

std::cout << "HELLO" << std::endl;

  MainFrame* main_frame =
      new MainFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(-1, -1));
  SetTopWindow(main_frame);
  main_frame->Show();
  return true;
}

ProthesisApp::~ProthesisApp() {
  // wxLogDebug("ProthesisApp::~ProthesisApp()");
}
