#ifndef PROTHESIS_APP_HPP_
#define PROTHESIS_APP_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data_manager.hpp"

class ProthesisApp : public wxApp {
 public:
  virtual bool OnInit();
  virtual ~ProthesisApp();

 private:
  DataManager *data_manager_;
};

DECLARE_APP(ProthesisApp)

#endif  // PROTHESIS_APP_HPP_
