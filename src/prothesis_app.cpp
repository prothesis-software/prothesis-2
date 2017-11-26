#include "prothesis_app.hpp"
#include "main_frame.hpp"

IMPLEMENT_APP(ProthesisApp)

// Entry point for our program
bool ProthesisApp::OnInit() {
  MainFrame *main_frame = new MainFrame(NULL, wxID_ANY,
                                        _("Prothesis v2"),
                                        wxDefaultPosition,
                                        wxSize(-1, -1));
  data_manager_ = new DataManager(main_frame);
  data_manager_->DisplayPanel(DataManager::PanelId::kDetailsPanel);

  SetTopWindow(main_frame);
  main_frame->Show();
  return true;
}

ProthesisApp::~ProthesisApp() {
  delete data_manager_;
}
