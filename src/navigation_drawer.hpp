#ifndef NAVIGATION_DRAWER_HPP_
#define NAVIGATION_DRAWER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/dataview.h>

#include <string>

#include "data_manager.hpp"

class NavigationDrawer : public wxPanel {
 public:
  NavigationDrawer(wxWindow* parent,
                   wxWindowID id,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   int64_t style = 0);
  void AddItem(std::string text, DataManager::PanelId);

 private:
  void OnLinkClick(wxCommandEvent &event);  // NOLINT
  void SetProperties();
  void DoLayout();
  wxFlexGridSizer *sizer_ = NULL;
  wxDataViewTreeCtrl *tree_ = NULL;
};

#endif  // NAVIGATION_DRAWER_HPP_
