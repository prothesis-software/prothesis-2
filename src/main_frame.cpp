#include "main_frame.hpp"

MainFrame::MainFrame(wxWindow *parent,
                     wxWindowID id,
                     const wxString &title,
                     const wxPoint &pos,
                     const wxSize &size,
                     int64_t style,
                     const wxString name)
  : wxFrame(parent, id, title, pos, size, style, name) {
  details_panel_ = new DetailsPanel(this, wxID_ANY);
  DoLayout();
}

void MainFrame::DoLayout() {
  wxBoxSizer *main_frame_sizer = new wxBoxSizer(wxVERTICAL);
  // wxSizerItem* wxSizer::Add (wxWindow *window,
  //                            int proportion = 0,
  //                            int flag = 0,
  //                            int border = 0,
  //                            wxObject *userData = NULL);

  main_frame_sizer->Add(details_panel_, 1, wxEXPAND, 0);
  this->SetSizer(main_frame_sizer);
  main_frame_sizer->Fit(this);
  this->Layout();
}
