#ifndef PANELS_PRIORITIES_PANEL_HPP_
#define PANELS_PRIORITIES_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/listbox.h>

#include <memory>
#include <string>

#include "src/data_panel.hpp"

class PrioritiesPanel : public DataPanel {
 public:
  PrioritiesPanel(wxWindow *parent,
                  wxWindowID id,
                  std::string panel_name,
                  std::string panel_title,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize,
                  int64_t style = 0);
  ~PrioritiesPanel();

  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;
  std::shared_ptr<cpptoml::table> GetUserState() override;
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();
};

#endif  // PANELS_PRIORITIES_PANEL_HPP_
