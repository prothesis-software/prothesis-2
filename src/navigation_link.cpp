#include "navigation_link.hpp"

NavigationLink::NavigationLink(wxWindow *parent,
                               wxWindowID   id,
                               const wxString &label,
                               const DataManager::PanelId target,
                               const wxPoint &pos,
                               const wxSize &size,
                               int64_t  style,
                               const wxString &name)
  : wxHyperlinkCtrl(parent, id, label, wxEmptyString, pos, size, style, name) {
  target_ = target;
}

DataManager::PanelId NavigationLink::GetTarget() {
  return target_;
}
