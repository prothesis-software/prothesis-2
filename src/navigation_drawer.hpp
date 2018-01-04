#ifndef NAVIGATION_DRAWER_HPP_
#define NAVIGATION_DRAWER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>

#include "data_manager.hpp"
#include "data_panel.hpp"
#include "navigation_item.hpp"
#include "main_frame.hpp"

class NavigationDrawer : public wxPanel {
 public:
  NavigationDrawer(wxWindow* parent,
                   wxWindowID id,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   int64_t style = 0);
  void AddItem(std::string label, DataManager::PanelId target,
               DataPanel *target_panel = NULL);

 private:
  void OnItemClick(wxCommandEvent &event);  // NOLINT
  void SetProperties();
  void DoLayout();
  wxGridSizer *sizer_ = NULL;
};

#endif  // NAVIGATION_DRAWER_HPP_
