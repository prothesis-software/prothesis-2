#include "main_frame.hpp"
#include <csignal>
#include <string>
#include <vector>

#include "navigation_drawer.hpp"

void MainFrame::OnKill(int sig) {
  wxLogDebug("MainFrame::OnKill");
  wxExit();
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, int64_t style,
                     const wxString name)
    : wxFrame(parent, id, title, pos, size, style, name) {
  std::signal(SIGINT, OnKill);
  panel_main_ = new wxPanel(this, wxID_ANY);

  sizer_main_frame_ = new wxFlexGridSizer(1, 1, 0, 0);
  notebook_ = new wxNotebook(panel_main_, wxID_ANY, wxDefaultPosition,
                             wxDefaultSize, wxNB_TOP);
  notebook_->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED,
                  &MainFrame::OnNotebookSelectionChange, this);
  notebook_assessments_ = new wxNotebook(notebook_, wxID_ANY, wxDefaultPosition,
                                         wxDefaultSize, wxNB_TOP);
  notebook_assessments_->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED,
                              &MainFrame::OnNotebookSelectionChange, this);

  data_manager_ = new DataManager(notebook_, notebook_assessments_);

  DoLayout();
  Fit();

  wxSize minSize = GetOverallMinSize();

  // To fix scroll bars on theme analysis panel
  minSize.IncBy(10, 10);

  // We want to be able to make smaller than the giant
  // analysis panel, so this is temporarily disabled
  // SetMinSize(minSize);

  SetSize(minSize);

  this->Bind(wxEVT_SIZE, &MainFrame::OnSizeChange, this);
}

void MainFrame::OnClose(wxCloseEvent& e) {
  wxLogDebug(_("MainFrame::OnClose()"));
  data_manager_->SaveUserConfig();
}

void MainFrame::OnNotebookSelectionChange(wxBookCtrlEvent& event) {
  // Only do stuff if there are still objects to work with
  wxLogDebug(_("MainFrame::OnNotebookSelectionChange() START"));

  if (!exit_requested_ && index_layout_.size() == 2) {
    int top_index = notebook_->GetSelection();
    int bottom_index = notebook_assessments_->GetSelection();

    if (top_index == wxNOT_FOUND || bottom_index == wxNOT_FOUND) {
      wxLogDebug("top or bottom index == wxNOT_FOUND");
    }

    if (size_t(top_index) >= index_layout_.at(0).size()) {
      wxLogDebug("top >= 0.size");
    }

    if (size_t(bottom_index) >= index_layout_.at(1).size()) {
      wxLogDebug("bottom >= 1.size");
    }

    DataPanel* panel = NULL;

    if (top_index == 1) {
      panel = index_layout_.at(1).at(bottom_index);

      DataManager::PanelId id =
          data_manager_->GetIdFromName(panel->GetPanelName());

      if (id == DataManager::PanelId::kWorkEnvironmentPanel) {
        panel->GetUserState();
      }
    } else {
      panel = index_layout_.at(0).at(top_index);
    }

    if (panel) {
      panel->OnTabActivate();
    }
  }

  wxLogDebug(_("MainFrame::OnNotebookSelectionChange() END"));
}

bool MainFrame::DisplayNextPanel() {
  int top_index = notebook_->GetSelection();
  int top_count = notebook_->GetPageCount();

  int bottom_index = notebook_assessments_->GetSelection();
  int bottom_count = notebook_assessments_->GetPageCount();

  if (top_index == 1) {
    if (bottom_index < bottom_count - 1) {
      notebook_assessments_->AdvanceSelection();
      return true;
    }
  }

  if (top_index < top_count - 1) {
    notebook_->AdvanceSelection();
    return true;
  } else {
    return false;
  }

  return false;
}

wxSize MainFrame::GetOverallMinSize() {
  Freeze();
  wxLogDebug(_("Getting best size..."));
  wxSize minSize = GetSize();

  wxLogDebug(_(std::to_string(minSize.x)) + _(", ") +
             _(std::to_string(minSize.y)));

  while (DisplayNextPanel() != false) {
    Fit();
    wxSize tmpSize = GetSize();
    wxLogDebug(_(std::to_string(tmpSize.x)) + _(", ") +
               _(std::to_string(tmpSize.y)));

    if (tmpSize.x > minSize.x) {
      minSize.x = tmpSize.x;
    }

    if (tmpSize.y > minSize.y) {
      minSize.y = tmpSize.y;
    }
  }

  wxLogDebug(_("Best size = ") + _(std::to_string(minSize.x)) + _(", ") +
             _(std::to_string(minSize.y)));

  notebook_->SetSelection(0);
  notebook_assessments_->SetSelection(0);

  Thaw();
  return minSize;
}

void MainFrame::OnSizeChange(wxSizeEvent& event) {
  wxLogDebug("Resize MainFrame");

  panel_main_->SetSize(GetClientSize());
  this->FitInside();
}

void MainFrame::DoLayout() {
  std::vector<DataPanel*> top_layout;
  std::vector<DataPanel*> bottom_layout;

  // sizer_content_
  for (size_t i = 0; i < DataManager::PanelId::kPanelCount; i++) {
    if (top_layout.size() != 1) {
      wxLogDebug(_("Adding panel ") +
                 _(data_manager_->GetPanelByIndex(i)->GetPanelTitle()) +
                 _(" to notebook"));

      DataPanel* panel = data_manager_->GetPanelByIndex(i);
      wxNotebook* panel_parent = static_cast<wxNotebook*>(panel->GetParent());
      panel_parent->AddPage(panel,
                            data_manager_->GetPanelByIndex(i)->GetPanelTitle());

      if (panel_parent == notebook_) {
        top_layout.push_back(panel);
      } else {
        bottom_layout.push_back(panel);
      }
    } else {
      // Insert psuedo panel
      notebook_->InsertPage(1, notebook_assessments_, "Assessments");
      top_layout.push_back(NULL);
      // Need to adjust i
      i--;
    }
  }

  index_layout_.push_back(top_layout);
  index_layout_.push_back(bottom_layout);
  // sizer_main_frame_->Add(notebook_, 1, wxEXPAND | wxALL, 10);

  // sizer_content_->Add(notebook_, 1, wxEXPAND, 0);
  // sizer_content_->Add(0, 0, 0, 0);

#ifdef PROTHESIS_VERSION
  // wxStaticText *version = new wxStaticText(panel_main_,
  //                                          wxID_ANY,
  //                                          _(PROTHESIS_VERSION));
  // sizer_content_->Add(version, 0, wxALIGN_LEFT | wxALIGN_BOTTOM, 0);
#else
  // sizer_content_->Add(0, 0, 0, 0);
#endif

  // sizer_content_->Add(0, 0, 0, 0);

  // sizer_content_->AddGrowableCol(0);
  // sizer_content_->AddGrowableRow(0);
  // sizer_content_->AddGrowableCol(1);
  // sizer_content_->AddGrowableRow(1);

  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  panel_main_->SetSizer(sizer);
  sizer->Add(notebook_, 1, wxEXPAND, 0);

  sizer_main_frame_->Add(panel_main_, 1, wxEXPAND, 0);

  sizer_main_frame_->AddGrowableCol(0);
  sizer_main_frame_->AddGrowableRow(0);

  this->SetSizer(sizer_main_frame_);
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
