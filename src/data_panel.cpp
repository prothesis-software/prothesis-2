#include "data_panel.hpp"
#include <string>
#include <vector>

std::vector<DataPanel*> DataPanel::panels_;

DataPanel::DataPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                     std::string panel_title, const wxPoint& pos,
                     const wxSize& size, int64_t style)
    : wxScrolled<wxPanel>(parent, id, pos, size, style) {
  panel_name_ = panel_name;
  panel_title_ = panel_title;

  DataPanel::panels_.push_back(this);
  this->Bind(wxEVT_SIZE, &DataPanel::OnSizeChange, this);
}

std::string DataPanel::GetPanelName() { return panel_name_; }

std::string DataPanel::GetPanelTitle() { return panel_title_; }

bool DataPanel::Next() { return false; }

void DataPanel::OnTabActivate() {
  wxLogDebug(_("OnTabActivate not implemented for ") + _(this->GetPanelName()));
}

void DataPanel::OnSizeChange(wxSizeEvent& event) {
  wxLogDebug("Changed panel size event");
  // this->SetScrollRate(10, 10);
}

DataPanel* DataPanel::GetPanelByName(std::string panel_name) {
  for (size_t i = 0; i < DataPanel::panels_.size(); i++) {
    if (panels_.at(i)->GetPanelName().compare(panel_name) == 0) {
      return panels_.at(i);
    }
  }
  wxLogWarning(_("Unable to find panel with the name '") + _(panel_name) +
               _("'"));
  return NULL;
}
