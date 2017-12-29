#include "checkbox_panel.hpp"
#include <memory>
#include <string>
#include <vector>

CheckBoxPanel::CheckBoxPanel(wxWindow* parent,
                             wxWindowID id,
                             std::string panel_name,
                             std::string panel_title,
                             const wxPoint& pos,
                             const wxSize& size,
                             int64_t style)
                             : DataPanel(parent, id, panel_name,
                               panel_title, pos, size, style) {
  DoLayout();
}

CheckBoxPanel::~CheckBoxPanel() {
  // void
}

bool CheckBoxPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  // void
  return false;
}

bool CheckBoxPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  // void
  return false;
}

void CheckBoxPanel::SetProperties() {
  // void
}

void CheckBoxPanel::DoLayout() {
  wxGridSizer *sizer = new wxGridSizer(0, 1, 0, 0);
  wxCheckListBox *list = new wxCheckListBox(this, wxID_ANY);

  wxString *label = new wxString("KEK");
  list->InsertItems(1, label, 0);
  sizer->Add(list, 1, wxEXPAND, 0, 0);

  this->SetSizer(sizer);
  Layout();
}

void CheckBoxPanel::SetCheckboxStateByLabel(std::string label, bool checked) {
  // void
}

void CheckBoxPanel::AddCheckBox(std::string label) {
  // void
}

  std::shared_ptr<cpptoml::table> CheckBoxPanel::GetUserState() {
    return NULL;
  }
