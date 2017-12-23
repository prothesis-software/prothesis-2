#include "main_frame.hpp"
#include <csignal>
#include <string>

void MainFrame::OnKill(int sig) {
  wxLogDebug("MainFrame::OnKill");
  wxExit();
}

MainFrame::MainFrame(wxWindow *parent,
                     wxWindowID id,
                     const wxString &title,
                     const wxPoint &pos,
                     const wxSize &size,
                     int64_t style,
                     const wxString name)
  : wxFrame(parent, id, title, pos, size, style, name) {
  std::signal(SIGINT, OnKill);
  data_manager_ = new DataManager(this);
  sizer_content_ = new wxFlexGridSizer(2, 3, 0, 0);
  sizer_main_frame_ = new wxFlexGridSizer(3, 1, 0, 0);

  // Need to give Ellipsize flags: http://trac.wxwidgets.org/ticket/10716
  label_title_ = new wxStaticText(this, wxID_ANY, wxT("Title"),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxALIGN_CENTER | wxST_ELLIPSIZE_END);
  SetProperties();
  DoLayout();
  DisplayPanel(data_manager_->
               GetPanelById(DataManager::PanelId::kDetailsPanel));
}



void MainFrame::SetHeaderTitle(std::string title) {
  label_title_->SetLabel(_(title));
}

void MainFrame::OnClose(wxCloseEvent &e) {
  wxLogDebug(_("MainFrame::OnClose()"));
  data_manager_->SaveUserConfig();
}

void MainFrame::DisplayPanelById(DataManager::PanelId id) {
  DisplayPanel(data_manager_->GetPanelById(id));
  active_panel_id_ = id;
}

// TODO(egeldenhuys): This is a bad implementation. Should be
// part of DataManager
bool MainFrame::DisplayNextPanel() {
  switch (active_panel_id_) {
  case DataManager::PanelId::kPassionPanel:
    DisplayPanelById(DataManager::PanelId::kPeopleIdPanel);
    break;
  case DataManager::PanelId::kPeopleIdPanel:
    DisplayPanelById(DataManager::PanelId::kDreamsPanel);
    break;
  case DataManager::PanelId::kDreamsPanel:
    DisplayPanelById(DataManager::PanelId::kValuesPanel);
    break;
  case DataManager::PanelId::kValuesPanel:
    DisplayPanelById(DataManager::PanelId::kSpokenWordsPanel);
    break;
  default:
    return false;
  }

  return true;
}

// TODO(egeldenhuys): Switch to wxSimplebook
// WARN(egeldenhuys): Causes valgrind errors
void MainFrame::DisplayPanel(DataPanel *panel) {
  // Freeze and thaw are required to prevent visual artifacts
  Freeze();
  wxLogDebug("MainFrame::DisplayPanel() START");
  const size_t kPanelViewIndex = 1;
  const size_t kBorderSize = 0;

  sizer_content_->Detach(kPanelViewIndex);
  sizer_content_->Insert(kPanelViewIndex,
                         panel, 1, wxEXPAND | wxALL, kBorderSize);
  if (active_panel_ != NULL)
      active_panel_->Hide();
  active_panel_ = panel;

  SetHeaderTitle(active_panel_->GetPanelTitle());
  panel->Show();
  Fit();
  wxLogDebug("MainFrame::DisplayPanel() END");
  Thaw();
}

void MainFrame::SetProperties() {
  label_title_->SetFont(wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, 0, wxT("")));
}

void MainFrame::DoLayout() {
  // title
  // wxBoxSizer *sizer_title_h = new wxBoxSizer(wxHORIZONTAL);
  // wxBoxSizer *sizer_title_v = new wxBoxSizer(wxVERTICAL);
  // sizer_title_v->Add(label_title_, 0, wxEXPAND, 0);
  // sizer_title_h->Add(sizer_title_v, 1, wxALIGN_BOTTOM, 0);
  // panel_title_->SetSizer(sizer_title_h);
  // sizer_header->Add(panel_title_, 1, wxEXPAND, 0);
  sizer_main_frame_->Add(label_title_, 1, wxALIGN_CENTER | wxEXPAND, 0);

  // bar
  // wxFlexGridSizer *sizer_bar = new wxFlexGridSizer(1, 1, 0, 0);
  wxStaticLine *line = new wxStaticLine(this, wxID_ANY);
  line->SetMinSize(wxSize(10, 4));  // Required to work
  // sizer_bar->Add(line, 0, wxEXPAND, 0);
  // sizer_bar->AddGrowableRow(0);
  // sizer_bar->AddGrowableCol(0);
  // sizer_main_frame_master_->Add(sizer_bar, 1, wxEXPAND, 0);
  sizer_main_frame_->Add(line, 1, wxEXPAND, 0);

  // sizer_content_
  sizer_content_->Add(0, 0, 0, 0, 0);  // TODO(egeldenhuys): navbar
  sizer_content_->Add(0, 0, 0, 0, 0);  // Index 1 content placeholder
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);  // TODO(egeldenhuys): button_next
  sizer_content_->AddGrowableCol(2);
  sizer_content_->AddGrowableRow(1);
  sizer_main_frame_->Add(sizer_content_, 1, wxEXPAND, 0);

  sizer_main_frame_->AddGrowableCol(0);
  SetSizer(sizer_main_frame_);
  sizer_main_frame_->Fit(this);
  Fit();
  Layout();
}

MainFrame::~MainFrame() {
  // wxLogDebug("MainFrame::~MainFrame() START");
  data_manager_->SaveUserConfig();
  delete data_manager_;
  // wxLogDebug("MainFrame::~MainFrame() END");
}
