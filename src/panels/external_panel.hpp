#ifndef PANELS_EXTERNAL_PANEL_HPP_
#define PANELS_EXTERNAL_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/combobox.h>

#include <memory>
#include <string>
#include <vector>

#include "src/data_panel.hpp"

#define CHOICE_BOX_KEYS_COUNT 3

class ExternalPanel : public DataPanel {
 public:
  ExternalPanel(wxWindow *parent, wxWindowID id, std::string panel_name,
                std::string panel_title, const wxPoint &pos = wxDefaultPosition,
                const wxSize &size = wxDefaultSize, int64_t style = 0);
  ~ExternalPanel();

  /**
   * TOML Specification:
   * [external]
   *   [external.life_keys]
   *     [[external.life_keys.type]]
   *       key = "key"
   *       title = "title"
   *       characteristics = ["a", "b", c"]
   *       work_environments = ["a", "b"]
   *       things_they_love_to_do = ["a", "b"]
   *
   * key - used for generating the choices in this panel
   * title - for analysis panel
   * characteristics - for analysis panel
   * work_enviornments - for analysis panel
   * things_they_love_to_do - for analysis panel
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification:
   * [external]
   * [external.life_keys]
   *   [[external.life_keys.type]]
   *     key = "key"
   * mbti = ["I", "S", "T", "J"]
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML Specification: same as GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();
  void AddMbtiTuple(std::vector<wxArrayString> *source_vector, std::string str1,
                    std::string str2);
  wxBoxSizer *sizer_keys_ = NULL;
  wxChoice *choice_boxes_keys_[CHOICE_BOX_KEYS_COUNT];
  wxChoice *choice_boxes_mbti_[4];
};
#endif  // PANELS_EXTERNAL_PANEL_HPP_
