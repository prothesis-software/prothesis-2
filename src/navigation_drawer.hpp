#ifndef NAVIGATION_DRAWER_HPP_
#define NAVIGATION_DRAWER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>

class NavigationDrawer : public wxPanel {
 public:
  NavigationDrawer(wxWindow* parent,
                   wxWindowID id,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   int64_t style = 0);
  void AddItem(std::string text);

 private:
  void SetProperties();
  void DoLayout();
  wxFlexGridSizer *sizer_ = NULL;
};

#endif  // NAVIGATION_DRAWER_HPP_
