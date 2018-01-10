#ifndef PANELS_CAREER_ORIENTATION_PANEL_HPP_
#define PANELS_CAREER_ORIENTATION_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <wx/utils.h>

#include <memory>
#include <string>
#include <vector>

#include "src/data_panel.hpp"
#include "src/paged_panel.hpp"

class CareerOrientationPanel : public PagedPanel {
 public:
  CareerOrientationPanel(wxWindow *parent, wxWindowID id,
                         std::string panel_name, std::string panel_title,
                         const wxPoint &pos = wxDefaultPosition,
                         const wxSize &size = wxDefaultSize, int64_t style = 0);

  wxPanel *CreateInternalPanel(std::string question,
                               std::vector<std::string> options);
  bool SetGuiState(std::shared_ptr<cpptoml::table> state);
  bool SetUserState(std::shared_ptr<cpptoml::table> state);
  std::shared_ptr<cpptoml::table> GetUserState();
  bool SetAnswer(std::string question, std::vector<std::string> options);
  wxCheckListBox *AddCheckboxes(wxPanel *panel,
                                std::vector<std::string> titles);

 private:
  std::vector<wxCheckListBox *> checkboxes;
};
#endif  // PANELS_CAREER_ORIENTATION_PANEL_HPP_
