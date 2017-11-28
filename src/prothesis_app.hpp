#ifndef PROTHESIS_APP_HPP_
#define PROTHESIS_APP_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <csignal>
#include "data_manager.hpp"

class ProthesisApp : public wxApp {
 public:
  virtual bool OnInit();
  virtual ~ProthesisApp();
  virtual int OnExit();
  static void OnKillRequest(int sig_num);

 private:
  DataManager *data_manager_;
};

DECLARE_APP(ProthesisApp)

#endif  // PROTHESIS_APP_HPP_
