#ifndef COMPONENTS_LIFE_KEY_CONTAINER_HPP_
#define COMPONENTS_LIFE_KEY_CONTAINER_HPP_

#include "src/coloured_button_container.hpp"

class LifeKeyContainer : public ColouredButtonContainer {
 public:
  LifeKeyContainer(wxWindow* parent, wxWindowID id, std::string panel_name,
                   std::string panel_title,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~LifeKeyContainer(){};

  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  void RefreshLifeKeyTags();

  struct LifeKeyWithTag {
    std::string key;
    std::string tag;
  };

 private:
  std::string GetTagByKey(std::string key);
  wxBoxSizer* sizer_tags_ = NULL;
  std::vector<struct LifeKeyWithTag> life_key_tags_;
  wxStaticText* label_tags_[3];
  void DoLayout();

};

#endif  // COMPONENTS_LIFE_KEY_CONTAINER_HPP_
