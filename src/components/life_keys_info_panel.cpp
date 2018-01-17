#include "life_keys_info_panel.hpp"

LifeKeysInfoPanel::LifeKeysInfoPanel(wxWindow* parent, wxWindowID id,
                                     const wxPoint& pos, const wxSize& size,
                                     int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  DoLayout();
}

void LifeKeysInfoPanel::SetLifeKeyData(
    std::shared_ptr<cpptoml::table> gui_state) {
  auto external_panel_table = gui_state->get_table("external");
  if (external_panel_table) {
    auto life_keys_table = external_panel_table->get_table("life_keys");
    if (life_keys_table) {
      auto type_array = life_keys_table->get_table_array("type");
      if (type_array) {
        for (const auto& type : *type_array) {
          auto key = type->get_as<std::string>("key");
          auto title = type->get_as<std::string>("title");
          auto love_to_do =
              type->get_array_of<std::string>("things_they_love_to_do");

          struct LifeKey life_key;
          if (key) {
            life_key.key = *key;
            wxLogDebug(_(*key));
          }
          if (title) {
            life_key.title = *title;
            wxLogDebug(_(*title));
          }
          if (love_to_do) {
            for (const std::string element : *love_to_do) {
              wxLogDebug(_(element));
              life_key.love_to_dos.push_back(element);
            }
          }

          life_keys_.push_back(life_key);
        }
      }
    }
  }
}

struct LifeKeysInfoPanel::LifeKey LifeKeysInfoPanel::GetLifeKeyDataByKey(
    std::string key) {
  for (size_t i = 0; i < life_keys_.size(); i++) {
    if (life_keys_.at(i).key.compare(key) == 0) {
      return life_keys_.at(i);
    }
  }

  struct LifeKey error;
  error.key = "Error";

  return error;
}

void LifeKeysInfoPanel::CreateLifeKeysPanel() {
  if (panel_life_keys_ != NULL) {
    sizer_->Detach(panel_life_keys_);
    delete panel_life_keys_;
  }

  panel_life_keys_ = new wxPanel(sizer_->GetStaticBox(), wxID_ANY);
  sizer_life_keys_ = new wxBoxSizer(wxVERTICAL);

  panel_life_keys_->SetSizer(sizer_life_keys_);
  sizer_->Add(panel_life_keys_, 0, wxEXPAND | wxALL, 6);
}

void LifeKeysInfoPanel::SetLifeKeys(std::vector<std::string> life_keys) {
  active_life_keys_ = life_keys;

  CreateLifeKeysPanel();

  for (size_t i = 0; i < life_keys.size(); i++) {
    struct LifeKey life_key_data = GetLifeKeyDataByKey(life_keys.at(i));
    if (life_key_data.key.compare(life_keys.at(i)) == 0) {
      wxLogDebug(_("Found life key") + _(life_keys.at(i)));

      wxStaticText* label_title =
          new wxStaticText(panel_life_keys_, wxID_ANY, life_key_data.title);
      wxFont font_title = label_title->GetFont();
      font_title.SetPointSize(16);
      font_title.Bold();
      label_title->SetFont(font_title);
      sizer_life_keys_->Add(label_title, 0, 0, 0);

      sizer_life_keys_->AddSpacer(0);

      for (size_t j = 0; j < life_key_data.love_to_dos.size(); j++) {
        wxStaticText* label_love =
            new wxStaticText(panel_life_keys_, wxID_ANY,
                             _("- ") + _(life_key_data.love_to_dos.at(j)));

        sizer_life_keys_->Add(label_love, 0, 0, 0);
      }

      sizer_life_keys_->AddSpacer(15);
    } else {
      wxLogWarning(_("Invalid life key:") + _(life_keys.at(i)));
    }
  }

  sizer_->Fit(this);
  Layout();
}

void LifeKeysInfoPanel::DoLayout() {
  sizer_ = new wxStaticBoxSizer(wxVERTICAL, this, "Life Keys");

  CreateLifeKeysPanel();

  this->SetSizer(sizer_);
  Layout();
}
