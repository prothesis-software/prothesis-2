#include "work_environment_panel.hpp"

#include <memory>
#include <string>

WorkEnvironmentPanel::WorkEnvironmentPanel(wxWindow* parent, wxWindowID id,
                                           std::string panel_name,
                                           std::string panel_title,
                                           const wxPoint& pos,
                                           const wxSize& size, int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  label_mbti_ = new wxStaticText(
      this, wxID_ANY, _("Please select MBTI in ") + _("'External' assessment"),
      wxDefaultPosition, wxDefaultSize,
      wxST_ELLIPSIZE_END | wxALIGN_CENTRE_HORIZONTAL);
  text_description_ =
      new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
  DoLayout();
}

WorkEnvironmentPanel::~WorkEnvironmentPanel() {
  wxLogDebug("WorkEnvironmentPanel::~WorkEnvironmentPanel()");
}

bool WorkEnvironmentPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  if (panel_table) {
    work_table_ = panel_table;
    return true;
  } else {
    wxLogDebug("No GUI table found for panel WorkEnvironmentPanel");
  }
  return false;
}

void WorkEnvironmentPanel::FitText() {
  // Source: https://forums.wxwidgets.org/viewtopic.php?t=13879
  // Author: lester
  //       (https://forums.wxwidgets.org/memberlist.php?mode=viewprofile&u=4301)

  wxString t_strValue = text_description_->GetValue();
  wxString t_strLine = "";
  int x = 0;
  int y = 0;
  int width = 0;
  wxFont tFont = GetFont();

  for (size_t i = 0; i < t_strValue.Len(); i++) {
    char ch = t_strValue.GetChar(i);

    if (ch == '\n') {
      GetTextExtent(t_strLine, &x, &y, NULL, NULL, &tFont);

      t_strLine = _("");
      width = wxMax(width, x);
    } else {
      t_strLine += ch;
    }
  }

  wxLogDebug(_(std::to_string(width)));
  text_description_->SetMinSize(wxSize(width, -1));
  // text_description_->SetMaxSize(wxSize(width, -1));
  Layout();
}

std::shared_ptr<cpptoml::table> WorkEnvironmentPanel::GetUserState() {
  DataPanel* external = DataPanel::GetPanelByName("external");

  auto external_table = external->GetUserState();

  if (external_table) {
    auto mbti_array = external_table->get_array_of<std::string>("mbti");

    if (mbti_array) {
      std::string mbti = "";
      for (const auto& mbti_element : *mbti_array) {
        mbti.append(mbti_element);
      }

      if (mbti.length() == 4) {
        label_mbti_->SetLabel(wxString(mbti));
      } else {
        label_mbti_->SetLabel(wxString("Please select MBTI ") +
                              _("in 'External' assessment"));
      }
      int x, y;
      wxFont font = label_mbti_->GetFont();
      GetTextExtent(label_mbti_->GetLabel(), &x, &y, NULL, NULL, &font);
      label_mbti_->SetSize(wxSize(x, -1));

      auto mbti_type_array = work_table_->get_table_array("type");

      if (mbti_type_array) {
        for (const auto& type_table : *mbti_type_array) {
          auto mbti_string = type_table->get_as<std::string>("mbti");

          if (mbti_string) {
            if (mbti_string->compare(mbti) == 0) {
              std::string lines = "";
              auto lines_array = type_table->get_array_of<std::string>("list");
              if (lines_array) {
                for (const auto& line : *lines_array) {
                  lines += "- ";
                  lines += line;
                  lines.append("\n");
                }
                text_description_->SetValue(wxString(lines));
                this->FitText();
              } else {
                wxLogDebug("list array was not found");
              }
            } else {
              // mbti did not match
            }
          } else {
            wxLogDebug("'mbti' field not found");
          }
        }
      } else {
        wxLogDebug(_("MBTI type table array not found"));
      }
    } else {
      wxLogDebug(_("WorkEnvironmentPanel could not") +
                 _("get the mbti array from ExternalPanel"));
    }
  } else {
    wxLogDebug("WorkEnvironmentPanel could not get the state of ExternalPanel");
  }

  return NULL;
}

bool WorkEnvironmentPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  GetUserState();
  return false;
}

void WorkEnvironmentPanel::DoLayout() {
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxFont font = GetFont();
  font.SetPointSize(17);
  label_mbti_->SetFont(font);
  sizer->Add(label_mbti_, 0, wxEXPAND | wxALIGN_CENTER, 0);
  sizer->Add(text_description_, 1, wxEXPAND | wxALIGN_CENTER, 0);
  this->SetSizer(sizer);
  sizer->Fit(this);
}
