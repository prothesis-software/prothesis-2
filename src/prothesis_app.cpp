#include "prothesis_app.hpp"
#include "main_frame.hpp"

IMPLEMENT_APP(ProthesisApp)

void ProthesisApp::OnKillRequest(int sig_num) {
  wxLogDebug("OnKillRequest()");
  wxExit();
}

// Entry point for our program
bool ProthesisApp::OnInit() {
  MainFrame *main_frame = new MainFrame(NULL, wxID_ANY,
                                        _("Prothesis v2.0.4"),
                                        wxDefaultPosition,
                                        wxSize(-1, -1));

  std::signal(SIGINT, OnKillRequest);
  data_manager_ = new DataManager(main_frame);
  data_manager_->DisplayPanel(DataManager::PanelId::kDetailsPanel);

  SetTopWindow(main_frame);
  main_frame->Show();
  return true;
}

int ProthesisApp::OnExit() {
  wxLogDebug("Preparing to exit...");
  data_manager_->SaveUserConfig();
  return 0;
}

ProthesisApp::~ProthesisApp() {
  delete data_manager_;
}
