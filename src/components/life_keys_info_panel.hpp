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
  ~LifeKeysInfoPanel(){};

  /**
   * Recreate the internal layout based on the given keys
   */
  void SetLifeKeys(std::vector<std::string> life_keys);
  void SetLifeKeyData(std::shared_ptr<cpptoml::table>(gui_state));

  struct LifeKey {
    std::string key;
    std::string title;
    std::vector<std::string> love_to_dos;
  };

 private:
  void DoLayout();
  void CreateLifeKeysPanel();
  struct LifeKey GetLifeKeyDataByKey(std::string key);
  std::vector<std::string> active_life_keys_;
  std::vector<struct LifeKey> life_keys_;
  wxPanel* panel_life_keys_ = NULL;
  wxBoxSizer* sizer_life_keys_ = NULL;
  wxStaticBoxSizer* sizer_ = NULL;
};

#endif  // COMPONENTS_LIFE_KEYS_INFO_PANEL_HPP_
