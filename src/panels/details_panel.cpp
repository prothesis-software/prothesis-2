#include "details_panel.hpp"
#include <memory>

DetailsPanel::DetailsPanel(wxWindow *parent,
                           wxWindowID id,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : DataPanel(parent, id, pos, size, style) {
  // begin wxGlade: DetailsPanel::DetailsPanel
  text_ctrl_name = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_surname = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  spin_ctrl_age = new wxSpinCtrl(this, wxID_ANY, wxT("18"), wxDefaultPosition,
                                 wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
  datepicker_ctrl_1 = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime,
                                           wxDefaultPosition, wxDefaultSize,
                                           wxDP_DEFAULT|wxDP_SHOWCENTURY);
  button_next = new wxButton(this, wxID_ANY, _("Next"));

  set_properties();
  do_layout();
  // end wxGlade
}

void DetailsPanel::set_properties() {
  // begin wxGlade: DetailsPanel::set_properties
  text_ctrl_name->SetMinSize(wxSize(150, -1));
  text_ctrl_surname->SetMinSize(wxSize(200, -1));
  // end wxGlade
}


void DetailsPanel::do_layout() {
  // begin wxGlade: DetailsPanel::do_layout
  wxFlexGridSizer* details_grid_sizer = new wxFlexGridSizer(0, 2, 7, 25);
  wxStaticText* label_name = new wxStaticText(this, wxID_ANY, _("Name"));
  details_grid_sizer->Add(label_name, 0, 0, 0);
  wxStaticText* label_surname = new wxStaticText(this, wxID_ANY, _("Surname"));
  details_grid_sizer->Add(label_surname, 0, 0, 0);
  details_grid_sizer->Add(text_ctrl_name, 0, 0, 0);
  details_grid_sizer->Add(text_ctrl_surname, 0, 0, 0);
  wxStaticText* label_age = new wxStaticText(this, wxID_ANY, _("Age"));
  details_grid_sizer->Add(label_age, 0, 0, 0);
  wxStaticText* label_date = new wxStaticText(this, wxID_ANY, _("Date"));
  details_grid_sizer->Add(label_date, 0, 0, 0);
  details_grid_sizer->Add(spin_ctrl_age, 0, 0, 0);
  details_grid_sizer->Add(datepicker_ctrl_1, 0, 0, 0);
  details_grid_sizer->Add(0, 0, 0, 0, 0);
  details_grid_sizer->Add(button_next, 0, wxALIGN_RIGHT, 0);
  this->SetSizer(details_grid_sizer);
  details_grid_sizer->Fit(this);
  // end wxGlade
}

void DetailsPanel::ButtonNextOnClick(wxCommandEvent &event) {
  event.Skip();
  // notify the user that he hasn't implemented the event handler yet
  wxLogDebug(wxT("(DetailsPanel::ButtonNextOnClick) not implemented yet"));
}

bool DetailsPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> DetailsPanel::GetUserState() {
  return NULL;
}


bool DetailsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

DetailsPanel::~DetailsPanel() {
  // void
}

BEGIN_EVENT_TABLE(DetailsPanel, wxPanel)
// begin wxGlade: DetailsPanel::event_table
EVT_BUTTON(wxID_ANY, DetailsPanel::ButtonNextOnClick)
// end wxGlade
END_EVENT_TABLE()
