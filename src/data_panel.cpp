#include "data_panel.hpp"
#include <string>

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
}

std::string DataPanel::GetPanelName() {
  return panel_name_;
}

std::string DataPanel::GetPanelTitle() {
  return panel_title_;
}
