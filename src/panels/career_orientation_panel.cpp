#include "career_orientation_panel.hpp"

#include <memory>
#include <string>
#include <vector>

CareerOrientationPanel::CareerOrientationPanel(wxWindow *parent, wxWindowID id,
                                               std::string panel_name,
                                               std::string panel_title,
                                               const wxPoint &pos,
                                               const wxSize &size,
                                               int64_t style)
    : PagedPanel(parent, id, panel_name, panel_title, pos, size, style) {
  wxLogDebug(_("Creating CareerOrientationPanel: ") + _(GetPanelName()));
}

#define QUESTION_WRAP_WIDTH 600
#define ANSWER_WIDTH 400  // DELETE ME
#define ANSWER_HEIGHT 100
wxPanel *CareerOrientationPanel::CreateInternalPanel(
    std::string question, std::vector<std::string> options) {
  wxPanel *panel = new wxPanel();
  this->titles.push_back(question);

  panel->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
  panel->Create(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

  wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 3, 10, 0);
  wxStaticText *question_text = new wxStaticText(panel, wxID_ANY, _(question));
  wxCheckListBox *box = AddCheckboxes(panel, options);
  question_text->Wrap(QUESTION_WRAP_WIDTH);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(question_text, 0, wxALL | wxALIGN_CENTER, 5);
  sizer->Add(0, 0, 0, 0);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(box, 0, wxALL | wxALIGN_CENTER, 5);
  sizer->Add(0, 0, 0, 0);

  sizer->AddGrowableCol(0);
  sizer->AddGrowableCol(2);
  panel->SetSizer(sizer);

  panel->Layout();
  return panel;
}

bool CareerOrientationPanel::SetGuiState(
    std::shared_ptr<cpptoml::table> state) {
  // Parse each quesion string
  // create a panel
  // add the panel to the panel vector
  std::shared_ptr<cpptoml::table> panel_table =
      state->get_table("career_orientation");

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
            table->get_as<std::string>("title");

        auto options = table->get_array_of<std::string>("options");
        // for (const auto& val : *vals)
        if (question_text && options) {
          wxPanel *internal_panel =
              CreateInternalPanel(*question_text, *options);
          AddPage(internal_panel);
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

  Init();
  return true;
}

bool CareerOrientationPanel::SetUserState(
    std::shared_ptr<cpptoml::table> state) {
  std::shared_ptr<cpptoml::table> panel_table =
      state->get_table(GetPanelName());

  if (panel_table != NULL && !panel_table->empty()) {
    std::shared_ptr<cpptoml::table_array> question_array =
        panel_table->get_table_array("question");
    for (const auto &question_table : *question_array) {
      auto question = question_table->get_as<std::string>("title");
      auto options = question_table->get_array_of<std::string>("options");
      if (options) {
        if (question) {
          SetAnswer(*question, *options);
        }
      }
    }
  } else {
    wxLogDebug(_("No User table exists for Career Orientation Panel:") +
               _(GetPanelName()));
    return false;
  }

  return true;
}

bool CareerOrientationPanel::SetAnswer(std::string question,
                                       std::vector<std::string> options) {
  size_t i = 0;
  for (std::string title : titles) {
    if (title == question) {
      for (std::string option : options)
        for (size_t j = 0; j < checkboxes[i]->GetCount(); j++) {
          if (option == checkboxes[i]->GetString(j).ToStdString())
            checkboxes[i]->Check(j);
        }
    }

    i++;
  }
  return true;
}

std::shared_ptr<cpptoml::table> CareerOrientationPanel::GetUserState() {
  wxLogDebug("CareerOrientationPanel::GetUserState()");
  // A; Create a table for the panel.
  std::shared_ptr<cpptoml::table> panel_data = cpptoml::make_table();

  // B; Create a table array containing questions & answer pairs.
  std::shared_ptr<cpptoml::table_array> questions_array =
      cpptoml::make_table_array();

  // C; Insert each question/answer pair into questions_array
  for (size_t i = 0; i < titles.size(); i++) {
    std::shared_ptr<cpptoml::table> table = cpptoml::make_table();
    table->insert("title", titles[i]);
    // C2; Insert all the options.
    wxCheckListBox *box = checkboxes[i];
    auto options_array = cpptoml::make_array();
    for (size_t j = 0; j < box->GetCount(); j++) {
      if (box->IsChecked(j))
        options_array->push_back(box->GetString(j).ToStdString());
    }
    table->insert("options", options_array);
    questions_array->push_back(table);
  }
  // D; Insert table_array back into panel_data
  panel_data->insert("question", questions_array);
  return panel_data;
}

wxCheckListBox *CareerOrientationPanel::AddCheckboxes(
    wxPanel *panel, std::vector<std::string> titles) {
  wxCheckListBox *box = new wxCheckListBox(panel, wxID_ANY);
  checkboxes.push_back(box);
  for (std::string x : titles) {
    box->InsertItems(1, new wxString(x), 0);
  }

  return box;
}
