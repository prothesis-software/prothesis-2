#include "details_panel.hpp"
#include <memory>
#include <string>
#include "src/main_frame.hpp"

DetailsPanel::DetailsPanel(wxWindow* parent, wxWindowID id,
                           std::string panel_name, std::string panel_title,
                           const wxPoint& pos, const wxSize& size,
                           int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  wxLogDebug("DetailsPanel::DetailsPanel() START");
  text_email_address_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_name_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  text_ctrl_surname_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
  spin_ctrl_age_ = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxSP_VERTICAL | wxSP_ARROW_KEYS, 0, 100, 18);
  datepicker_ctrl_ =
      new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition,
                           wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);
  SetProperties();
  DoLayout();
  wxLogDebug("DetailsPanel::DetailsPanel() END");
}

DetailsPanel::~DetailsPanel() { wxLogDebug("DetailsPanel::~DetailsPanel()"); }

void DetailsPanel::SetProperties() {
  text_ctrl_name_->SetMinSize(wxSize(150, -1));
  text_ctrl_surname_->SetMinSize(wxSize(200, -1));
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
  panel_data->insert("surname",
                     text_ctrl_surname_->GetLineText(0).ToStdString());
  panel_data->insert("age", spin_ctrl_age_->GetValue());
  panel_data->insert(
      "date", datepicker_ctrl_->GetValue().FormatISODate().ToStdString());
  panel_data->insert("email", text_email_address_->GetValue().ToStdString());
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

    cpptoml::option<int> age = details_table->get_as<int>("age");
    if (age) {
      spin_ctrl_age_->SetValue(*age);
    }

    auto email = details_table->get_as<std::string>("email");
    if (email) {
      text_email_address_->SetValue(*email);
    }

    return true;
  } else {
    wxLogDebug("No table exists for DetailsPanel");
    return false;
  }
}

void DetailsPanel::DoLayout() {
  wxLogDebug("DetailsPanel::DoLayout() START");

  const size_t kRowBorder = 10;

  wxFlexGridSizer* details_grid_sizer = new wxFlexGridSizer(1, 3, 6, 26);

  wxStaticText* label_name =
      new wxStaticText(this, wxID_ANY, _("Name"), wxDefaultPosition,
                       wxDefaultSize, wxALIGN_BOTTOM);
  wxStaticText* label_surname =
      new wxStaticText(this, wxID_ANY, _("Surname"), wxDefaultPosition,
                       wxDefaultSize, wxALIGN_BOTTOM);
  wxStaticText* label_age = new wxStaticText(this, wxID_ANY, _("Age"));
  wxStaticText* label_date = new wxStaticText(this, wxID_ANY, _("Date"));
  wxStaticText* label_email = new wxStaticText(this, wxID_ANY, "Email");

  wxBoxSizer* sizer_content = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizer_body = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* sizer_col_left = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizer_name = new wxBoxSizer(wxVERTICAL);
  sizer_name->Add(label_name, 0, 0, 0);
  sizer_name->Add(text_ctrl_name_, 0, 0, 0);

  wxBoxSizer* sizer_age = new wxBoxSizer(wxVERTICAL);
  sizer_age->Add(label_age);
  sizer_age->Add(spin_ctrl_age_, 0, wxEXPAND);

  sizer_col_left->Add(sizer_name, 0, wxALL, kRowBorder);
  sizer_col_left->Add(sizer_age, 0, wxALL | wxEXPAND, kRowBorder);

  wxBoxSizer* sizer_col_right = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizer_surname = new wxBoxSizer(wxVERTICAL);
  sizer_surname->Add(label_surname);
  sizer_surname->Add(text_ctrl_surname_);

  wxBoxSizer* sizer_date = new wxBoxSizer(wxVERTICAL);
  sizer_date->Add(label_date);
  sizer_date->Add(datepicker_ctrl_, 0, wxEXPAND | wxALIGN_RIGHT);

  sizer_col_right->Add(sizer_surname, 0, wxALL, kRowBorder);
  sizer_col_right->Add(sizer_date, 0, wxEXPAND | wxALL, kRowBorder);

  sizer_body->Add(sizer_col_left);
  sizer_body->Add(sizer_col_right);

  wxBoxSizer* sizer_email = new wxBoxSizer(wxVERTICAL);
  sizer_email->Add(label_email);
  sizer_email->Add(text_email_address_, 1, wxEXPAND);

  sizer_content->Add(sizer_body);
  sizer_content->Add(sizer_email, 1, wxEXPAND | wxALL, kRowBorder);

  details_grid_sizer->Add(0, 0, 0, 0);
  details_grid_sizer->Add(sizer_content, 0, wxEXPAND, 0);
  details_grid_sizer->Add(0, 0, 0, 0);

  details_grid_sizer->AddGrowableCol(0);
  details_grid_sizer->AddGrowableCol(2);

  wxBitmap bmp;
  // TODO(Armand): Change this so it loads from the app root.
  wxStaticBitmap* image;
  image = new wxStaticBitmap(this, wxID_ANY,
                             wxBitmap("test.jpg", wxBITMAP_TYPE_JPEG),
                             wxPoint(0, 0), wxSize(50, 50));

  sizer_body->Add(image);
  this->SetSizer(details_grid_sizer);
  Layout();
  details_grid_sizer->Fit(this);
  wxLogDebug("DetailsPanel::DoLayout() END");
}
