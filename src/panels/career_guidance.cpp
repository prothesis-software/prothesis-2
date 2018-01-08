#include "career_guidance.hpp"

#include <memory>
#include <string>

CareerGuidancePanel::CareerGuidancePanel(wxWindow *parent, wxWindowID id,
                                         std::string panel_name,
                                         std::string panel_title,
                                         const wxPoint &pos, const wxSize &size,
                                         int64_t style)
    : PagedPanel(parent, id, panel_name, panel_title, pos, size, style) {}

wxPanel *CareerGuidancePanel::CreateInternalPanel(std::string question) {
  return NULL;
}

bool CareerGuidancePanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return true;
}

bool CareerGuidancePanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return true;
}

std::shared_ptr<cpptoml::table> CareerGuidancePanel::GetUserState() {
  return NULL;
}
