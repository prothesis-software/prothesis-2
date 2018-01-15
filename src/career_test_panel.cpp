#include "career_test_panel.hpp"

#include <memory>
#include <string>
#include <vector>

CareerTestPanel::CareerTestPanel(wxWindow* parent, wxWindowID id,
                                 std::string panel_name,
                                 std::string panel_title, const wxPoint& pos,
                                 const wxSize& size, int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

CareerTestPanel::~CareerTestPanel() {
  // void
}

bool CareerTestPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

bool CareerTestPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  if (panel_table) {
    for (size_t i = 0; i < 4; i++) {
      auto str =
          panel_table->get_as<std::string>("interest_" + std::to_string(i + 1));
      auto perc = panel_table->get_as<int>("interest_" + std::to_string(i + 1) +
                                           "_percentage");

      if (str) {
        text_interests_.at(i)->SetValue(*str);
      }
      if (perc) {
        spin_ctrl_percentages_.at(i)->SetValue(*perc);
      }
    }
  } else {
    return false;
  }

  return true;
}

std::shared_ptr<cpptoml::table> CareerTestPanel::GetUserState() {
  auto panel_table = cpptoml::make_table();

  for (size_t i = 0; i < 4; i++) {
    panel_table->insert("interest_" + std::to_string(i + 1),
                        text_interests_.at(i)->GetValue().ToStdString());

    panel_table->insert("interest_" + std::to_string(i + 1) + "_percentage",
                        spin_ctrl_percentages_.at(i)->GetValue());
  }

  return panel_table;
}

void CareerTestPanel::DoLayout() {
  wxStaticBoxSizer* sizer =
      new wxStaticBoxSizer(wxVERTICAL, this, this->GetPanelTitle());
  wxFlexGridSizer* sizer_content = new wxFlexGridSizer(5, 2, 0, 0);

  wxStaticText* label_interest =
      new wxStaticText(sizer->GetStaticBox(), wxID_ANY, "Interest");
  wxStaticText* label_perc =
      new wxStaticText(sizer->GetStaticBox(), wxID_ANY, "%");

  sizer_content->Add(label_interest, 0, wxALIGN_CENTER, 0);
  sizer_content->Add(label_perc, 0, wxALIGN_CENTER, 0);

  for (size_t i = 0; i < 4; i++) {
    wxTextCtrl* text_interest = new wxTextCtrl(sizer->GetStaticBox(), wxID_ANY);
    wxSpinCtrl* spin_ctrl = new wxSpinCtrl(sizer->GetStaticBox(), wxID_ANY);

    text_interest->SetMinSize(wxSize(200, -1));
    spin_ctrl->SetMinSize(wxSize(75, -1));

    sizer_content->Add(text_interest, 1, wxALL, 5);
    sizer_content->Add(spin_ctrl, 0, wxALL, 5);

    text_interests_.push_back(text_interest);
    spin_ctrl_percentages_.push_back(spin_ctrl);
  }

  sizer->Add(sizer_content);
  this->SetSizer(sizer);
  Layout();
}
