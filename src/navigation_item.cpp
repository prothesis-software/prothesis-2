#include "navigation_item.hpp"
#include <string>

NavigationItem::NavigationItem(wxWindow* parent, wxWindowID id,
                               const wxString& label,
                               const DataManager::PanelId target,
                               DataPanel* target_panel, const wxPoint& pos,
                               const wxSize& size, int64_t style)
    : wxButton(parent, id, label, pos, size, style) {
  target_ = target;
  target_panel_ = target_panel;
}

DataManager::PanelId NavigationItem::GetTarget() { return target_; }

DataPanel* NavigationItem::GetTargetPanel() {
  if (target_panel_ == NULL) {
    wxLogWarning(_("Navigation item has not target panel!"));
  }
  return target_panel_;
}
