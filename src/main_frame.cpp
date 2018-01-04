#include "main_frame.hpp"
#include <csignal>
#include <string>

#include "navigation_drawer.hpp"

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
  panel_main_ = new wxPanel(this, wxID_ANY);

  sizer_content_ = new wxFlexGridSizer(2, 2, 0, 0);
  sizer_main_frame_ = new wxFlexGridSizer(3, 1, 0, 0);
  notebook_ = new wxNotebook(panel_main_, wxID_ANY, wxDefaultPosition,
                                        wxDefaultSize, wxNB_TOP);
  notebook_->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED,
                  &MainFrame::OnNotebookSelectionChange,
                  this);
  data_manager_ = new DataManager(notebook_);
  // Need to give Ellipsize flags: http://trac.wxwidgets.org/ticket/10716
  label_title_ = new wxStaticText(panel_main_, wxID_ANY, wxT("Title"),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxALIGN_CENTER | wxST_ELLIPSIZE_END);
  SetProperties();
  DoLayout();
  DisplayPanelById(DataManager::PanelId::kDetailsPanel);
  Fit();

  wxSize minSize = GetOverallMinSize();
  SetMinSize(minSize);
  SetSize(minSize);
}

void MainFrame::SetHeaderTitle(std::string title) {
  label_title_->SetLabel(_(title));
}

void MainFrame::OnClose(wxCloseEvent &e) {
  wxLogDebug(_("MainFrame::OnClose()"));
  data_manager_->SaveUserConfig();
}

void MainFrame::OnNotebookSelectionChange(wxBookCtrlEvent& event) {
  // Only do stuff if there are still objects to work with
  if (!exit_requested_) {
    int index = notebook_->GetSelection();
    DataManager::PanelId id = data_manager_->GetIdFromIndex(index);

    DataPanel *panel = data_manager_->GetPanelById(id);
    active_panel_ = panel;
    active_panel_id_ = id;
    SetHeaderTitle(active_panel_->GetPanelTitle());
  }
}

void MainFrame::DisplayPanelById(DataManager::PanelId id) {
  if (active_panel_id_ != id) {
    notebook_->ChangeSelection(id);
    active_panel_id_ = id;
    active_panel_ = data_manager_->GetPanelById(id);
    SetHeaderTitle(active_panel_->GetPanelTitle());
    Refresh();
  }
}

bool MainFrame::DisplayNextPanel() {
  if (active_panel_id_ + 1 < DataManager::PanelId::kPanelCount) {
    DisplayPanelById(data_manager_->GetIdFromIndex(active_panel_id_ + 1));
    return true;
  } else {
    return false;
  }
}

// TODO(egeldenhuys): Switch to wxSimplebook
// WARN(egeldenhuys): Causes valgrind errors
// Do not use directly. Use DisplayPanelById()
void MainFrame::DisplayPanel_deprecated(DataPanel *panel) {
  // Freeze and thaw are required to prevent visual artifacts
  Freeze();

  const size_t kPanelViewIndex = 1;
  const size_t kBorderSize = 0;

  sizer_content_->Detach(kPanelViewIndex);
  sizer_content_->Insert(kPanelViewIndex,
                         panel, 1, wxEXPAND | wxALL, kBorderSize);
  if (active_panel_ != NULL)
      active_panel_->Hide();
  active_panel_ = panel;
  wxLogDebug(_("Displaying panel ") + _(panel->GetPanelName()));
  SetHeaderTitle(active_panel_->GetPanelTitle());
  panel->Show();
  Layout();

  Thaw();
}


wxSize MainFrame::GetOverallMinSize() {
  Freeze();
  wxLogDebug(_("Getting best size..."));
  wxSize minSize = GetSize();
  DataManager::PanelId orig = active_panel_id_;

  wxLogDebug(_(std::to_string(minSize.x)) +
             _(", ") +
             _(std::to_string(minSize.y)));

  while (DisplayNextPanel() != false) {
    Fit();
    wxSize tmpSize = GetSize();
    wxLogDebug(_(std::to_string(tmpSize.x)) +
               _(", ") +
               _(std::to_string(tmpSize.y)));

    if (tmpSize.x > minSize.x) {
      minSize.x = tmpSize.x;
    }

    if (tmpSize.y > minSize.y) {
      minSize.y = tmpSize.y;
    }
  }

  wxLogDebug(_("Best size = ") +
             _(std::to_string(minSize.x)) +
             _(", ") +
             _(std::to_string(minSize.y)));

  DisplayPanelById(orig);
  Thaw();
  return minSize;
}

void MainFrame::SetProperties() {
  label_title_->SetFont(wxFont(16, wxDEFAULT, wxNORMAL, wxBOLD, 0, wxT("")));
}

void MainFrame::OnButtonNextClick(wxCommandEvent &event) {
  if (active_panel_ == NULL) {
    wxLogWarning("active_panel_ == NULL");
  }

  if (!active_panel_->Next()) {
    wxLogDebug("End of panel pages, going to next panel");
    DisplayNextPanel();
  }
}

void MainFrame::DoLayout() {
  // TODO(egeldenhuys): panel_main_frame_ otherwise we have strange backround
  // colour on windows

  // HEADER
  sizer_main_frame_->Add(label_title_, 1, wxEXPAND | wxALIGN_CENTER, 0);
  // bar
  wxStaticLine *line = new wxStaticLine(panel_main_, wxID_ANY);
  line->SetMinSize(wxSize(10, 4));  // Required to work
  sizer_main_frame_->Add(line, 1, wxEXPAND, 0);

  // sizer_content_
  for (size_t i = 0; i < DataManager::PanelId::kPanelCount; i++) {
    wxLogDebug(_("Adding panel ") +
               _(data_manager_->GetPanelByIndex(i)->GetPanelTitle()) +
               _(" to notebook"));

    wxPanel *panel = data_manager_->GetPanelByIndex(i);
    notebook_->AddPage(panel,
                      data_manager_->GetPanelByIndex(i)->GetPanelTitle());
  }

  sizer_content_->Add(notebook_, 1, wxEXPAND, 0);
  sizer_content_->Add(0, 0, 0, 0);

#ifdef PROTHESIS_VERSION
  wxStaticText *version = new wxStaticText(panel_main_,
                                           wxID_ANY,
                                           _(PROTHESIS_VERSION));
  sizer_content_->Add(version, 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
#else
  sizer_content_->Add(0, 0, 0, 0);
#endif

  wxButton *button_next = new wxButton(panel_main_, wxID_ANY, _("Next"));
  button_next->Bind(wxEVT_BUTTON, &MainFrame::OnButtonNextClick, this);

  sizer_content_->Add(button_next, 0, wxALIGN_RIGHT | wxALIGN_BOTTOM | wxALL,
                      20);

  sizer_content_->AddGrowableCol(1);
  sizer_content_->AddGrowableRow(1);

  sizer_main_frame_->Add(sizer_content_, 1, wxEXPAND, 0);

  sizer_main_frame_->AddGrowableCol(0);
  sizer_main_frame_->AddGrowableRow(2);
  panel_main_->SetSizer(sizer_main_frame_);
  sizer_main_frame_->Fit(panel_main_);
  Fit();
  Layout();
}

MainFrame::~MainFrame() {
  wxLogDebug("MainFrame::~MainFrame() START");
  exit_requested_ = true;
  data_manager_->SaveUserConfig();
  delete data_manager_;
  delete notebook_;
  wxLogDebug("MainFrame::~MainFrame() END");
}
