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

  const int64_t header_style = 0;

  data_manager_ = new DataManager(this);
  sizer_content_ = new wxFlexGridSizer(1, 3, 0, 0);
  panel_drawer_button_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, header_style);
  button_drawer_ = new wxButton(panel_drawer_button_, wxID_ANY, wxT("Drawer"));

  panel_title_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                             wxDefaultSize, header_style);
  label_title_ = new wxStaticText(panel_title_, wxID_ANY, wxT("Title"),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxALIGN_CENTER);

  panel_config_button_ = new wxPanel(this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, header_style);
  button_config_ = new wxButton(panel_config_button_, wxID_ANY, wxT("Config"));

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

void MainFrame::DisplayPanel(DataPanel *panel) {
  const size_t kPanelViewIndex = 1;

  if (active_panel_ != NULL)
    active_panel_->Hide();

  // TODO(egeldenhuys): Detach vs Remove
  sizer_content_->Detach(kPanelViewIndex);
  sizer_content_->Insert(kPanelViewIndex, panel, 1, wxEXPAND, 0);
  panel->Show();
  active_panel_ = panel;
  SetHeaderTitle(active_panel_->GetPanelTitle());
  Layout();
  Fit();
}

void MainFrame::SetProperties() {
  label_title_->SetFont(wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, 0, wxT("")));
}

void MainFrame::DoLayout() {
  wxFlexGridSizer* sizer_main_frame_master = new wxFlexGridSizer(4, 1, 0, 0);

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
  sizer_main_frame_master->Add(sizer_header, 1, wxEXPAND, 0);

  // bar
  wxFlexGridSizer *sizer_bar = new wxFlexGridSizer(1, 1, 0, 0);
  wxStaticLine *line = new wxStaticLine(this, wxID_ANY);
  line->SetMinSize(wxSize(10, 4));  // Required to work
  sizer_bar->Add(line, 0, wxEXPAND, 0);
  sizer_bar->AddGrowableRow(0);
  sizer_bar->AddGrowableCol(0);
  sizer_main_frame_master->Add(sizer_bar, 1, wxEXPAND, 0);

  // sizer_content_
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->Add(0, 0, 0, 0, 0);
  sizer_content_->AddGrowableCol(0);
  sizer_content_->AddGrowableCol(2);
  sizer_main_frame_master->Add(sizer_content_, 1, wxEXPAND);

  // sizer_footer
  wxFlexGridSizer *sizer_footer = new wxFlexGridSizer(1, 3, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->Add(0, 0, 0, 0, 0);
  sizer_footer->AddGrowableRow(0);
  sizer_footer->AddGrowableCol(0);
  sizer_footer->AddGrowableCol(1);
  sizer_footer->AddGrowableCol(2);
  sizer_main_frame_master->Add(sizer_footer, 1, wxEXPAND, 0);

  SetSizer(sizer_main_frame_master);
  sizer_main_frame_master->AddGrowableRow(2);
  sizer_main_frame_master->AddGrowableCol(0);

  Layout();
}

MainFrame::~MainFrame() {
  // wxLogDebug("MainFrame::~MainFrame() START");
  data_manager_->SaveUserConfig();
  delete data_manager_;
  // wxLogDebug("MainFrame::~MainFrame() END");
}