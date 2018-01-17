#include "mbti_panel.hpp"

#include <memory>
#include <string>
#include <vector>

MbtiPanel::MbtiPanel(wxWindow* parent, wxWindowID id,

                     const wxPoint& pos, const wxSize& size, int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  DoLayout();
}

MbtiPanel::~MbtiPanel() {
  // void
}

void MbtiPanel::SetMbti(std::string mbti) {
  mbti_ = mbti;
  label_mbti_->SetLabel(mbti);
}

std::string MbtiPanel::GetMbti() { return mbti_; }

void MbtiPanel::DoLayout() {
  this->SetMinSize(wxSize(50, -1));

  wxStaticBoxSizer* sizer = new wxStaticBoxSizer(wxVERTICAL, this, "MBTI");
  label_mbti_ = new wxStaticText(sizer->GetStaticBox(), wxID_ANY, "        ");

  sizer->Add(label_mbti_, 0, wxALIGN_CENTER | wxALL, 10);

  this->SetSizer(sizer);
  Layout();
}
