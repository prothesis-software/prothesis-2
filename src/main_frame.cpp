#include "main_frame.hpp"

MainFrame::MainFrame(const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size)
  : wxFrame(reinterpret_cast<wxFrame*>(NULL), -1, title, pos, size) {
  // begin wxGlade: MainFrame::MainFrame
  details_panel = new DetailsPanel(this, wxID_ANY);

  set_properties();
  do_layout();
  // end wxGlade
}

void MainFrame::set_properties() {
  // begin wxGlade: MainFrame::set_properties
  SetTitle(_("frame"));
  // end wxGlade
}


void MainFrame::do_layout() {
  // begin wxGlade: MainFrame::do_layout
  wxBoxSizer* main_frame_sizer = new wxBoxSizer(wxVERTICAL);
  main_frame_sizer->Add(details_panel, 1, wxEXPAND, 0);
  SetSizer(main_frame_sizer);
  main_frame_sizer->Fit(this);
  Layout();
  // end wxGlade
}
