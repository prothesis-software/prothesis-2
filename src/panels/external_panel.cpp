#include "external_panel.hpp"

#include <memory>
#include <string>

ExternalPanel::ExternalPanel(wxWindow *parent,
                             wxWindowID id,
                             std::string panel_name,
                             std::string panel_title,
                             const wxPoint &pos,
                             const wxSize &size,
                             int64_t style)
  : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

ExternalPanel::~ExternalPanel() {
  // void
}


bool ExternalPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> ExternalPanel::GetUserState() {
  return NULL;
}

bool ExternalPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

void ExternalPanel::DoLayout() {
  wxGridSizer *sizer = new wxGridSizer(1, 2, 0, 0);
  wxBoxSizer *sizer_mbti_keys = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizer_mbti = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizer_mbti_combo_boxes = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_keys = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizer_career = new wxBoxSizer(wxVERTICAL);
  wxPanel *panel_career = new wxPanel(this, wxID_ANY);
  panel_career->SetBackgroundColour(wxColour(255, 0, 0));
  panel_career->SetMinSize(wxSize(200, 300));
  sizer_career->Add(panel_career, 0, wxEXPAND, 0);

  wxStaticText *label_mbti = new wxStaticText(this, wxID_ANY, _("MBTI"));
  sizer_mbti->Add(label_mbti, 0, wxALIGN_BOTTOM, 0);

  wxChoice *choice_boxes_mbti[4];
  for (size_t i = 0; i < 4; i++) {
    choice_boxes_mbti[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                                  wxSize(60, -1));
    sizer_mbti_combo_boxes->Add(choice_boxes_mbti[i], 0, 0, 0);
    sizer_mbti_combo_boxes->AddSpacer(5);
  }
  sizer_mbti->Add(sizer_mbti_combo_boxes, 0, 0, 0);

  wxStaticText *label_keys = new wxStaticText(this, wxID_ANY, _("Life Keys"));
  sizer_keys->Add(label_keys, 0, wxALIGN_BOTTOM, 0);

  wxChoice *choice_boxes_keys[3];
  for (size_t i = 0; i < 4; i++) {
    choice_boxes_keys[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                                  wxSize(-1, -1));
    sizer_keys->Add(choice_boxes_keys[i], 0, 0, 0);
    sizer_keys->AddSpacer(5);
  }

  sizer_mbti_keys->Add(sizer_mbti, 0, wxBOTTOM, 20);
  sizer_mbti_keys->Add(sizer_keys, 0, 0, 0);

  sizer->Add(sizer_mbti_keys, 0, 0, 0);
  sizer->Add(sizer_career, 0, 0, 0);

  this->SetSizer(sizer);
}
