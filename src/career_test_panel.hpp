#ifndef CAREER_TEST_PANEL_HPP_
#define CAREER_TEST_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/spinctrl.h>

#include <memory>
#include <string>
#include <vector>

#include "data_panel.hpp"

class CareerTestPanel : public DataPanel {
 public:
  CareerTestPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                  std::string panel_title,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~CareerTestPanel();

  /**
   * Not used.
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification for Getting the User state:
   * [panel_name]
   *   interest_1 = "Hockey"
   *   interest_1_percentage = 54
   *   interest_2 = "Golf"
   *   interest_2_percentage = 0
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML Specification is the same as for GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();
  std::vector<wxTextCtrl*> text_interests_;
  std::vector<wxSpinCtrl*> spin_ctrl_percentages_;
};
#endif  // CAREER_TEST_PANEL_HPP_
