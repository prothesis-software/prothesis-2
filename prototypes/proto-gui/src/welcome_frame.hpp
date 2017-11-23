#ifndef WELCOME_FRAME_H
#define WELCOME_FRAME_H

#include <wx/wxprec.h>
#include "proto_gui_app.hpp"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class WelcomeFrame: public wxFrame {
public:
  WelcomeFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
  wxButton *btnClose;
  wxBoxSizer *sizerA;
  wxBoxSizer *sizerB;
  void OnExit( wxCommandEvent& event );

  enum {
    btnCloseId = -1 // Starting id
  };
  
};

#endif

  
