#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "panels/details_panel.hpp"

class MainFrame: public wxFrame {
 public:
  MainFrame(wxWindow *parent,
            wxWindowID id,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            int64_t style = wxDEFAULT_FRAME_STYLE,
            const wxString name = wxFrameNameStr);
 private:
  void DoLayout();

 protected:
  DetailsPanel *details_panel_;
};

#endif  // MAIN_FRAME_HPP_
