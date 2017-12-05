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
  // void
}

wxPanel *QuestionsPanel::CreateInternalPanel(std::string question) {
  wxLogDebug(_("Creating question panel: ") + _(question));

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  // panel->Hide();
  wxFlexGridSizer *sizer = new wxFlexGridSizer(2, 3, 10, 0);
  wxStaticText *question_text = new wxStaticText(panel, wxID_ANY, _(question));
  wxTextCtrl *text_ctrl_answer = new wxTextCtrl(panel, wxID_ANY, wxEmptyString);
  // wxTextCtrl->wxTextCtrl
  text_ctrl_answer->SetMinSize(wxSize(300, 150));
  sizer->Add(0, 0, 0, 0);
  sizer->Add(question_text, 0, wxTOP | wxALIGN_CENTER, 5);
  sizer->Add(0, 0, 0, 0);

  sizer->Add(0, 0, 0, 0);
  sizer->Add(text_ctrl_answer, 1, wxBOTTOM | wxALIGN_CENTER, 0);
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
    wxLogDebug(_("No table exists for panel ") + _(this->GetPanelName()));
    return false;
  }

  Init();
  return true;
}

bool QuestionsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> QuestionsPanel::GetUserState() {
  return NULL;
}
