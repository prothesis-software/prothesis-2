#include "external_panel.hpp"

#include <memory>
#include <string>
#include <vector>

ExternalPanel::ExternalPanel(wxWindow* parent, wxWindowID id,
                             std::string panel_name, std::string panel_title,
                             const wxPoint& pos, const wxSize& size,
                             int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  sizer_keys_ = new wxBoxSizer(wxVERTICAL);

  for (size_t i = 0; i < CHOICE_BOX_KEYS_COUNT; i++) {
    choice_boxes_keys_[i] = NULL;
  }

  DoLayout();
}

ExternalPanel::~ExternalPanel() {
  wxLogDebug("ExternalPanel::~ExternalPanel()");
}

bool ExternalPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  mbti_info_panel_->SetMbtiInfoData(state);

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
        wxArrayString keys;

        for (const auto& life_key_type : *life_key_types) {
          auto key = life_key_type->get_as<std::string>("key");

          if (key) {
            // Add the key to the key vector
            keys.Add(wxString(*key));
          } else {
            wxLogDebug(_("'key' was not found for ") +
                       _("table external.life_keys.type ") + _("for panel ") +
                       _(this->GetPanelName()));
          }  // key
        }    // key iteration loop

        // Create choice boxes
        for (size_t i = 0; i < CHOICE_BOX_KEYS_COUNT; i++) {
          choice_boxes_keys_[i] = new wxChoice(
              this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), keys);
          sizer_keys_->Add(choice_boxes_keys_[i], 0, 0, 0);
          sizer_keys_->AddSpacer(5);
        }
      } else {
        wxLogDebug(_("Table array external.life_keys.type was not found") +
                   _("for panel ") + _(this->GetPanelName()));
      }  // life_key_types
    } else {
      wxLogDebug(_("Table external.life_keys was not found for panel ") +
                 _(this->GetPanelName()));
    }  // life_keys_table

  } else {
    wxLogDebug(_("No GUI table exists for panel ") + _(this->GetPanelName()));
    return false;
  }  // panel_table

  return true;
}

std::shared_ptr<cpptoml::table> ExternalPanel::GetUserState() {
  auto panel_table = cpptoml::make_table();
  auto life_keys_table = cpptoml::make_table();
  auto life_keys_table_array = cpptoml::make_table_array();
  auto mbti_array = cpptoml::make_array();

  // mbti
  std::string mbti[4];
  for (size_t i = 0; i < 4; i++) {
    const int selection = choice_boxes_mbti_[i]->GetSelection();
    if (selection != wxNOT_FOUND) {
      const std::string value =
          choice_boxes_mbti_[i]->GetString(selection).ToStdString();

      mbti[i] = value;
    } else {
      mbti[i] = "";
    }
    mbti_array->push_back(mbti[i]);
  }

  // life keys
  size_t keys_found = 0;
  for (size_t i = 0; i < CHOICE_BOX_KEYS_COUNT; i++) {
    if (choice_boxes_keys_[i]) {
      if (choice_boxes_keys_[i]->GetSelection() != wxNOT_FOUND) {
        auto life_key_type = cpptoml::make_table();
        const int selection = choice_boxes_keys_[i]->GetSelection();

        const std::string key =
            choice_boxes_keys_[i]->GetString(selection).ToStdString();

        life_key_type->insert("key", key);
        life_keys_table_array->push_back(life_key_type);
        keys_found++;
      }
    }
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
        wxArrayString keys;

        for (const auto& life_key_type : *life_key_types) {
          auto key = life_key_type->get_as<std::string>("key");

          if (key) {
            // Add the key to the key vector
            keys.Add(wxString(*key));
          } else {
            wxLogDebug(_("'key' was not found for ") +
                       _("table external.life_keys.type ") + _("for panel ") +
                       _(this->GetPanelName()));
          }  // key
        }    // key iteration loop

        if (keys.Count() > CHOICE_BOX_KEYS_COUNT) {
          wxLogWarning(_(std::to_string(keys.Count())) +
                       _(" life keys found in user config,") + _(" but only") +
                       _(std::to_string(CHOICE_BOX_KEYS_COUNT)) +
                       _(" are allowed to be selected"));
        }

        // Set choice box selections
        for (size_t i = 0; i < CHOICE_BOX_KEYS_COUNT && i < keys.Count(); i++) {
          const int selection = choice_boxes_keys_[i]->FindString(keys[i]);

          if (selection != wxNOT_FOUND) {
            choice_boxes_keys_[i]->SetSelection(selection);
          } else {
            wxLogWarning(_("The life key ") + _(keys[i]) +
                         _(" was not found as an option in the GUI config"));
          }
        }
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
      for (const auto& value : *mbti_array) {
        for (size_t i = 0; i < 4; i++) {
          const int selection = choice_boxes_mbti_[i]->FindString(value);
          if (selection != wxNOT_FOUND) {
            choice_boxes_mbti_[i]->SetSelection(selection);
          }
        }
      }
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

void ExternalPanel::AddMbtiTuple(std::vector<wxArrayString>* source_vector,
                                 std::string str1, std::string str2) {
  wxArrayString tuple;
  tuple.Add(str1);
  tuple.Add(str2);
  source_vector->push_back(tuple);
}

std::string ExternalPanel::GetMbti() {
  std::string mbti_string = "";

  // mbti
  std::string mbti[4];
  for (size_t i = 0; i < 4; i++) {
    const int selection = choice_boxes_mbti_[i]->GetSelection();
    if (selection != wxNOT_FOUND) {
      const std::string value =
          choice_boxes_mbti_[i]->GetString(selection).ToStdString();

      mbti[i] = value;
    } else {
      mbti[i] = "";
    }
    mbti_string += mbti[i];
  }

  return mbti_string;
}

std::vector<std::string> ExternalPanel::GetLifeKeys() {
  std::vector<std::string> result;

  // life keys
  for (size_t i = 0; i < CHOICE_BOX_KEYS_COUNT; i++) {
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

void ExternalPanel::OnMbtiChange(wxCommandEvent& event) {
  std::string mbti = GetMbti();

  if (mbti.length() == 4) {
    mbti_info_panel_->SetMbti(mbti);
  }
}

void ExternalPanel::DoLayout() {
  wxFlexGridSizer* sizer = new wxFlexGridSizer(1, 3, 0, 0);
  wxFlexGridSizer* sizer_content = new wxFlexGridSizer(2, 2, 30, 30);

  wxBoxSizer* sizer_mbti_keys = new wxBoxSizer(wxVERTICAL);
  wxStaticBoxSizer* sizer_mbti = new wxStaticBoxSizer(wxVERTICAL, this, "MBTI");
  wxBoxSizer* sizer_mbti_combo_boxes = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_career = new wxBoxSizer(wxVERTICAL);

  panel_career_ =
      new CareerTestPanel(this, wxID_ANY, "career_test", "Career Test");
  sizer_career->Add(panel_career_, 0, wxEXPAND | wxALL, 5);

  std::vector<wxArrayString> mbti_tuples;
  AddMbtiTuple(&mbti_tuples, "I", "E");
  AddMbtiTuple(&mbti_tuples, "S", "N");
  AddMbtiTuple(&mbti_tuples, "T", "F");
  AddMbtiTuple(&mbti_tuples, "J", "P");

  for (size_t i = 0; i < 4; i++) {
    choice_boxes_mbti_[i] =
        new wxChoice(sizer_mbti->GetStaticBox(), wxID_ANY, wxDefaultPosition,
                     wxSize(60, -1), mbti_tuples[i]);
    sizer_mbti_combo_boxes->Add(choice_boxes_mbti_[i], 0, 0, 0);
    sizer_mbti_combo_boxes->AddSpacer(5);
    choice_boxes_mbti_[i]->Bind(wxEVT_CHOICE, &ExternalPanel::OnMbtiChange,
                                this);
  }

  mbti_info_panel_ = new MbtiInfoPanel(sizer_mbti->GetStaticBox(), wxID_ANY);
  sizer_mbti->Add(sizer_mbti_combo_boxes, 0, wxALL, 6);
  sizer_mbti->Add(mbti_info_panel_, 0, wxALL, 6);

  wxStaticText* label_keys = new wxStaticText(this, wxID_ANY, _("Life Keys"));
  sizer_keys_->Add(label_keys, 0, wxALIGN_BOTTOM, 0);

  sizer_mbti_keys->Add(sizer_mbti, 0, wxBOTTOM, 20);
  sizer_mbti_keys->Add(sizer_keys_, 0, wxALL, 0);

  sizer_content->Add(sizer_mbti_keys, 0, wxALL, 5);
  sizer_content->Add(sizer_career, 0, wxALL, 5);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(sizer_content, 0, 0, 0);
  sizer->Add(0, 0, 0, 0);

  sizer->AddGrowableCol(0);
  sizer->AddGrowableCol(1);

  Layout();
  this->SetSizer(sizer);
}
