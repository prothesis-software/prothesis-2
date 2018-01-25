#include "theme_analysis_panel.hpp"

#include <memory>
#include <string>
#include <vector>

ThemeAnalysisPanel::ThemeAnalysisPanel(wxWindow* parent, wxWindowID id,
                                       std::string panel_name,
                                       std::string panel_title,
                                       const wxPoint& pos, const wxSize& size,
                                       int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  // Red
  colours_.push_back(wxColour(255, 0, 0));
  colours_.push_back(wxColour(255, 160, 165));

  // Green
  colours_.push_back(wxColour(0, 102, 0));
  colours_.push_back(wxColour(150, 255, 169));

  // Blue
  colours_.push_back(wxColour(0, 0, 255));
  colours_.push_back(wxColour(147, 206, 255));

  // Purple
  colours_.push_back(wxColour(153, 0, 153));
  colours_.push_back(wxColour(206, 150, 255));

  DoLayout();

  // this->FitInside();
  this->Fit();
  // this->SetScrollRate(10, 10);
  this->Bind(wxEVT_SIZE, &ThemeAnalysisPanel::OnSizeChange, this);
}

ThemeAnalysisPanel::~ThemeAnalysisPanel() {
  // void
}

void ThemeAnalysisPanel::OnSizeChange(wxSizeEvent& event) {
  wxLogDebug("Size");
  this->FitInside();
  this->SetScrollRate(10, 10);
  Layout();
}

bool ThemeAnalysisPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  panel_mbti_info_->SetMbtiInfoData(state);
  return true;
}

std::shared_ptr<cpptoml::table> ThemeAnalysisPanel::GetUserState() {
  auto panel_table = cpptoml::make_table();

  for (size_t i = 0; i < c_button_containers_.size(); i++) {
    auto c_button_table = c_button_containers_.at(i)->GetUserState();
    panel_table->insert(c_button_containers_.at(i)->GetPanelName(),
                        c_button_table);
  }

  for (size_t i = 0; i < theme_panels_.size(); i++) {
    panel_table->insert(theme_panels_.at(i)->GetPanelName(),
                        theme_panels_.at(i)->GetUserState());
  }

  return panel_table;
}

bool ThemeAnalysisPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  if (panel_table) {
    for (size_t i = 0; i < c_button_containers_.size(); i++) {
      c_button_containers_.at(i)->SetUserState(panel_table);
    }

    for (size_t i = 0; i < theme_panels_.size(); i++) {
      theme_panels_.at(i)->SetUserState(panel_table);
    }
  }

  return true;
}

void ThemeAnalysisPanel::OnPanelHover(wxMouseEvent& event) {
  wxPanel* panel = static_cast<wxPanel*>(event.GetEventObject());
  panel->SetBackgroundColour(wxColour(255, 0, 0));
  Refresh();
}

void ThemeAnalysisPanel::OnPanelHoverExit(wxMouseEvent& event) {
  wxPanel* panel = static_cast<wxPanel*>(event.GetEventObject());
  panel->SetBackgroundColour(wxColour(0, 0, 255));
  Refresh();
}

void ThemeAnalysisPanel::OnColouredButtonClick(wxCommandEvent& event) {
  wxButton* btn = static_cast<wxButton*>(event.GetEventObject());
  ColouredButton* panel = static_cast<ColouredButton*>(btn->GetParent());

  panel->SetColour(active_colour_);
  Refresh();
}

ColouredButtonContainer* ThemeAnalysisPanel::CreateCheckBoxDisplay(
    std::string source_panel_name, std::string panel_name,
    std::string panel_title) {
  ColouredButtonContainer* container =
      new ColouredButtonContainer(this, wxID_ANY, panel_name, panel_title);
  CheckBoxPanel* source_panel =
      static_cast<CheckBoxPanel*>(GetPanelByName(source_panel_name));

  CheckBoxDisplay tuple;
  tuple.container = container;
  tuple.source_panel = source_panel;

  checkbox_displays_.push_back(tuple);
  c_button_containers_.push_back(container);

  return container;
}

void ThemeAnalysisPanel::UnbindButtons(ColouredButtonContainer* container) {
  std::vector<ColouredButton*> btns = container->GetColouredButtons();
  for (size_t i = 0; i < btns.size(); i++) {
    btns.at(i)->Unbind(wxEVT_BUTTON, &ThemeAnalysisPanel::OnColouredButtonClick,
                       this);
  }
}

void ThemeAnalysisPanel::BindButtons(ColouredButtonContainer* container) {
  std::vector<ColouredButton*> btns_new = container->GetColouredButtons();
  for (size_t i = 0; i < btns_new.size(); i++) {
    btns_new.at(i)->Bind(wxEVT_BUTTON,
                         &ThemeAnalysisPanel::OnColouredButtonClick, this);
  }
}

void ThemeAnalysisPanel::OnTabActivate() {
  wxLogDebug("Refreshing theme panel");
  RefreshCheckBoxDisplays();
  RefreshQuestionDisplays();

  ExternalPanel* external_panel =
      static_cast<ExternalPanel*>(GetPanelByName("external"));
  PrioritiesPanel* priorities_panel =
      static_cast<PrioritiesPanel*>(GetPanelByName("priorities"));

  std::vector<std::string> items = external_panel->GetLifeKeys();
  std::vector<std::string> items_priorities = priorities_panel->GetPriorities();

  UnbindButtons(life_keys_);
  UnbindButtons(priorities_);

  life_keys_->UpdateItems(items);
  priorities_->UpdateItems(items_priorities);

  BindButtons(life_keys_);
  BindButtons(priorities_);

  std::string mbti = external_panel->GetMbti();
  panel_mbti_info_->SetMbti(mbti);

  Layout();
  this->FitInside();
  this->SetMinSize(this->GetBestSize());
}

void ThemeAnalysisPanel::RefreshQuestionDisplays() {
  for (size_t i = 0; i < question_displays_.size(); i++) {
    std::string answer =
        question_displays_.at(i).source_panel->GetAnalysisAnswer();
    question_displays_.at(i).text_ctrl->SetValue(answer);
  }
}

wxPanel* ThemeAnalysisPanel::CreateQuestionDisplay(
    std::string source_panel_name, std::string panel_title) {
  wxPanel* panel = new wxPanel(this, wxID_ANY);
  wxStaticBoxSizer* sizer =
      new wxStaticBoxSizer(wxVERTICAL, panel, panel_title);
  wxTextCtrl* text_ctrl = new wxTextCtrl(
      sizer->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition,
      wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
  text_ctrl->SetMinSize(wxSize(400, 100));
  QuestionsPanel* source_panel =
      static_cast<QuestionsPanel*>(GetPanelByName(source_panel_name));
  sizer->Add(text_ctrl, 0, 0, 0);
  panel->SetSizer(sizer);

  QuestionDisplay tuple;
  tuple.panel = panel;
  tuple.sizer = sizer;
  tuple.text_ctrl = text_ctrl;
  tuple.source_panel = source_panel;

  question_displays_.push_back(tuple);

  return panel;
}

void ThemeAnalysisPanel::RefreshCheckBoxDisplays() {
  wxLogDebug("Refreshing CheckBoxDisplays");

  for (size_t i = 0; i < checkbox_displays_.size(); i++) {
    std::vector<std::string> items =
        checkbox_displays_.at(i).source_panel->GetCheckedItems();

    // Unlink events
    std::vector<ColouredButton*> btns =
        checkbox_displays_.at(i).container->GetColouredButtons();
    for (size_t j = 0; j < btns.size(); j++) {
      btns.at(j)->Unbind(wxEVT_BUTTON,
                         &ThemeAnalysisPanel::OnColouredButtonClick, this);
    }
    checkbox_displays_.at(i).container->UpdateItems(items);

    // Link events
    std::vector<ColouredButton*> btns_new =
        checkbox_displays_.at(i).container->GetColouredButtons();
    for (size_t j = 0; j < btns_new.size(); j++) {
      btns_new.at(j)->Bind(wxEVT_BUTTON,
                           &ThemeAnalysisPanel::OnColouredButtonClick, this);
    }
  }

  Layout();
}

void ThemeAnalysisPanel::OnPanelColourClick(wxMouseEvent& event) {
  wxLogDebug("OnPanelColourClick()");
  wxPanel* panel = static_cast<wxPanel*>(event.GetEventObject());
  active_colour_ = panel->GetBackgroundColour();

  for (size_t i = 0; i < colours_.size(); i += 2) {
    if (colours_.at(i) == active_colour_) {
      active_colour_index_ = i;
    }
  }

  panel_colour_preview_->SetBackgroundColour(active_colour_);
  Refresh();
}

wxStaticBoxSizer* ThemeAnalysisPanel::CreateColourSelection() {
  wxStaticBoxSizer* sizer_colours =
      new wxStaticBoxSizer(wxHORIZONTAL, this, "Colours");
  for (size_t i = 0; i < colours_.size(); i += 2) {
    wxPanel* panel_colour =
        new wxPanel(sizer_colours->GetStaticBox(), wxID_ANY);
    panel_colour->SetBackgroundColour(colours_.at(i));
    panel_colour->SetMinSize(wxSize(50, 25));
    panel_colour->Bind(wxEVT_LEFT_UP, &ThemeAnalysisPanel::OnPanelColourClick,
                       this);
    sizer_colours->Add(panel_colour, 0, wxRIGHT | wxALL, 5);
  }

  wxStaticText* label_preview =
      new wxStaticText(sizer_colours->GetStaticBox(), wxID_ANY, "Active: ");

  sizer_colours->Add(label_preview, 0, wxALIGN_CENTER | wxRIGHT, 5);

  panel_colour_preview_ = new wxPanel(sizer_colours->GetStaticBox(), wxID_ANY);
  panel_colour_preview_->SetMinSize(wxSize(50, 25));

  sizer_colours->Add(panel_colour_preview_, 0, wxALIGN_CENTER, 0);
  return sizer_colours;
}

void ThemeAnalysisPanel::OnThemeButtonClick(wxCommandEvent& event) {
  // WARN: Assumes the structure of the ThemPanel
  // Need a Colour class hierachy
  ColouredButton* button = static_cast<ColouredButton*>(event.GetEventObject());
  wxStaticBox* box = static_cast<wxStaticBox*>(button->GetParent());
  ThemePanel* panel = static_cast<ThemePanel*>(box->GetParent());

  panel->SetColour(colours_.at(active_colour_index_ + 1));
  Refresh();
}

wxBoxSizer* ThemeAnalysisPanel::CreateThemePanels() {
  wxBoxSizer* sizer_themes = new wxBoxSizer(wxVERTICAL);

  for (size_t i = 0; i < 4; i++) {
    std::string i_str = std::to_string(i + 1);
    std::string panel_name = std::string("theme_") + i_str;
    std::string panel_title = std::string("Theme ") + i_str;

    ThemePanel* theme_panel =
        new ThemePanel(this, wxID_ANY, panel_name, panel_title);
    theme_panel->GetButton()->Bind(
        wxEVT_BUTTON, &ThemeAnalysisPanel::OnThemeButtonClick, this);
    theme_panels_.push_back(theme_panel);
    sizer_themes->Add(theme_panel, 0, 0, 0);
    sizer_themes->AddSpacer(10);
  }

  return sizer_themes;
}

void ThemeAnalysisPanel::DoLayout() {
  wxFlexGridSizer* sizer_main = new wxFlexGridSizer(1, 5, 0, 0);
  wxBoxSizer* sizer_left = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* sizer_mbti_colour = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_boxes = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_boxes_left = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* sizer_boxes_right = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizer_middle = new wxBoxSizer(wxVERTICAL);

  ColouredButtonContainer* skills =
      CreateCheckBoxDisplay("skills", "theme_analysis_skills", "Skills");
  ColouredButtonContainer* roles =
      CreateCheckBoxDisplay("roles", "theme_analysis_roles", "Roles");
  ColouredButtonContainer* people_orientation = CreateCheckBoxDisplay(
      "people_orientation", "theme_analysis_people_orientation",
      "People Orientation");
  wxPanel* panel_passion = CreateQuestionDisplay("passion", "Passion");
  wxPanel* panel_people_id = CreateQuestionDisplay("people_id", "People ID");
  wxPanel* panel_dreams = CreateQuestionDisplay("dreams", "Dreams");
  wxPanel* panel_values = CreateQuestionDisplay("values", "Values");
  wxPanel* panel_spoken_words =
      CreateQuestionDisplay("spoken_words", "Spoken Words");
  life_keys_ = new ColouredButtonContainer(
      this, wxID_ANY, "theme_analysis_life_keys", "Life Keys");

  priorities_ = new ColouredButtonContainer(
      this, wxID_ANY, "theme_analysis_priorities", "Priorities");
  c_button_containers_.push_back(life_keys_);
  c_button_containers_.push_back(priorities_);

  wxBoxSizer* sizer_themes = CreateThemePanels();

  wxStaticBoxSizer* sizer_colours = CreateColourSelection();
  panel_mbti_info_ = new MbtiInfoPanel(this, wxID_ANY);
  panel_mbti_info_->HideMbtiSelection();

  const int flags = wxALL;
  const int border = 5;

  // sizer_mbti_colour
  sizer_mbti_colour->Add(panel_mbti_info_, 0, flags, border);
  sizer_mbti_colour->Add(sizer_colours, 0, flags, border);

  // sizer_boxes_left
  sizer_boxes_left->Add(roles, 0, flags, border);
  sizer_boxes_left->Add(priorities_, 0, flags, border);

  // sizer_boxes_right
  sizer_boxes_right->Add(skills, 0, flags, border);
  sizer_boxes_right->Add(life_keys_, 0, flags, border);
  sizer_boxes_right->Add(people_orientation, 0, flags, border);

  // sizer_boxes
  sizer_boxes->Add(sizer_boxes_left, 0, flags, border);
  sizer_boxes->Add(sizer_boxes_right, 0, flags, border);

  // sizer_left
  sizer_left->Add(sizer_mbti_colour, 0, flags, border);
  sizer_left->Add(sizer_boxes, 0, flags, border);

  // sizer_middle
  sizer_middle->Add(panel_people_id, 0, flags, border);
  sizer_middle->Add(panel_dreams, 0, flags, border);
  sizer_middle->Add(panel_spoken_words, 0, flags, border);
  sizer_middle->Add(panel_values, 0, flags, border);
  sizer_middle->Add(panel_passion, 0, flags, border);

  // sizer_main
  sizer_main->Add(0, 0, 0, 0);
  sizer_main->Add(sizer_left, 0, flags, border);
  sizer_main->Add(sizer_middle, 0, flags, border);
  sizer_main->Add(sizer_themes, 0, flags, border);

  this->SetSizer(sizer_main);
  sizer_main->Fit(this);
  Layout();
}
