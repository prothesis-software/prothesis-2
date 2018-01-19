#include "checkbox_panel.hpp"
#include <memory>
#include <string>
#include <vector>

CheckBoxPanel::CheckBoxPanel(wxWindow* parent, wxWindowID id,
                             std::string panel_name, std::string panel_title,
                             const wxPoint& pos, const wxSize& size,
                             int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  label_limit_ = new wxStaticText(this, wxID_ANY, "");
  label_limit_->SetForegroundColour(wxColour(255, 0, 0));
  // label_limit_->Hide();

  DoLayout();
  this->Bind(wxEVT_CHECKLISTBOX, &CheckBoxPanel::OnCheckBoxChange, this);
}

CheckBoxPanel::~CheckBoxPanel() {
  wxLogDebug(_("CheckBoxPanel::~CheckBoxPanel(): ") + _(this->GetPanelName()));
}

bool CheckBoxPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  // Parse each quesion string
  // create a panel
  // add the panel to the panel vector
  std::shared_ptr<cpptoml::table> panel_table =
      state->get_table(this->GetPanelName());

  if (panel_table) {
    // We can get the array named questions since we already
    // extracted the panel table.
    // ie the '[[panel_name.questions]]' becomes '[[questions]]'
    std::shared_ptr<cpptoml::table_array> questions =
        panel_table->get_table_array("question");
    if (questions) {
      for (const std::shared_ptr<cpptoml::table>& table : *questions) {
        // Get the question text from the table we extracted
        cpptoml::option<std::string> question_text =
            table->get_as<std::string>("question");

        if (question_text) {
          wxLogDebug(_(this->GetPanelName()) + _(": Adding checkbox '") +
                     _(*question_text) + _("'"));
          AddCheckBox(*question_text);
        } else {
          wxLogError(_("A question table was found for panel ") +
                     _(this->GetPanelName()) +
                     _(" but the key 'question' was not found"));
        }
      }
    } else {
      wxLogDebug(_("No questions found for panel ") + _(GetPanelName()));
    }
  } else {
    wxLogDebug(_("No GUI table exists for panel ") + _(this->GetPanelName()));
    return false;
  }

  return true;
}

bool CheckBoxPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  std::shared_ptr<cpptoml::table> panel_table =
      state->get_table(GetPanelName());

  if (panel_table != NULL && !panel_table->empty()) {
    std::shared_ptr<cpptoml::table_array> question_array =
        panel_table->get_table_array("question");

    for (const auto& question_table : *question_array) {
      auto question = question_table->get_as<std::string>("question");
      auto answer = question_table->get_as<std::string>("answer");

      if (answer) {
        if (question) {
          if (*answer == "true") {
            SetCheckboxStateByLabel(*question, true);
          } else {
            SetCheckboxStateByLabel(*question, false);
          }
        }
      }
    }
  } else {
    wxLogDebug(_("No User table exists for Question Panel:") +
               _(GetPanelName()));
    return false;
  }

  return true;
}

std::shared_ptr<cpptoml::table> CheckBoxPanel::GetUserState() {
  wxLogDebug("CheckBoxPanel::GetUserState()");
  std::shared_ptr<cpptoml::table> panel_data = cpptoml::make_table();

  std::shared_ptr<cpptoml::table_array> question_array =
      cpptoml::make_table_array();

  for (size_t i = 0; i < 3; i++) {
    wxCheckListBox* box = boxes_[i];
    for (size_t i = 0; i < box->GetCount(); i++) {
      // Create a question answer pair
      std::shared_ptr<cpptoml::table> question_table = cpptoml::make_table();
      if (box->IsChecked(i))
        question_table->insert("answer", "true");
      else
        question_table->insert("answer", "false");

      question_table->insert("question", std::string(box->GetString(i)));
      question_array->push_back(question_table);
    }
  }

  panel_data->insert("question", question_array);
  return panel_data;
}

std::vector<std::string> CheckBoxPanel::GetCheckedItems() {
  std::vector<std::string> result;

  for (size_t i = 0; i < 3; i++) {
    wxCheckListBox* box = boxes_[i];
    for (size_t j = 0; j < box->GetCount(); j++) {
      if (box->IsChecked(j)) {
        result.push_back(box->GetString(j).ToStdString());
      }
    }
  }

  return result;
}

void CheckBoxPanel::OnCheckBoxListSelectionChange(wxCommandEvent& event) {
  wxCheckListBox* list_box =
      static_cast<wxCheckListBox*>(event.GetEventObject());

  for (size_t i = 0; i < 3; i++) {
    if (boxes_[i] != list_box) {
      boxes_[i]->SetSelection(wxNOT_FOUND);
    }
  }
}

void CheckBoxPanel::OnCheckBoxChange(wxCommandEvent& event) {
  int index = event.GetInt();
  wxCheckListBox* check_list_box =
      static_cast<wxCheckListBox*>(event.GetEventObject());
  bool checked = check_list_box->IsChecked(index);

  if (checked_item_count_ >= MAX_CHECKED_ITEMS && checked == true) {
    check_list_box->Check(index, false);
  } else {
    if (checked) {
      checked_item_count_++;
    } else {
      checked_item_count_--;
    }

    if (checked_item_count_ >= MAX_CHECKED_ITEMS) {
      label_limit_->SetLabel("Limit of 7 has been reached");
    } else {
      label_limit_->SetLabel("");
    }
  }

  Layout();
}

void CheckBoxPanel::SetCheckboxStateByLabel(std::string label, bool checked) {
  for (size_t i = 0; i < 3; i++) {
    int pos = boxes_[i]->FindString(label);
    if (pos != -1) {
      boxes_[i]->Check(pos, checked);
      if (checked) {
        checked_item_count_++;
        if (checked_item_count_ >= MAX_CHECKED_ITEMS) {
          label_limit_->SetLabel("Limit of 7 has been reached");
        } else {
          label_limit_->SetLabel("");
        }
      }
      return;
    }
  }
}

void CheckBoxPanel::AddCheckBox(std::string label) {
  wxCheckListBox* box = this->list_box_a_;
  if (box->GetCount() >= MAX_ITEMS) {
    box = this->list_box_b_;
    if (box->GetCount() >= MAX_ITEMS) {
      box = this->list_box_c_;
    }
  }

  box->InsertItems(1, new wxString(label), 0);
}

void CheckBoxPanel::DoLayout() {
  wxBoxSizer* sizer_root = new wxBoxSizer(wxVERTICAL);

  wxGridSizer* sizer = new wxGridSizer(0, 3, 0, 0);
  this->list_box_a_ = new wxCheckListBox(this, wxID_ANY);
  this->list_box_b_ = new wxCheckListBox(this, wxID_ANY);
  this->list_box_c_ = new wxCheckListBox(this, wxID_ANY);

  boxes_[0] = list_box_a_;
  boxes_[1] = list_box_b_;
  boxes_[2] = list_box_c_;

  for (size_t i = 0; i < 3; i++) {
    sizer->Add(boxes_[i], 1, wxEXPAND | wxALIGN_LEFT, 0);
    boxes_[i]->Bind(wxEVT_LISTBOX,
                    &CheckBoxPanel::OnCheckBoxListSelectionChange, this);
  }

  sizer_root->Add(label_limit_, 0, wxALIGN_CENTER | wxALL, 6);
  sizer_root->Add(sizer, 0, wxALIGN_CENTER);

  this->SetSizer(sizer_root);
  Layout();
}
