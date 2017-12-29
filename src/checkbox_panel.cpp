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
  wxGridSizer *sizer = new wxGridSizer(0, 3, 0, 0);
  this->listBoxA = new wxCheckListBox(this, wxID_ANY);
  this->listBoxB = new wxCheckListBox(this, wxID_ANY);
  this->listBoxC = new wxCheckListBox(this, wxID_ANY);

  sizer->Add(listBoxA, 1, wxEXPAND | wxALIGN_LEFT, 0, 0);
  sizer->Add(listBoxB, 1, wxEXPAND | wxALIGN_CENTER, 0, 0);
  sizer->Add(listBoxC, 1, wxEXPAND | wxALIGN_RIGHT, 0, 0);

  this->SetSizer(sizer);
  Layout();
}

void CheckBoxPanel::SetCheckboxStateByLabel(std::string label, bool checked) {
  wxCheckListBox *box = this->listBoxA;
  int pos = box->FindString(label);
  if (pos != -1) {
    box->Check(pos, checked);
    return;
  }

  box = this->listBoxB;
  pos = box->FindString(label);
  if (pos != -1) {
    box->Check(pos, checked);
    return;
  }

  box = this->listBoxC;
  pos = box->FindString(label);
    if (pos != -1) {
      box->Check(pos, checked);
      return;
    }
  // What is looooveeeee! Baby don't huuurt meee
}

void CheckBoxPanel::AddCheckBox(std::string label) {
    wxCheckListBox *box = this->listBoxA;
    if (box->GetCount() >= MAX_ITEMS) {
      box = this->listBoxB;
      if (box->GetCount() >= MAX_ITEMS) {
        box = this->listBoxC;
      }
    }

    box->InsertItems(1, new wxString(label), 0);
}

  std::shared_ptr<cpptoml::table> CheckBoxPanel::GetUserState() {
    return NULL;
  }
