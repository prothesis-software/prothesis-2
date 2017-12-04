#ifndef PANELS_PASSION_PANEL_HPP_
#define PANELS_PASSION_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>
#include <memory>
#include <vector>

#include "src/questions_panel.hpp"

class PassionPanel : public QuestionsPanel {
 public:
  PassionPanel(wxWindow* parent,
               wxWindowID id,
               std::string panel_name,
               std::string panel_title,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               int64_t style = 0);
  ~PassionPanel();
};

#endif  // PANELS_PASSION_PANEL_HPP_
