#include "theme_panel.hpp"

#include <memory>
#include <string>
#include <vector>

ThemePanel::ThemePanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                       std::string panel_title, const wxPoint& pos,
                       const wxSize& size, int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

ThemePanel::~ThemePanel() {
  // void
}

bool ThemePanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> ThemePanel::GetUserState() {
  auto panel_table = cpptoml::make_table();

  panel_table->insert("what", text_what_->GetValue().ToStdString());
  panel_table->insert("how", text_how_->GetValue().ToStdString());
  panel_table->insert("principle", text_principle_->GetValue().ToStdString());

  if (colour_.IsOk()) {
    panel_table->insert("rgb", colour_.GetRGB());
  } else {
    panel_table->insert("rgb", -1);
  }

  return panel_table;
}

ColouredButton* ThemePanel::GetButton() { return button_; }

bool ThemePanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  if (panel_table) {
    auto what = panel_table->get_as<std::string>("what");
    if (what) {
      text_what_->SetValue(*what);
    }

    auto how = panel_table->get_as<std::string>("how");
    if (how) {
      text_how_->SetValue(*how);
    }

    auto principle = panel_table->get_as<std::string>("principle");
    if (principle) {
      text_principle_->SetValue(*principle);
    }

    auto rgb = panel_table->get_as<int>("rgb");
    if (rgb) {
      if (*rgb != -1) {
        wxColour colour;
        colour.SetRGB(*rgb);
        this->SetColour(colour);
      }
    }
  }

  return true;
}

void ThemePanel::SetColour(wxColour colour) {
  colour_ = colour;
  this->SetBackgroundColour(colour);
}

wxColour ThemePanel::GetColour() { return colour_; }

void ThemePanel::DoLayout() {
  int label_border = 5;
  int text_border = 5;
  int text_border_flags = wxBOTTOM | wxRIGHT;

  wxGridBagSizer* sizer = new wxGridBagSizer();

  label_title_ = new wxStaticText(this, wxID_ANY, _(this->GetPanelTitle()));

  wxStaticText* label_what = new wxStaticText(this, wxID_ANY, _("What"));
  text_what_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                              kTextBoxSize, wxTE_MULTILINE);
  wxStaticText* label_how = new wxStaticText(this, wxID_ANY, _("How"));

  text_how_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                             kTextBoxSize, wxTE_MULTILINE);
  wxStaticText* label_principle =
      new wxStaticText(this, wxID_ANY, _("Principle"));
  text_principle_ =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     kTextBoxSize, wxTE_MULTILINE);

  button_ = new ColouredButton(this, wxID_ANY, "Set colour");
  button_->SetMinSize(wxSize(-1, 50));

  // label_title_->SetFont(label_title_->GetFont().MakeBold());
  sizer->Add(label_title_, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALIGN_CENTER);
  sizer->Add(label_what, wxGBPosition(1, 0), wxDefaultSpan,
             wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, label_border);

  sizer->Add(text_what_, wxGBPosition(1, 1), wxDefaultSpan, text_border_flags,
             text_border);

  sizer->Add(label_how, wxGBPosition(2, 0), wxDefaultSpan,
             wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, label_border);
  sizer->Add(text_how_, wxGBPosition(2, 1), wxDefaultSpan, text_border_flags,
             text_border);

  sizer->Add(label_principle, wxGBPosition(3, 0), wxDefaultSpan,
             wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxRIGHT, label_border);

  sizer->Add(text_principle_, wxGBPosition(3, 1), wxDefaultSpan,
             text_border_flags, text_border);

  sizer->Add(button_, wxGBPosition(2, 2), wxDefaultSpan, 0, 0);

  this->SetSizer(sizer);
  Layout();
}
