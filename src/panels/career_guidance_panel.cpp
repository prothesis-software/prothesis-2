#include "career_guidance_panel.hpp"

#include <memory>
#include <string>
#include <vector>

CareerGuidancePanel::CareerGuidancePanel(wxWindow* parent, wxWindowID id,
                                         std::string panel_name,
                                         std::string panel_title,
                                         const wxPoint& pos, const wxSize& size,
                                         int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

CareerGuidancePanel::~CareerGuidancePanel() {
  // void
}

void CareerGuidancePanel::OnTabActivate() {
  ExternalPanel* external_panel =
      static_cast<ExternalPanel*>(GetPanelByName("external"));
  panel_mbti_->SetMbti(external_panel->GetMbti());
}

bool CareerGuidancePanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> CareerGuidancePanel::GetUserState() {
  return NULL;
}

bool CareerGuidancePanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return true;
}

void CareerGuidancePanel::DoLayout() {
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

  panel_mbti_ = new MbtiPanel(this, wxID_ANY);

  sizer->Add(panel_mbti_, 0, 0, 0);
  this->SetSizer(sizer);
  Layout();
}
