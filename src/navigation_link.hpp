#ifndef NAVIGATION_LINK_HPP_
#define NAVIGATION_LINK_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/hyperlink.h>

#include "data_manager.hpp"

class NavigationLink : public wxHyperlinkCtrl {
 public:
  NavigationLink(wxWindow *parent,
                 wxWindowID   id,
                 const wxString &label,
                 const DataManager::PanelId target,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize,
                 int64_t  style = wxHL_DEFAULT_STYLE,
                 const wxString &name = wxHyperlinkCtrlNameStr);

  DataManager::PanelId GetTarget();

 private:
  DataManager::PanelId target_;
};

#endif  // NAVIGATION_LINK_HPP_
