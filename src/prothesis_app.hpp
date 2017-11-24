#ifndef PROTHESIS_APP_HPP_
#define PROTHESIS_APP_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class ProthesisApp : public wxApp {
 public:
  virtual bool OnInit();
  virtual ~ProthesisApp();
};

DECLARE_APP(ProthesisApp)

#endif  // PROTHESIS_APP_HPP_
