#ifndef COMPONENTS_LIFE_KEYS_INFO_PANEL_HPP_
#define COMPONENTS_LIFE_KEYS_INFO_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "include/cpptoml.h"

class LifeKeysInfoPanel : public wxPanel {
 public:
  LifeKeysInfoPanel(wxWindow* parent, wxWindowID id,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~LifeKeysInfoPanel() { delete life_keys_keys_; };

  /**
   * Recreate the internal layout based on the given keys
   */
  void SetLifeKeys(std::vector<std::string> life_keys);

  /**
   * TOML SPEC:
   * [external.life_keys]
   *   [[external.life_keys.type]]
   *     key = ""
   *     title = ""
   *     characteristics = [""]
   *     work_environments = [""]
   *     things_they_love_to_do = [""]
   */
  void SetLifeKeyData(std::shared_ptr<cpptoml::table>(gui_state));

  void OnLifeKeyChange(wxCommandEvent& event);  // NOLINT
  std::vector<std::string> GetLifeKeys();

  struct LifeKey {
    std::string key;
    std::string title;
    std::vector<std::string> love_to_dos;
  };

 private:
  void DoLayout();
  void CreateLifeKeysPanel();
  void CreateChoiceBoxes(wxWindow* parent, wxSizer* injection_sizer,
                                wxArrayString* keys);
  struct LifeKey GetLifeKeyDataByKey(std::string key);
  std::vector<std::string> active_life_keys_;
  std::vector<struct LifeKey> life_keys_;
  wxArrayString* life_keys_keys_ = NULL;
  wxChoice* choice_boxes_keys_[3];
  wxPanel* panel_life_keys_ = NULL;
  wxBoxSizer* sizer_choice_boxes_ = NULL;
  wxBoxSizer* sizer_life_keys_ = NULL;
  wxStaticBoxSizer* sizer_ = NULL;
};

#endif  // COMPONENTS_LIFE_KEYS_INFO_PANEL_HPP_
