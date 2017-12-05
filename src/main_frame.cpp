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
  wxLogDebug("MainFrame::MainFrame() START");
  std::signal(SIGINT, OnKill);

  const int64_t header_style = 0;

  data_manager_ = new DataManager(this);
  sizer_content_ = new wxFlexGridSizer(1, 3, 0, 0);
  panel_drawer_button_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, header_style);
  button_drawer_ = new wxButton(panel_drawer_button_, wxID_ANY, wxT("Drawer"));

  panel_title_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                             wxDefaultSize, header_style);

  // Need to give Ellipsize flags: http://trac.wxwidgets.org/ticket/10716
  label_title_ = new wxStaticText(panel_title_, wxID_ANY, wxT("Title"),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxALIGN_CENTER | wxST_ELLIPSIZE_END);

  panel_config_button_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, header_style);
  button_config_ = new wxButton(panel_config_button_, wxID_ANY, wxT("Config"));

  sizer_main_frame_master_ = new wxFlexGridSizer(4, 1, 0, 0);

  SetProperties();
  DoLayout();

  wxLogDebug("MainFrame::MainFrame() Getting detail panel");
  DisplayPanel(data_manager_->
               GetPanelById(DataManager::PanelId::kDetailsPanel));
  //  sizer_main_frame_master_->Fit(this);
  wxLogDebug("MainFrame::MainFrame() END");
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
  default:
    return false;
  }

  return true;
}

// TODO(egeldenhuys): Switch to wxSimplebook
// WARN(egeldenhuys): Causes valgrind errors
void MainFrame::DisplayPanel(DataPanel *panel) {
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
  panel->Layout();
  Layout();
  Fit();
  wxLogDebug("MainFrame::DisplayPanel() END");
}

void MainFrame::SetProperties() {
  label_title_->SetFont(wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, 0, wxT("")));
}

void MainFrame::DoLayout() {
  // sizer_header
  wxFlexGridSizer *sizer_header = new wxFlexGridSizer(1, 3, 0, 0);

  // drawer button
  wxBoxSizer *sizer_drawer_button = new wxBoxSizer(wxVERTICAL);
  sizer_drawer_button->Add(button_drawer_, 0, 0, 0);
  panel_drawer_button_->SetSizer(sizer_drawer_button);
  sizer_header->Add(panel_drawer_button_, 1, wxEXPAND, 0);

  // title
  wxBoxSizer *sizer_title_h = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_title_v = new wxBoxSizer(wxVERTICAL);
  sizer_title_v->Add(label_title_, 0, wxEXPAND, 0);
  sizer_title_h->Add(sizer_title_v, 1, wxALIGN_BOTTOM, 0);
  panel_title_->SetSizer(sizer_title_h);
  sizer_header->Add(panel_title_, 1, wxEXPAND, 0);

  // config button
  wxBoxSizer *sizer_config_button = new wxBoxSizer(wxVERTICAL);
  sizer_config_button->Add(button_config_, 0, wxALIGN_RIGHT, 0);
  panel_config_button_->SetSizer(sizer_config_button);
  sizer_header->Add(panel_config_button_, 1, wxEXPAND, 0);
  sizer_header->AddGrowableRow(0);
  sizer_header->AddGrowableCol(0);
  sizer_header->AddGrowableCol(1);
  sizer_header->AddGrowableCol(2);
  sizer_main_frame_master_->Add(sizer_header, 1, wxEXPAND, 0);

  // bar
  wxFlexGridSizer *sizer_bar = new wxFlexGridSizer(1, 1, 0, 0);
  wxStaticLine *line = new wxStaticLine(this, wxID_ANY);
  line->SetMinSize(wxSize(10, 4));  // Required to work
  sizer_bar->Add(line, 0, wxEXPAND, 0);
  sizer_bar->AddGrowableRow(0);
  sizer_bar->AddGrowableCol(0);
  sizer_main_frame_master_->Add(sizer_bar, 1, wxEXPAND, 0);

  // sizer_content_
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->AddGrowableCol(0);
  sizer_content_->AddGrowableCol(2);
  sizer_main_frame_master_->Add(sizer_content_, 1, wxEXPAND);

  // sizer_footer
  wxFlexGridSizer *sizer_footer = new wxFlexGridSizer(1, 3, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->AddGrowableRow(0);
  sizer_footer->AddGrowableCol(0);
  sizer_footer->AddGrowableCol(1);
  sizer_footer->AddGrowableCol(2);
  sizer_main_frame_master_->Add(sizer_footer, 1, wxEXPAND, 0);

  SetSizer(sizer_main_frame_master_);
  sizer_main_frame_master_->AddGrowableRow(2);
  sizer_main_frame_master_->AddGrowableCol(0);

  sizer_main_frame_master_->Fit(this);
  Layout();
}

MainFrame::~MainFrame() {
  // wxLogDebug("MainFrame::~MainFrame() START");
  data_manager_->SaveUserConfig();
  delete data_manager_;
  // wxLogDebug("MainFrame::~MainFrame() END");
}
