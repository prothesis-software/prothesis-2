#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "panels/details_panel.hpp"

class MainFrame: public wxFrame {
 public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

 private:
  // begin wxGlade: MainFrame::methods
  void set_properties();
  void do_layout();
  // end wxGlade

 protected:
  // begin wxGlade: MainFrame::attributes
  DetailsPanel* details_panel;
  // end wxGlade
};

#endif  // MAIN_FRAME_HPP_
