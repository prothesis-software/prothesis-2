#ifndef QUESTIONS_PANEL_HPP_
#define QUESTIONS_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "paged_panel.hpp"

#define QUESTION_WRAP_WIDTH 600
#define ANSWER_WIDTH 400
#define ANSWER_HEIGHT 100

class QuestionsPanel : public PagedPanel {
 public:
  QuestionsPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                 std::string panel_title,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~QuestionsPanel();

  /**
   * TOML Specification for Setting the GUI State
   *
   * [panel_name]
   *   [[panel_name.question]]
   *     question = "question text"
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification for Getting the User state:
   *
   * [panel_name]
   *   [[panel_name.question]]
   *     question = "question text"
   *     answer = "answer text"
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML Specification is the same as for GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * Returns the string used in the analysis panel
   */
  std::string GetAnalysisAnswer();

 private:
  /**
   * Create a panel to be pased to PagedPanel::SetPanels(...)
   * The parent will be this object.
   * The question label and answer text components will be added
   * to label_questions_ and text_ctrl_answers_
   */
  wxPanel* CreateInternalPanel(std::string question);

  wxTextCtrl* GetAnswerCtrlByQuestion(std::string question);

  /**
   * Set the answer for the corresponding question text
   */
  bool SetAnswer(std::string question, std::string answer);

  /**
   * Index i in both vectors correspond to a question-answer pair
   */
  std::vector<wxStaticText*> label_questions_;
  std::vector<wxTextCtrl*> text_ctrl_answers_;
};

#endif  // QUESTIONS_PANEL_HPP_
