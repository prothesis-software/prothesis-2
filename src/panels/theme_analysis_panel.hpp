#ifndef PANELS_THEME_ANALYSIS_PANEL_HPP_
#define PANELS_THEME_ANALYSIS_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "src/checkbox_panel.hpp"
#include "src/coloured_button.hpp"
#include "src/coloured_button_container.hpp"
#include "src/data_panel.hpp"
#include "src/panels/external_panel.hpp"
#include "src/panels/priorities_panel.hpp"
#include "src/questions_panel.hpp"
#include "src/theme_panel.hpp"

/**
 * 1. Receives GUI state from data manager
 * 2. Constructs gui from own key
 * 3. Each ColouredButtonContainer also syncs with its source
 */
class ThemeAnalysisPanel : public DataPanel {
 public:
  ThemeAnalysisPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                     std::string panel_title,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~ThemeAnalysisPanel();

  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  std::shared_ptr<cpptoml::table> GetUserState() override;

  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

  struct CheckBoxDisplay {
    ColouredButtonContainer* container;
    CheckBoxPanel* source_panel;
  };

  struct QuestionDisplay {
    wxPanel* panel;
    wxStaticBoxSizer* sizer;
    wxTextCtrl* text_ctrl;
    QuestionsPanel* source_panel;
  };

  void OnTabActivate() override;

 private:
  void OnSizeChange(wxSizeEvent& event);              // NOLINT
  void OnPanelHover(wxMouseEvent& event);             // NOLINT
  void OnPanelHoverExit(wxMouseEvent& event);         // NOLINT
  void OnColouredButtonClick(wxCommandEvent& event);  // NOLINT
  void OnPanelColourClick(wxMouseEvent& event);       // NOLINT
  void OnThemeButtonClick(wxCommandEvent& event);     // NOLINT
  void BindButtons(ColouredButtonContainer* container);
  void UnbindButtons(ColouredButtonContainer* container);
  wxStaticBoxSizer* CreateColourSelection();
  wxBoxSizer* CreateThemePanels();
  wxPanel* CreateMbtiPanel();
  wxPanel* CreateQuestionDisplay(std::string source_panel_name,
                                 std::string panel_title);
  /**
   * Create a new checkbox display and add it to the list.
   * Does not initialize the contents.
   */
  ColouredButtonContainer* CreateCheckBoxDisplay(std::string source_panel_name,
                                                 std::string panel_name,
                                                 std::string panel_title);
  /**
   * Sync the CheckBoxDisplays with their source panels.
   * Also updates the event bindings
   */
  void RefreshCheckBoxDisplays();

  /**
   * Get all the summary answers from other panels
   * and display in the respective QuestionDisplay tuple
   */
  void RefreshQuestionDisplays();

  void DoLayout();
  std::vector<CheckBoxDisplay> checkbox_displays_;
  std::vector<QuestionDisplay> question_displays_;

  ColouredButtonContainer* life_keys_ = NULL;
  ColouredButtonContainer* priorities_ = NULL;

  /**
   * Used to keep track of all ColouredButtonContainer* objects
   */
  std::vector<ColouredButtonContainer*> c_button_containers_;

  std::vector<ThemePanel*> theme_panels_;

  /**
   * Every second index is the colour for the theme panel
   */
  std::vector<wxColour> colours_;
  wxColour active_colour_;
  int active_colour_index_ = 0;
  wxPanel* panel_colour_preview_ = NULL;
  wxStaticText* label_mbti_ = NULL;
};

#endif  // PANELS_THEME_ANALYSIS_PANEL_HPP_
