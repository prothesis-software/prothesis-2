#include "external_panel.hpp"

#include <memory>
#include <string>
#include <vector>

ExternalPanel::ExternalPanel(wxWindow* parent, wxWindowID id,
                             std::string panel_name, std::string panel_title,
                             const wxPoint& pos, const wxSize& size,
                             int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  wxLogDebug("ExternalPanel::ExternalPanel() START");
  DoLayout();
  wxLogDebug("ExternalPanel::ExternalPanel() END");
}

ExternalPanel::~ExternalPanel() {
  wxLogDebug("ExternalPanel::~ExternalPanel()");
}

bool ExternalPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug("ExternalPanel::SetGuiState()");

  mbti_info_panel_->SetMbtiInfoData(state);
  panel_life_keys_info_->SetLifeKeyData(state);

  return true;
}

std::vector<std::string> ExternalPanel::GetLifeKeys() {
  return panel_life_keys_info_->GetLifeKeys();
}

std::shared_ptr<cpptoml::table> ExternalPanel::GetUserState() {
  auto panel_table = cpptoml::make_table();
  auto life_keys_table = cpptoml::make_table();
  auto life_keys_table_array = cpptoml::make_table_array();
  auto mbti_array = cpptoml::make_array();

  // mbti
  std::vector<std::string> mbti = mbti_info_panel_->GetMbtiAsVector();
  for (size_t i = 0; i < 4; i++) {
    mbti_array->push_back(mbti.at(i));
  }

  // life keys
  size_t keys_found = 0;
  std::vector<std::string> keys = panel_life_keys_info_->GetLifeKeys();

  for (size_t i = 0; i < keys.size(); i++) {
    auto life_key_type = cpptoml::make_table();
    life_key_type->insert("key", keys.at(i));
    life_keys_table_array->push_back(life_key_type);
    keys_found++;
  }

  // career test
  auto career_table = panel_career_->GetUserState();
  panel_table->insert(panel_career_->GetPanelName(), career_table);

  if (keys_found > 0) {
    life_keys_table->insert("type", life_keys_table_array);
    panel_table->insert("life_keys", life_keys_table);
  }
  panel_table->insert("mbti", mbti_array);

  return panel_table;
}

std::string ExternalPanel::GetMbti() { return mbti_info_panel_->GetMbti(); }

bool ExternalPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug(_("ExternalPanel::SetUserState() START"));

  auto panel_table = state->get_table(this->GetPanelName());

  // Get root table from state
  if (panel_table) {
    // Get life keys table
    auto life_keys_table = panel_table->get_table("life_keys");

    if (life_keys_table) {
      // Get type table array
      auto life_key_types = life_keys_table->get_table_array("type");

      if (life_key_types) {
        // Iterate over the types and collect the keys
        std::vector<std::string> keys;

        for (const auto& life_key_type : *life_key_types) {
          auto key = life_key_type->get_as<std::string>("key");

          if (key) {
            // Add the key to the key vector
            keys.push_back(*key);
          } else {
            wxLogDebug(_("'key' was not found for ") +
                       _("table external.life_keys.type ") + _("for panel ") +
                       _(this->GetPanelName()));
          }  // key
        }    // key iteration loop

        if (keys.size() > CHOICE_BOX_KEYS_COUNT) {
          wxLogWarning(_(std::to_string(keys.size())) +
                       _(" life keys found in user config,") + _(" but only") +
                       _(std::to_string(CHOICE_BOX_KEYS_COUNT)) +
                       _(" are allowed to be selected"));
        }

        panel_life_keys_info_->SetLifeKeys(keys);

      } else {
        wxLogDebug(_("Table array external.life_keys.type was not found") +
                   _("for panel ") + _(this->GetPanelName()));
      }  // life_key_types
    } else {
      wxLogDebug(_("Table external.life_keys was not found for panel ") +
                 _(this->GetPanelName()));
    }  // life_keys_table

    // MBTI
    auto mbti_array = panel_table->get_array_of<std::string>("mbti");
    if (mbti_array) {
      mbti_info_panel_->SetMbti(*mbti_array);

    } else {
      wxLogDebug(_("mbti array not found for external panel"));
    }

    panel_career_->SetUserState(panel_table);
  } else {
    wxLogDebug(_("No User table exists for panel ") + _(this->GetPanelName()));
    wxLogDebug(_("ExternalPanel::SetUserState() END"));
    return false;
  }  // panel_table

  mbti_info_panel_->SetMbti(GetMbti());

  wxLogDebug(_("ExternalPanel::SetUserState() END"));
  return true;
}

void ExternalPanel::DoLayout() {
  wxLogDebug("ExternalPanel::DoLayout() START");
  wxFlexGridSizer* sizer = new wxFlexGridSizer(1, 3, 0, 0);
  wxFlexGridSizer* sizer_content = new wxFlexGridSizer(2, 2, 30, 30);

  wxBoxSizer* sizer_left_col = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* sizer_career = new wxBoxSizer(wxVERTICAL);

  panel_life_keys_info_ = new LifeKeysInfoPanel(this, wxID_ANY);

  panel_career_ =
      new CareerTestPanel(this, wxID_ANY, "career_test", "Career Test");
  sizer_career->Add(panel_career_, 0, wxEXPAND | wxALL, 5);

  mbti_info_panel_ = new MbtiInfoPanel(this, wxID_ANY);

  sizer_left_col->Add(mbti_info_panel_, 0, wxBOTTOM, 20);
  sizer_left_col->Add(panel_life_keys_info_, 0, wxALL, 0);

  sizer_content->Add(sizer_left_col, 0, wxALL, 5);
  sizer_content->Add(sizer_career, 0, wxALL, 5);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(sizer_content, 0, 0, 0);
  sizer->Add(0, 0, 0, 0);

  sizer->AddGrowableCol(0);
  sizer->AddGrowableCol(1);

  Layout();
  this->SetSizer(sizer);

  wxLogDebug("ExternalPanel::DoLayout() END");
}
