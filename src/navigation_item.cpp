#include "navigation_item.hpp"
#include <string>

NavigationItem::NavigationItem(wxWindow *parent,
                               wxWindowID id,
                               const wxString &label,
                               const DataManager::PanelId target,
                               const wxPoint &pos,
                               const wxSize &size,
                               int64_t style)
  : wxButton(parent, id, label, pos, size, style) {
  target_ = target;
  SetBackgroundColour(wxColour(255, 0, 0));
}

DataManager::PanelId NavigationItem::GetTarget() {
  return target_;
}
