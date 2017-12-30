#include "checkbox_panel.hpp"
#include <memory>
#include <string>
#include <vector>

CheckBoxPanel::CheckBoxPanel(wxWindow *parent, wxWindowID id,
                             std::string panel_name, std::string panel_title,
                             const wxPoint &pos, const wxSize &size,
                             int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

CheckBoxPanel::~CheckBoxPanel() {
  // void
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
      for (const std::shared_ptr<cpptoml::table> &table : *questions) {
        // Get the question text from the table we extracted
        cpptoml::option<std::string> question_text =
            table->get_as<std::string>("question");

        if (question_text) {
          // void
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

    for (const auto &question_table : *question_array) {
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

  wxCheckListBox *boxes[3];
  boxes[0] = listBoxA;
  boxes[1] = listBoxB;
  boxes[2] = listBoxC;

  for (size_t i = 0; i < 3; i++) {
    wxCheckListBox *box = boxes[i];
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

void CheckBoxPanel::DoLayout() {
  wxGridSizer *sizer = new wxGridSizer(0, 3, 0, 0);
  this->listBoxA = new wxCheckListBox(this, wxID_ANY);
  this->listBoxB = new wxCheckListBox(this, wxID_ANY);
  this->listBoxC = new wxCheckListBox(this, wxID_ANY);

  sizer->Add(listBoxA, 1, wxEXPAND | wxALIGN_LEFT, 0, 0);
  sizer->Add(listBoxB, 1, wxEXPAND | wxALIGN_CENTER, 0, 0);
  sizer->Add(listBoxC, 1, wxEXPAND | wxALIGN_RIGHT, 0, 0);

  this->SetSizer(sizer);
  Layout();
}

void CheckBoxPanel::SetCheckboxStateByLabel(std::string label, bool checked) {
  wxCheckListBox *box = this->listBoxA;
  int pos = box->FindString(label);
  if (pos != -1) {
    box->Check(pos, checked);
    return;
  }

  box = this->listBoxB;
  pos = box->FindString(label);
  if (pos != -1) {
    box->Check(pos, checked);
    return;
  }

  box = this->listBoxC;
  pos = box->FindString(label);
  if (pos != -1) {
    box->Check(pos, checked);
    return;
  }
  // What is looooveeeee! Baby don't huuurt meee
}

void CheckBoxPanel::AddCheckBox(std::string label) {
  wxCheckListBox *box = this->listBoxA;
  if (box->GetCount() >= MAX_ITEMS) {
    box = this->listBoxB;
    if (box->GetCount() >= MAX_ITEMS) {
      box = this->listBoxC;
    }
  }

  box->InsertItems(1, new wxString(label), 0);
}
