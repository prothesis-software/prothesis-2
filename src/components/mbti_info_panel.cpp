#include "mbti_info_panel.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

MbtiInfoPanel::MbtiInfoPanel(wxWindow* parent, wxWindowID id,
                             const wxPoint& pos, const wxSize& size,
                             int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  DoLayout();
}

void MbtiInfoPanel::SetMbti(std::string mbti) {
  wxLogDebug("MbtiInfoPanel::SetMbti() START");

  if (mbti.length() != 4) {
    wxLogWarning("Invalid MBTI string");
  }

  mbti_ = mbti;
  struct MbtiInfoPanel::MbtiInfo mbti_info = GetMbtiInfo(mbti);

  for (size_t i = 0; i < 4; i++) {
    labels_mbti_[i]->SetLabel(mbti.substr(i, 1));
    descriptions_1_[i]->SetLabel(mbti_info.descriptions_1.at(i));

    if (i < 3) {
      descriptions_2_[i]->SetLabel(mbti_info.descriptions_2.at(i));
    }
  }

  for (size_t i = 0; i < 4; i++) {
    descriptions_1_[i]->Wrap(DESC_1_WRAP_PX);
    if (i < 3) {
      descriptions_2_[i]->Wrap(DESC_2_WRAP_PX);
    }
  }

  this->Layout();
}

void MbtiInfoPanel::SetMbtiInfoData(std::shared_ptr<cpptoml::table> gui_state) {
  wxLogDebug("MbtiInfoPanel::SetMbtiInfoData() START");
  auto mbti_table = gui_state->get_table("mbti_info");

  if (mbti_table) {
    struct MbtiInfoPanel::MbtiEntry mbti_entry;

    auto type_array = mbti_table->get_table_array("type");
    if (type_array) {
      for (const auto& type_table : *type_array) {
        auto key = type_table->get_as<std::string>("key");
        if (key) {
          mbti_entry.key = *key;
        } else {
          wxLogWarning("Could not find key 'key' on [[mbti_info.type]]");
        }

        auto desc1 = type_table->get_as<std::string>("description_1");
        if (desc1) {
          mbti_entry.desc1 = *desc1;
        } else {
          wxLogWarning(
              "Could not find key 'description_2' on [[mbti_info.type]]");
        }

        auto desc2 = type_table->get_as<std::string>("description_2");
        if (desc2) {
          mbti_entry.desc2 = *desc2;
        } else {
          wxLogWarning(
              "Could not find key 'description_2' on [[mbti_info.type]]");
        }

        mbti_entries_.push_back(mbti_entry);
      }
    }
  } else {
    wxLogWarning("Could not find table 'mbti_info' in GUI config");
  }
}

struct MbtiInfoPanel::MbtiEntry MbtiInfoPanel::GetMbtiEntry(std::string key) {
  for (size_t i = 0; i < mbti_entries_.size(); i++) {
    if (mbti_entries_.at(i).key.compare(key) == 0) {
      return mbti_entries_.at(i);
    }
  }

  struct MbtiInfoPanel::MbtiEntry error;
  error.key = "Error";

  wxLogWarning(_("Could not find mbti key " + key));
  return error;
}

struct MbtiInfoPanel::MbtiInfo MbtiInfoPanel::GetMbtiInfo(std::string mbti) {
  wxLogDebug("MbtiInfoPanel::GetMbtiInfo() START");
  struct MbtiInfoPanel::MbtiInfo mbti_info;

  // Get description 1
  for (size_t i = 0; i < 4; i++) {
    std::stringstream ss;
    ss << mbti.at(i);
    std::string mbti_letter = "";
    ss >> mbti_letter;

    struct MbtiEntry entry = GetMbtiEntry(mbti_letter);
    mbti_info.descriptions_1.push_back(entry.desc1);
  }

  // First desc2
  struct MbtiEntry entry = GetMbtiEntry(mbti.substr(0, 1));
  mbti_info.descriptions_2.push_back(entry.desc2);

  // Middle desc2
  std::string long_key = "";
  long_key = mbti.substr(1, 2);
  wxLogDebug(_(long_key));

  for (size_t k = 0; k < mbti_entries_.size(); k++) {
    if (mbti_entries_.at(k).key.compare(long_key) == 0) {
      mbti_info.descriptions_2.push_back(mbti_entries_.at(k).desc2);
      break;
    }
  }

  // Last desc2
  entry = GetMbtiEntry(mbti.substr(3, 1));
  mbti_info.descriptions_2.push_back(entry.desc2);

  if (mbti_info.descriptions_1.size() != 4 ||
      mbti_info.descriptions_2.size() != 3) {
    wxLogWarning(
        "Could not parse MBTI info. Error on [mbti_info] (most likely)");
  }

  return mbti_info;
}

void MbtiInfoPanel::DoLayout() {
  wxGridBagSizer* sizer = new wxGridBagSizer(0, 0);

  wxStaticLine* line1 = new wxStaticLine(this);
  wxStaticLine* line2 = new wxStaticLine(this);
  wxStaticLine* line3 = new wxStaticLine(this);

  wxStaticText* mbti1 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* mbti2 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* mbti3 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* mbti4 = new wxStaticText(this, wxID_ANY, wxEmptyString);

  wxStaticText* desc1 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* desc2 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* desc3 = new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* desc4 = new wxStaticText(this, wxID_ANY, wxEmptyString);

  wxStaticText* ext_desc1 =
      new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* ext_desc2 =
      new wxStaticText(this, wxID_ANY, wxEmptyString);
  wxStaticText* ext_desc3 = new wxStaticText(
      this, wxID_ANY, wxEmptyString);

  const int kFlags = wxALL | wxALIGN_CENTER;
  const int kBorder = 6;

  sizer->Add(line1, wxGBPosition(0, 0), wxGBSpan(1, 3), wxEXPAND, 0);
  sizer->Add(line2, wxGBPosition(2, 0), wxGBSpan(1, 3), wxEXPAND, 0);
  sizer->Add(line3, wxGBPosition(5, 0), wxGBSpan(1, 3), wxEXPAND, 0);

  sizer->Add(mbti1, wxGBPosition(1, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer->Add(mbti2, wxGBPosition(3, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer->Add(mbti3, wxGBPosition(4, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer->Add(mbti4, wxGBPosition(6, 0), wxGBSpan(1, 1), kFlags, kBorder);

  const int kDescFlags = wxALL | wxALIGN_LEFT;
  const int kDescBorder = 6;

  sizer->Add(desc1, wxGBPosition(1, 1), wxGBSpan(1, 1), kDescFlags,
             kDescBorder);
  sizer->Add(desc2, wxGBPosition(3, 1), wxGBSpan(1, 1), kDescFlags,
             kDescBorder);
  sizer->Add(desc3, wxGBPosition(4, 1), wxGBSpan(1, 1), kDescFlags,
             kDescBorder);
  sizer->Add(desc4, wxGBPosition(6, 1), wxGBSpan(1, 1), kDescFlags,
             kDescBorder);

  labels_mbti_[0] = mbti1;
  labels_mbti_[1] = mbti2;
  labels_mbti_[2] = mbti3;
  labels_mbti_[3] = mbti4;

  for (size_t i = 0; i < 4; i++) {
    wxFont font = labels_mbti_[i]->GetFont();
    font.SetPointSize(16);
    font.MakeBold();
    labels_mbti_[i]->SetFont(font);
  }

  descriptions_1_[0] = desc1;
  descriptions_1_[1] = desc2;
  descriptions_1_[2] = desc3;
  descriptions_1_[3] = desc4;

  descriptions_2_[0] = ext_desc1;
  descriptions_2_[1] = ext_desc2;
  descriptions_2_[2] = ext_desc3;

  sizer->Add(ext_desc1, wxGBPosition(1, 2), wxGBSpan(1, 1), 0, 0);
  sizer->Add(ext_desc2, wxGBPosition(3, 2), wxGBSpan(2, 1), wxALIGN_CENTER, 0);
  sizer->Add(ext_desc3, wxGBPosition(6, 2), wxGBSpan(1, 1), 0, 0);

  this->SetSizer(sizer);
  sizer->Fit(this);

  Layout();
}
