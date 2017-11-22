#ifndef WELCOME_FRAME
#define WELCOME_FRAME

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class WelcomeFrame: public wxFrame {
public:
  WelcomeFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
  wxButton *btnClose;
  wxBoxSizer *sizerA;
  
  void OnExit( wxCommandEvent& event );

  DECLARE_EVENT_TABLE()
};

enum {
  btnCloseId = wxID_ANY // declares an id which will be used to call our button
};

#endif

  
