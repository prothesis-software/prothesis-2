#include "details_panel.hpp"
#include <memory>
#include <string>
#include "src/main_frame.hpp"

DetailsPanel::DetailsPanel(wxWindow *parent,
                           wxWindowID id,
                           std::string panel_name,
                           std::string panel_title,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  wxLogDebug("DetailsPanel::DetailsPanel() START");
  text_ctrl_name_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_surname_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  spin_ctrl_age_ = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxSP_VERTICAL | wxSP_ARROW_KEYS,
                                  0, 100, 18);
  datepicker_ctrl_ = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime,
                                          wxDefaultPosition, wxDefaultSize,
                                          wxDP_DEFAULT | wxDP_SHOWCENTURY);
  SetProperties();
  DoLayout();
  wxLogDebug("DetailsPanel::DetailsPanel() END");
}

void DetailsPanel::SetProperties() {
  text_ctrl_name_->SetMinSize(wxSize(150, -1));
  text_ctrl_surname_->SetMinSize(wxSize(200, -1));
}

void DetailsPanel::DoLayout() {
  wxLogDebug("DetailsPanel::DoLayout() START");
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
  details_grid_sizer->Add(0, 0, 0, 0);

  this->SetSizer(details_grid_sizer);
  Layout();
  details_grid_sizer->Fit(this);
  wxLogDebug("DetailsPanel::DoLayout() END");
}

bool DetailsPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  wxLogDebug(wxT("DetailsPanel does not use a GUI config."));
  return false;
}

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
  return panel_data;
}

bool DetailsPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  std::shared_ptr<cpptoml::table> details_table = state->get_table(panel_name_);

  if (!details_table->empty()) {
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
  // wxLogDebug("DetailsPanel::~DetailsPanel()");
}
