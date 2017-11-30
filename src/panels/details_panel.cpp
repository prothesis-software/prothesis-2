#include "details_panel.hpp"
#include <memory>
#include <string>

DetailsPanel::DetailsPanel(wxWindow *parent,
                           wxWindowID id,
                           std::string panel_name,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : DataPanel(parent, id, panel_name, pos, size, style) {
  text_ctrl_name_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_surname_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  spin_ctrl_age_ = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxSP_VERTICAL | wxSP_ARROW_KEYS,
                                  0, 100, 18);

  // TODO(egeldenhuys):
  // - Handle Invalid date exception when text is deleted
  // - Use dd/mm/yyyy date format
  datepicker_ctrl_ = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime,
                                          wxDefaultPosition, wxDefaultSize,
                                          wxDP_DEFAULT | wxDP_SHOWCENTURY);
  time_t time_now = wxDateTime::GetTimeNow();
  wxDateTime dt;
  dt.Set(time_now);
  dt.SetCountry(wxDateTime::Country::France);
  datepicker_ctrl_->SetValue(dt);

  button_next_ = new wxButton(this, kButtonNextId, _("Next"));

  SetProperties();
  DoLayout();
}

void DetailsPanel::SetProperties() {
  text_ctrl_name_->SetMinSize(wxSize(150, -1));
  text_ctrl_surname_->SetMinSize(wxSize(200, -1));
}

void DetailsPanel::DoLayout() {
  const int kPanelBorderSize = 10;

  wxFlexGridSizer *details_grid_sizer = new wxFlexGridSizer(5, 2, 7, 25);
  wxStaticText *label_name = new wxStaticText(this, wxID_ANY, _("Name"));
  details_grid_sizer->Add(label_name, 0, wxTOP | wxLEFT, kPanelBorderSize);
  wxStaticText* label_surname = new wxStaticText(this, wxID_ANY, _("Surname"));
  details_grid_sizer->Add(label_surname, 0, wxTOP | wxRIGHT, kPanelBorderSize);

  details_grid_sizer->Add(text_ctrl_name_, 0, wxLEFT, kPanelBorderSize);
  details_grid_sizer->Add(text_ctrl_surname_, 0, wxRIGHT, kPanelBorderSize);

  wxStaticText* label_age = new wxStaticText(this, wxID_ANY, _("Age"));
  details_grid_sizer->Add(label_age, 0, wxLEFT, kPanelBorderSize);

  wxStaticText* label_date = new wxStaticText(this, wxID_ANY, _("Date"));
  details_grid_sizer->Add(label_date, 0, wxRIGHT, kPanelBorderSize);

  details_grid_sizer->Add(spin_ctrl_age_, 0, wxLEFT,
                          kPanelBorderSize);
  details_grid_sizer->Add(datepicker_ctrl_, 0, wxRIGHT,
                          kPanelBorderSize);
  details_grid_sizer->Add(0, 0, 0, 0, 0);
  details_grid_sizer->Add(button_next_, 0, wxRIGHT | wxBOTTOM | wxALIGN_RIGHT,
                          kPanelBorderSize);
  this->SetSizer(details_grid_sizer);
  details_grid_sizer->Fit(this);
}

void DetailsPanel::OnButtonNextClick(wxCommandEvent &event) {
  event.Skip();
  wxLogDebug(wxT("DetailsPanel::ButtonNextOnClick not implemented yet"));
}

bool DetailsPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug(wxT("DetailsPanel does not use a GUI config."));
  return false;
}

// cpptoml::base was is to pass the shared_ptr in a
// different way in an attempt to fix the windows
// problems
// TODO(egeldenhuys): Fix on Windows
std::shared_ptr<cpptoml::table> DetailsPanel::GetUserState() {
  wxLogDebug(_("DetailsPanel::GetUserState()"));
  // std::shared_ptr<cpptoml::table> root = cpptoml::make_table();
  std::shared_ptr<cpptoml::table> panel_data = cpptoml::make_table();

  panel_data->insert("name", text_ctrl_name_->GetLineText(0).ToStdString());
  panel_data->insert("surname", text_ctrl_surname_->GetLineText(0)
                     .ToStdString());
  panel_data->insert("age", spin_ctrl_age_->GetValue());
  panel_data->insert("date", datepicker_ctrl_->GetValue()
               .FormatISODate().ToStdString());
  // root->insert("details", panel_data);
  return panel_data;
}

bool DetailsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  std::shared_ptr<cpptoml::table> details_table = state->get_table(panel_name_);

  if (details_table) {
      cpptoml::option<std::string> name =
        details_table->get_as<std::string>("name");
      if (name) {
        text_ctrl_name_->SetValue(_(*name));
      }

      cpptoml::option<std::string> surname =
        details_table->get_as<std::string>("surname");
      if (surname) {
        text_ctrl_surname_->SetValue(_(*surname));
      }

      cpptoml::option<std::string> date =
        details_table->get_as<std::string>("date");
      if (date) {
        wxDateTime date_time;
        date_time.ParseFormat(*date, "%Y-%m-%d");
        datepicker_ctrl_->SetValue(date_time);
      }

      cpptoml::option<int> age =
        details_table->get_as<int>("age");
      if (age) {
        spin_ctrl_age_->SetValue(*age);
      }

      return true;
  } else {
    wxLogDebug("No table exists for DetailsPanel");
    return false;
  }
}

DetailsPanel::~DetailsPanel() {
  // void
}

BEGIN_EVENT_TABLE(DetailsPanel, wxPanel)
EVT_BUTTON(kButtonNextId, DetailsPanel::OnButtonNextClick)
END_EVENT_TABLE()
