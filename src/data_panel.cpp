#include "data_panel.hpp"
#include <string>

DataPanel::DataPanel(wxWindow* parent,
                     wxWindowID id,
                     std::string panel_name,
                     const wxPoint& pos,
                     const wxSize& size,
                     int64_t style)
  : wxPanel(parent, id, pos, size, style) {
  panel_name_ = panel_name;
}

std::string DataPanel::GetPanelName() {
  return panel_name_;
}
