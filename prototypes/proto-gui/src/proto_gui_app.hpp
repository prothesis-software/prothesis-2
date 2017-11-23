#ifndef PROTO_GUI_APP
#define PROTO_GUI_APP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ProtoGuiApp: public wxApp {
public:
  virtual bool OnInit();
  virtual ~ProtoGuiApp();

};

DECLARE_APP(ProtoGuiApp)

#endif
