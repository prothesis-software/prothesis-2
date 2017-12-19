#include "navigation_drawer.hpp"
#include <wx/hyperlink.h>

#include <string>

#include "data_manager.hpp"

NavigationDrawer::NavigationDrawer(wxWindow* parent,
                     wxWindowID id,
                     const wxPoint& pos,
                     const wxSize& size,
                     int64_t style)
  : wxPanel(parent, id, pos, size, style) {
  sizer_ = new wxFlexGridSizer(0, 1, 0, 0);

  DoLayout();
  SetProperties();
}

void NavigationDrawer::AddItem(std::string text) {
  wxHyperlinkCtrl *link = new wxHyperlinkCtrl(this, wxID_ANY,
                                              _(text),
                                              wxEmptyString);
  sizer_->Add(link, 0, 0, 0);
}

void NavigationDrawer::SetProperties() {
  this->SetBackgroundColour(wxColour(210, 230, 239));
}

void NavigationDrawer::DoLayout() {
  AddItem("Details");
  AddItem("External");
  this->SetSizer(sizer_);
  Layout();
}
