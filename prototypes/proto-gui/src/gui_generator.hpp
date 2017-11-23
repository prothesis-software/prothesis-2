#ifndef GUI_GENERATOR
#define GUI_GENERATOR

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class GuiGenerator {
public:
  int injectButtons(wxWindow *window, wxBoxSizer *parentSizer, std::string configFile);
};
  
#endif
