#include "life_key_container.hpp"

LifeKeyContainer::LifeKeyContainer(wxWindow* parent, wxWindowID id,
                                   std::string panel_name,
                                   std::string panel_title, const wxPoint& pos,
                                   const wxSize& size, int64_t style)
    : ColouredButtonContainer(parent, id, panel_name, panel_title, pos, size,
                              style) {
  for (size_t i = 0; i < 3; i++) {
    label_tags_[i] = NULL;
  }

  DoLayout();
}

bool LifeKeyContainer::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());
  if (panel_table) {
    auto tag_table_array = panel_table->get_table_array("life_key_tag");

    if (tag_table_array) {
      for (const auto& tag_table : *tag_table_array) {
        struct LifeKeyWithTag life_key_with_tag;

        auto key = tag_table->get_as<std::string>("key");
        if (key) {
          life_key_with_tag.key = *key;
        }

        auto tag = tag_table->get_as<std::string>("tag");
        if (tag) {
          life_key_with_tag.tag = *tag;
        }

        life_key_tags_.push_back(life_key_with_tag);
      }
    }
  } else {
    wxLogDebug("Could not find table for Theme Analysis");
  }

  return true;
}

std::string LifeKeyContainer::GetTagByKey(std::string key) {
  for (size_t i = 0; i < life_key_tags_.size(); i++) {
    if (life_key_tags_.at(i).key.compare(key) == 0) {
      return life_key_tags_.at(i).tag;
    }
  }

  return "Key not found";
}

void LifeKeyContainer::RefreshLifeKeyTags() {
  wxLogDebug("Refreshing life key tags");
  std::vector<ColouredButton*> buttons = this->GetColouredButtons();

  if (buttons.size() > 3) {
    wxLogDebug("ERROR: There are more than 3 life keys!");
    wxLogError("There are more than 3 life keys!");
  }

  for (size_t i = 0; i < buttons.size(); i++) {
    label_tags_[i]->SetLabel(
        GetTagByKey(buttons.at(i)->GetLabel().ToStdString()));
  }
}

void LifeKeyContainer::DoLayout() {
  sizer_tags_ = new wxBoxSizer(wxVERTICAL);

  for (size_t i = 0; i < 3; i++) {
    label_tags_[i] = new wxStaticText(this, wxID_ANY, "TAG");
    sizer_tags_->Add(label_tags_[i], 0, 0, 0);
  }

  sizer_root_->Add(sizer_tags_, 0, 0, 0);
}
