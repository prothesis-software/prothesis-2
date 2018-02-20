#include "life_keys_info_panel.hpp"

LifeKeysInfoPanel::LifeKeysInfoPanel(wxWindow* parent, wxWindowID id,
                                     const wxPoint& pos, const wxSize& size,
                                     int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  wxLogDebug("LifeKeysInfoPanel::LifeKeysInfoPanel() START");
  for (size_t i = 0; i < 3; i++) {
    choice_boxes_keys_[i] = NULL;
  }

  DoLayout();
  wxLogDebug("LifeKeysInfoPanel::LifeKeysInfoPanel() END");
}

void LifeKeysInfoPanel::SetLifeKeyData(
    std::shared_ptr<cpptoml::table> gui_state) {
  // Keys
  auto panel_table = gui_state->get_table("external");

  // Get root table from state
  if (panel_table) {
    // Get life keys table
    auto life_keys_table = panel_table->get_table("life_keys");

    if (life_keys_table) {
      // Get type table array
      auto life_key_types = life_keys_table->get_table_array("type");

      if (life_key_types) {
        // Iterate over the types and collect the keys
        life_keys_keys_ = new wxArrayString();

        for (const auto& life_key_type : *life_key_types) {
          auto key = life_key_type->get_as<std::string>("key");

          if (key) {
            // Add the key to the key vector
            life_keys_keys_->Add(wxString(*key));
          } else {
            wxLogDebug(_("'key' was not found for ") +
                       _("table external.life_keys.type ") +
                       _("for panel external"));
          }  // key
        }    // key iteration loop

      } else {
        wxLogDebug(_("Table array external.life_keys.type was not found") +
                   _("for panel LifeKeysInfoPanel"));
      }  // life_key_types
    } else {
      wxLogDebug(
          _("Table external.life_keys was not found for panel external"));
    }  // life_keys_table

  } else {
    wxLogDebug(_("No GUI table exists for panel external"));
  }  // panel_table

  // Info
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

  CreateChoiceBoxes(sizer_->GetStaticBox(), sizer_choice_boxes_,
                    life_keys_keys_);
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

std::vector<std::string> LifeKeysInfoPanel::GetLifeKeys() {
  std::vector<std::string> result;

  // life keys
  for (size_t i = 0; i < 3; i++) {
    if (choice_boxes_keys_[i]) {
      if (choice_boxes_keys_[i]->GetSelection() != wxNOT_FOUND) {
        const int selection = choice_boxes_keys_[i]->GetSelection();

        const std::string key =
            choice_boxes_keys_[i]->GetString(selection).ToStdString();

        result.push_back(key);
      }
    }
  }

  return result;
}

void LifeKeysInfoPanel::OnLifeKeyChange(wxCommandEvent& event) {
  SetLifeKeys(GetLifeKeys());
}

void LifeKeysInfoPanel::CreateChoiceBoxes(wxWindow* parent,
                                          wxSizer* injection_sizer,
                                          wxArrayString* keys) {
  // Create choice boxes
  for (size_t i = 0; i < 3; i++) {
    choice_boxes_keys_[i] = new wxChoice(parent, wxID_ANY, wxDefaultPosition,
                                         wxSize(-1, -1), *keys);
    choice_boxes_keys_[i]->Bind(wxEVT_CHOICE,
                                &LifeKeysInfoPanel::OnLifeKeyChange, this);
    injection_sizer->Add(choice_boxes_keys_[i], 0, 0, 0);
    injection_sizer->AddSpacer(5);
  }
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

  // Set choice box selections
  for (size_t i = 0; i < 3 && i < life_keys.size(); i++) {
    const int selection = choice_boxes_keys_[i]->FindString(life_keys[i]);

    if (selection != wxNOT_FOUND) {
      choice_boxes_keys_[i]->SetSelection(selection);
    } else {
      wxLogWarning(_("The life key ") + _(life_keys[i]) +
                   _(" was not found as an option in the GUI config"));
    }
  }

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
  wxLogDebug("LifeKeysInfoPanel::DoLayout() START");
  sizer_ = new wxStaticBoxSizer(wxVERTICAL, this, "Life Keys");

  sizer_choice_boxes_ = new wxBoxSizer(wxHORIZONTAL);
  sizer_->Add(sizer_choice_boxes_, 0, wxALL, 6);

  CreateLifeKeysPanel();

  this->SetSizer(sizer_);
  Layout();
  wxLogDebug("LifeKeysInfoPanel::DoLayout() END");
}
