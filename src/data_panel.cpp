#include "data_panel.hpp"
#include <string>
#include <vector>

std::vector<DataPanel*> DataPanel::panels_;

DataPanel::DataPanel(wxWindow* parent,
                     wxWindowID id,
                     std::string panel_name,
                     std::string panel_title,
                     const wxPoint& pos,
                     const wxSize& size,
                     int64_t style)
  : wxPanel(parent, id, pos, size, style) {
  panel_name_ = panel_name;
  panel_title_ = panel_title;

  DataPanel::panels_.push_back(this);
}

std::string DataPanel::GetPanelName() {
  return panel_name_;
}

std::string DataPanel::GetPanelTitle() {
  return panel_title_;
}

bool DataPanel::Next() {
  return false;
}

DataPanel* DataPanel::GetPanelByName(std::string panel_name) {
  for (size_t i = 0; i < DataPanel::panels_.size(); i++) {
    if (panels_.at(i)->GetPanelName().compare(panel_name) == 0) {
      return panels_.at(i);
    }
  }
  wxLogWarning(_("Unable to find panel with the name '") +
               _(panel_name) +
               _("'"));
  return NULL;
}
