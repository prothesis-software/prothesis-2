#include "details_panel.hpp"
#include <memory>

DetailsPanel::DetailsPanel(wxWindow *parent,
                           wxWindowID id,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : DataPanel(parent, id, pos, size, style) {
  text_ctrl_name_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_surname_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  spin_ctrl_age_ = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxSP_VERTICAL | wxSP_ARROW_KEYS,
                                  0, 100, 18);

  wxDateTime *date_time = new wxDateTime;
  // TODO(egeldenhuys): Handle invalid date + Date format
  datepicker_ctrl_ = new wxDatePickerCtrl(this, wxID_ANY, *date_time,
                                          wxDefaultPosition, wxDefaultSize,
                                          wxDP_DEFAULT | wxDP_SHOWCENTURY);
  delete date_time;
  button_next_ = new wxButton(this, kButtonNextId, _("Next"));

  SetProperties();
  DoLayout();
}

void DetailsPanel::SetProperties() {
  text_ctrl_name_->SetMinSize(wxSize(150, -1));
  text_ctrl_surname_->SetMinSize(wxSize(200, -1));
}

void DetailsPanel::DoLayout() {
  wxFlexGridSizer *details_grid_sizer = new wxFlexGridSizer(5, 2, 7, 25);
  wxStaticText *label_name = new wxStaticText(this, wxID_ANY, _("Name"));
  // Add (wxWindow *window, int proportion=0, int flag=0, int border=0
  details_grid_sizer->Add(label_name, 0, 0, 0);

  wxStaticText* label_surname = new wxStaticText(this, wxID_ANY, _("Surname"));
  details_grid_sizer->Add(label_surname, 0, 0, 0);

  details_grid_sizer->Add(text_ctrl_name_, 0, 0, 0);
  details_grid_sizer->Add(text_ctrl_surname_, 0, 0, 0);

  wxStaticText* label_age = new wxStaticText(this, wxID_ANY, _("Age"));
  details_grid_sizer->Add(label_age, 0, 0, 0);

  wxStaticText* label_date = new wxStaticText(this, wxID_ANY, _("Date"));
  details_grid_sizer->Add(label_date, 0, 0, 0);

  details_grid_sizer->Add(spin_ctrl_age_, 0, 0, 0);
  details_grid_sizer->Add(datepicker_ctrl_, 0, 0, 0);
  details_grid_sizer->Add(0, 0, 0, 0, 0);
  details_grid_sizer->Add(button_next_, 0, wxALIGN_RIGHT, 0);
  this->SetSizer(details_grid_sizer);
  details_grid_sizer->Fit(this);
}

void DetailsPanel::OnButtonNextClick(wxCommandEvent &event) {
  event.Skip();
  // notify the user that he hasn't implemented the event handler yet
  wxLogDebug(wxT("DetailsPanel::ButtonNextOnClick not implemented yet"));
}

bool DetailsPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug(wxT("DetailsPanel::SetGuiState not implemented yet"));
  return false;
}

std::shared_ptr<cpptoml::table> DetailsPanel::GetUserState() {
  wxLogDebug(wxT("DetailsPanel::GetUserState not implemented yet"));
  return NULL;
}


bool DetailsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug(wxT("DetailsPanel::SetUserSate not implemented yet"));
  return false;
}

DetailsPanel::~DetailsPanel() {
  // void
}

BEGIN_EVENT_TABLE(DetailsPanel, wxPanel)
EVT_BUTTON(kButtonNextId, DetailsPanel::OnButtonNextClick)
END_EVENT_TABLE()
