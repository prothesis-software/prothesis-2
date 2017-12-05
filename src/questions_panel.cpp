#include "questions_panel.hpp"
#include <memory>
#include <string>
#include <vector>

QuestionsPanel::QuestionsPanel(wxWindow *parent,
                           wxWindowID id,
                           std::string panel_name,
                           std::string panel_title,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : PagedPanel(parent, id, panel_name, panel_title, pos, size, style) {
  // void
}

QuestionsPanel::~QuestionsPanel() {
  // wxLogDebug("QuestionsPanel::~QuestionsPanel()");
}

wxPanel *QuestionsPanel::CreateInternalPanel(std::string question) {
  wxLogDebug(_("Creating question panel: ") + _(question));

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  // panel->Hide();
  wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 3, 10, 0);
  wxStaticText *question_text = new wxStaticText(panel, wxID_ANY, _(question));
  wxTextCtrl *text_ctrl_answer = new wxTextCtrl(panel, wxID_ANY,
                                                wxEmptyString,
                                                wxDefaultPosition,
                                                wxDefaultSize,
                                                wxTE_MULTILINE);
  // WARN:STATIC
  text_ctrl_answer->SetMinSize(wxSize(400, 100));
  sizer->Add(0, 0, 0, 0);
  sizer->Add(question_text, 0, wxALL | wxALIGN_CENTER, 5);
  sizer->Add(0, 0, 0, 0);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(text_ctrl_answer, 1, wxALL | wxALIGN_CENTER, 5);
  sizer->Add(0, 0, 0, 0);

  sizer->AddGrowableCol(0);
  sizer->AddGrowableCol(2);
  panel->SetSizer(sizer);

  label_questions_.push_back(question_text);
  text_ctrl_answers_.push_back(text_ctrl_answer);

  panel->Layout();
  return panel;
}

bool QuestionsPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  // Parse each quesion string
  // create a panel
  // add the panel to the panel vector
  std::shared_ptr<cpptoml::table> panel_table =
    state->get_table(this->GetPanelName());

  if (panel_table) {
    std::cout << *panel_table << std::endl;

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
          wxPanel* internal_panel = CreateInternalPanel(*question_text);
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

bool QuestionsPanel::SetAnswer(std::string question, std::string answer) {
  wxTextCtrl *answer_text_ctrl = GetAnswerCtrlByQuestion(question);

  if (answer_text_ctrl != NULL) {
    answer_text_ctrl->SetValue(answer);
  } else {
    return false;
  }

  return true;
}

wxTextCtrl* QuestionsPanel::GetAnswerCtrlByQuestion(std::string question) {
  for (size_t i = 0; i < label_questions_.size(); i++) {
    std::string label_str = label_questions_.at(i)->GetLabel().ToStdString();

    if (label_str.compare(question) == 0) {
      return text_ctrl_answers_.at(i);
    }
  }

  return NULL;
}

bool QuestionsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
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
          SetAnswer(*question, *answer);
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

std::shared_ptr<cpptoml::table> QuestionsPanel::GetUserState() {
  wxLogDebug("QuestionsPanel::GetUserState()");
  std::shared_ptr<cpptoml::table> panel_data = cpptoml::make_table();

  std::shared_ptr<cpptoml::table_array> question_array =
    cpptoml::make_table_array();

  for (size_t i = 0; i < text_ctrl_answers_.size(); i++) {
    // Create a question answer pair
    std::shared_ptr<cpptoml::table> question_table =
    cpptoml::make_table();
    question_table->insert("answer",
                           text_ctrl_answers_.at(i)->GetValue().ToStdString());
    question_table->insert("question",
                           label_questions_.at(i)->GetLabel().ToStdString());
    question_array->push_back(question_table);
  }

  panel_data->insert("question", question_array);
  return panel_data;
}
