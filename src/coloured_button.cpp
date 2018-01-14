#include "coloured_button.hpp"

#include <string>

ColouredButton::ColouredButton(wxWindow* parent, wxWindowID id,
                               std::string label, const wxPoint& pos,
                               const wxSize& size, int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  button_ = new wxButton(this, wxID_ANY, label);
  DoLayout();
}

ColouredButton::~ColouredButton() {
  // void
}

void ColouredButton::SetColour(wxColour colour) {
  colour_ = colour;
  button_->SetForegroundColour(colour);
}

wxColour ColouredButton::GetColour() { return colour_; }

std::string ColouredButton::GetButtonLabel() {
  return button_->GetLabel().ToStdString();
}

wxButton* ColouredButton::GetButton() { return button_; }

void ColouredButton::DoLayout() {
  wxBoxSizer* sizer_h = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* sizer_v = new wxBoxSizer(wxVERTICAL);

  sizer_h->Add(button_, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 0);
  sizer_v->Add(sizer_h, 1, wxALIGN_CENTER | wxEXPAND, 0);

  this->SetSizer(sizer_v);
  sizer_v->Fit(this);
  Layout();
}
