#ifndef PANELS_CAREER_GUIDANCE_PANEL_HPP_
#define PANELS_CAREER_GUIDANCE_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "src/data_panel.hpp"
#include "src/mbti_panel.hpp"
#include "src/panels/external_panel.hpp"

class CareerGuidancePanel : public DataPanel {
 public:
  CareerGuidancePanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                      std::string panel_title,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~CareerGuidancePanel();

  /**
   * Fetches the life keys data from [external.life_keys]
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  std::shared_ptr<cpptoml::table> GetUserState() override;

  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

  void OnTabActivate() override;

 private:
  void DoLayout();
  MbtiPanel* panel_mbti_ = NULL;
};
#endif  // PANELS_CAREER_GUIDANCE_PANEL_HPP_
