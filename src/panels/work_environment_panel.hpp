#ifndef PANELS_WORK_ENVIRONMENT_PANEL_HPP_
#define PANELS_WORK_ENVIRONMENT_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>

#include "src/data_panel.hpp"

class WorkEnvironmentPanel : public DataPanel {
 public:
  WorkEnvironmentPanel(wxWindow *parent, wxWindowID id, std::string panel_name,
                       std::string panel_title,
                       const wxPoint &pos = wxDefaultPosition,
                       const wxSize &size = wxDefaultSize, int64_t style = 0);
  ~WorkEnvironmentPanel();

  /**
   * TOML Spec:
   * [work_environment]
   *   [[work_environment.type]]
   *     mbti = "ISTJ"
   *     list = ["line 1", "line x..."]
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * Depends ExternalPanel. Returns NULL.
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * Depends on ExternalPanel.
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();
  void FitText();
  std::shared_ptr<cpptoml::table> work_table_ = NULL;
  wxStaticText *label_mbti_ = NULL;
  wxTextCtrl *text_description_ = NULL;
};
#endif  // PANELS_WORK_ENVIRONMENT_PANEL_HPP_
