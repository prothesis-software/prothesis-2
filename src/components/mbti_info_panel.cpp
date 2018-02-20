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

void MbtiInfoPanel::SetMbti(std::vector<std::string> mbti) {
  std::string result = "";

  for (size_t i = 0; i < 4; i++) {
    if (mbti.at(i).compare(" ") != 0) {
      result += mbti.at(i);
    } else {
      result += " ";
    }
  }

  SetMbti(result);
}

void MbtiInfoPanel::SetMbti(std::string mbti) {
  wxLogDebug("MbtiInfoPanel::SetMbti() START");

  if (mbti.length() != 4) {
    wxLogWarning("Invalid MBTI string");
  }

  mbti_ = mbti;
  struct MbtiInfoPanel::MbtiInfo mbti_info = GetMbtiInfo(mbti);

  wxLogDebug("MbtiInfoPanel::SetMbti() 1");
  for (size_t i = 0; i < 4; i++) {
    wxLogDebug(_("MbtiInfoPanel::SetMbti() letter: " + std::to_string(i)));
    for (size_t j = 0; j < 4; j++) {
      const int selection =
          choice_boxes_mbti_[j]->FindString(mbti.substr(i, 1));
      if (selection != wxNOT_FOUND) {
        wxLogDebug("MbtiInfoPanel::SetMbti() Setting Choice");
        choice_boxes_mbti_[j]->SetSelection(selection);
      }
    }

    wxLogDebug("MbtiInfoPanel::SetMbti() Setting label and desc1");
    labels_mbti_[i]->SetLabel(mbti.substr(i, 1));
    descriptions_1_[i]->SetLabel(mbti_info.descriptions_1.at(i));

    if (i < 3) {
      wxLogDebug(
          _("MbtiInfoPanel::SetMbti() setting desc2: " + std::to_string(i)));
      descriptions_2_[i]->SetLabel(mbti_info.descriptions_2.at(i));
      wxLogDebug("MbtiInfoPanel::SetMbti() 2");
    }
  }

  wxLogDebug("MbtiInfoPanel::SetMbti() Setting wrap");
  for (size_t i = 0; i < 4; i++) {
    descriptions_1_[i]->Wrap(DESC_1_WRAP_PX);
    if (i < 3) {
      descriptions_2_[i]->Wrap(DESC_2_WRAP_PX);
    }
  }

  this->Layout();
  this->Fit();
  wxLogDebug("MbtiInfoPanel::SetMbti() END");
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
  error.key = "error";
  error.desc1 = "error";
  error.desc2 = "error";

  wxLogDebug(_("Could not find mbti key " + key));
  return error;
}

struct MbtiInfoPanel::MbtiInfo MbtiInfoPanel::GetMbtiInfo(std::string mbti) {
  wxLogDebug("MbtiInfoPanel::GetMbtiInfo() START");

  if (mbti.length() != 4) {
    wxLogDebug("MbtiInfoPanel::GetMbtiInfo(): Incorrect mbti str len");
    wxLogWarning("MbtiInfoPanel::GetMbtiInfo(): Incorrect mbti str len");
  }

  struct MbtiInfoPanel::MbtiInfo mbti_info;

  // Get description 1
  for (size_t i = 0; i < 4; i++) {
    std::stringstream ss;
    ss << mbti.at(i);
    std::string mbti_letter = "";
    ss >> mbti_letter;

    struct MbtiEntry entry = GetMbtiEntry(mbti_letter);

    if (entry.key.compare("error") != 0) {
      mbti_info.descriptions_1.push_back(entry.desc1);
    } else {
      mbti_info.descriptions_1.push_back("");
    }
  }

  // First desc2
  struct MbtiEntry entry = GetMbtiEntry(mbti.substr(0, 1));
  if (entry.key.compare("error") != 0) {
    mbti_info.descriptions_2.push_back(entry.desc2);
  } else {
    mbti_info.descriptions_2.push_back("");
  }

  // Middle desc2
  std::string long_key = "";
  long_key = mbti.substr(1, 2);
  wxLogDebug(_(long_key));

  bool found = false;
  for (size_t k = 0; k < mbti_entries_.size(); k++) {
    if (mbti_entries_.at(k).key.compare(long_key) == 0) {
      mbti_info.descriptions_2.push_back(mbti_entries_.at(k).desc2);
      found = true;
      break;
    }
  }

  if (!found) {
    mbti_info.descriptions_2.push_back("");
  }

  // Last desc2
  entry = GetMbtiEntry(mbti.substr(3, 1));
  if (entry.key != "error") {
    mbti_info.descriptions_2.push_back(entry.desc2);
  } else {
    mbti_info.descriptions_2.push_back("");
  }

  if (mbti_info.descriptions_1.size() != 4) {
    wxLogDebug("mbti_info.descriptions_1.size() != 4");
  }

  if (mbti_info.descriptions_2.size() != 3) {
    wxLogDebug("mbti_info.descriptions_2.size() != 3");
  }

  wxLogDebug("MbtiInfoPanel::GetMbtiInfo() END");
  return mbti_info;
}

std::vector<std::string> MbtiInfoPanel::GetMbtiAsVector() {
  std::string mbti = GetMbti();
  std::vector<std::string> result;

  for (size_t i = 0; i < mbti.length(); i++) {
    result.push_back(mbti.substr(i, 1));
  }

  return result;
}

std::string MbtiInfoPanel::GetMbti() {
  std::string mbti_string = "";

  // mbti
  std::string mbti[4];
  for (size_t i = 0; i < 4; i++) {
    const int selection = choice_boxes_mbti_[i]->GetSelection();
    if (selection != wxNOT_FOUND) {
      const std::string value =
          choice_boxes_mbti_[i]->GetString(selection).ToStdString();

      mbti[i] = value;
    } else {
      mbti[i] = " ";
    }
    mbti_string += mbti[i];
  }

  return mbti_string;
}

void MbtiInfoPanel::HideMbtiSelection() {
  sizer_root_->Hide(sizer_mbti_combo_boxes_, true);

  for (size_t i = 0; i < 4; i++) {
    choice_boxes_mbti_[i]->Hide();
  }

  this->Layout();
}

void MbtiInfoPanel::OnMbtiChange(wxCommandEvent& event) {
  std::string mbti = GetMbti();

  if (mbti.length() == 4) {
    SetMbti(mbti);
  }

  sizer_root_->Fit(this);
  this->GetParent()->Layout();
}

void MbtiInfoPanel::AddMbtiTuple(std::vector<wxArrayString>* source_vector,
                                 std::string str1, std::string str2) {
  wxArrayString tuple;
  tuple.Add(str1);
  tuple.Add(str2);
  source_vector->push_back(tuple);
}

void MbtiInfoPanel::DoLayout() {
  sizer_ = new wxGridBagSizer(0, 0);
  sizer_root_ = new wxStaticBoxSizer(wxVERTICAL, this, "MBTI");
  wxWindow* parent_sizer = sizer_root_->GetStaticBox();

  sizer_mbti_combo_boxes_ = new wxBoxSizer(wxHORIZONTAL);

  std::vector<wxArrayString> mbti_tuples;

  AddMbtiTuple(&mbti_tuples, "I", "E");
  AddMbtiTuple(&mbti_tuples, "S", "N");
  AddMbtiTuple(&mbti_tuples, "T", "F");
  AddMbtiTuple(&mbti_tuples, "J", "P");

  for (size_t i = 0; i < 4; i++) {
    choice_boxes_mbti_[i] =
        new wxChoice(parent_sizer, wxID_ANY, wxDefaultPosition, wxSize(60, -1),
                     mbti_tuples[i]);
    sizer_mbti_combo_boxes_->Add(choice_boxes_mbti_[i], 0, 0, 0);
    sizer_mbti_combo_boxes_->AddSpacer(5);
    choice_boxes_mbti_[i]->Bind(wxEVT_CHOICE, &MbtiInfoPanel::OnMbtiChange,
                                this);
  }

  sizer_root_->Add(sizer_mbti_combo_boxes_, 0, wxALL, 6);

  wxStaticLine* line1 = new wxStaticLine(parent_sizer);
  wxStaticLine* line2 = new wxStaticLine(parent_sizer);
  wxStaticLine* line3 = new wxStaticLine(parent_sizer);

  wxStaticText* mbti1 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* mbti2 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* mbti3 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* mbti4 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);

  wxStaticText* desc1 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* desc2 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* desc3 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* desc4 = new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);

  wxStaticText* ext_desc1 =
      new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* ext_desc2 =
      new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);
  wxStaticText* ext_desc3 =
      new wxStaticText(parent_sizer, wxID_ANY, wxEmptyString);

  const int kFlags = wxALL | wxALIGN_CENTER;
  const int kBorder = 6;

  sizer_->Add(line1, wxGBPosition(0, 0), wxGBSpan(1, 3), wxEXPAND, 0);
  sizer_->Add(line2, wxGBPosition(2, 0), wxGBSpan(1, 3), wxEXPAND, 0);
  sizer_->Add(line3, wxGBPosition(5, 0), wxGBSpan(1, 3), wxEXPAND, 0);

  sizer_->Add(mbti1, wxGBPosition(1, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer_->Add(mbti2, wxGBPosition(3, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer_->Add(mbti3, wxGBPosition(4, 0), wxGBSpan(1, 1), kFlags, kBorder);
  sizer_->Add(mbti4, wxGBPosition(6, 0), wxGBSpan(1, 1), kFlags, kBorder);

  const int kDescFlags = wxALL | wxALIGN_LEFT;
  const int kDescBorder = 6;

  sizer_->Add(desc1, wxGBPosition(1, 1), wxGBSpan(1, 1), kDescFlags,
              kDescBorder);
  sizer_->Add(desc2, wxGBPosition(3, 1), wxGBSpan(1, 1), kDescFlags,
              kDescBorder);
  sizer_->Add(desc3, wxGBPosition(4, 1), wxGBSpan(1, 1), kDescFlags,
              kDescBorder);
  sizer_->Add(desc4, wxGBPosition(6, 1), wxGBSpan(1, 1), kDescFlags,
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

  sizer_->Add(ext_desc1, wxGBPosition(1, 2), wxGBSpan(1, 1), wxLEFT, 20);
  sizer_->Add(ext_desc2, wxGBPosition(3, 2), wxGBSpan(2, 1), wxLEFT, 20);
  sizer_->Add(ext_desc3, wxGBPosition(6, 2), wxGBSpan(1, 1), wxLEFT, 20);

  sizer_root_->Add(sizer_, 0, wxALL, 6);
  this->SetSizer(sizer_root_);

  Layout();
}
