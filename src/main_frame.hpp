#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MainFrame: public wxFrame {
 public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

#endif  // MAIN_FRAME_HPP_
