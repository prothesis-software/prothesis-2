#ifndef NAVIGATION_ITEM_HPP_
#define NAVIGATION_ITEM_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "data_manager.hpp"

class NavigationItem : public wxButton {
 public:
  NavigationItem(
      wxWindow *parent, wxWindowID id, const wxString &label = wxEmptyString,
      const DataManager::PanelId target = DataManager::PanelId::kDefaultPanel,
      DataPanel *target_panel = NULL, const wxPoint &pos = wxDefaultPosition,
      const wxSize &size = wxDefaultSize, int64_t style = 0);

  DataManager::PanelId GetTarget();
  DataPanel *GetTargetPanel();

 private:
  DataManager::PanelId target_;
  DataPanel *target_panel_;
};

#endif  // NAVIGATION_ITEM_HPP_
