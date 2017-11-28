#include "main_frame.hpp"

MainFrame::MainFrame(wxWindow *parent,
                     wxWindowID id,
                     const wxString &title,
                     const wxPoint &pos,
                     const wxSize &size,
                     int64_t style,
                     const wxString name)
  : wxFrame(parent, id, title, pos, size, style, name) {
  active_panel_ = NULL;
  SetProperties();
  DoLayout();
}

void MainFrame::DisplayPanel(DataPanel *panel) {
  const size_t kPanelViewIndex = 1;

  if (active_panel_ != NULL)
    active_panel_->Hide();

  // TODO(egeldenhuys): Detach vs Remove
  main_frame_sizer_->Detach(kPanelViewIndex);
  main_frame_sizer_->Insert(kPanelViewIndex, panel, 1, wxEXPAND, 0);
  panel->Show();
  active_panel_ = panel;

  Layout();
  Fit();
}

void MainFrame::SetProperties() {
  // void
}

void MainFrame::DoLayout() {
  main_frame_sizer_ = new wxFlexGridSizer(2, 3, 0, 0);

  main_frame_sizer_->Add(0, 0, 0, 0);
  main_frame_sizer_->Add(0, 0, 0, 0);  // Place holder for panels (index 1)
  main_frame_sizer_->Add(0, 0, 0, 0);

  // Need to fill empty slots as well
  main_frame_sizer_->Add(0, 0, 0, 0);
  main_frame_sizer_->Add(0, 0, 0, 0);
  main_frame_sizer_->Add(0, 0, 0, 0);

  main_frame_sizer_->AddGrowableCol(0);
  main_frame_sizer_->AddGrowableCol(2);
  main_frame_sizer_->AddGrowableRow(1);

  this->SetSizer(main_frame_sizer_);
  main_frame_sizer_->Fit(this);
  this->Layout();
}
