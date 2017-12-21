#include "navigation_drawer.hpp"
#include <wx/hyperlink.h>
#include <wx/dataview.h>

#include <string>

#include "data_manager.hpp"
#include "navigation_link.hpp"
#include "main_frame.hpp"

NavigationDrawer::NavigationDrawer(wxWindow* parent,
                     wxWindowID id,
                     const wxPoint& pos,
                     const wxSize& size,
                     int64_t style)
  : wxPanel(parent, id, pos, size, style) {
  sizer_ = new wxFlexGridSizer(0, 1, 0, 0);
  tree_ = new wxDataViewTreeCtrl(this, wxID_ANY);
  DoLayout();
  SetProperties();
}

void NavigationDrawer::OnLinkClick(wxCommandEvent &event) {
  MainFrame *main_frame = static_cast<MainFrame *>(wxTheApp->GetTopWindow());
  NavigationLink *link = static_cast<NavigationLink *>(event.GetEventObject());
  main_frame->DisplayPanelById(link->GetTarget());
}

void NavigationDrawer::AddItem(std::string text,
                               DataManager::PanelId target) {
  // NavigationLink *link = new NavigationLink(this, wxID_ANY,
  //                                              _(text),
  //                                              target);
  // sizer_->Add(link, 0, 0, 0);
  // link->Bind(wxEVT_HYPERLINK, &NavigationDrawer::OnLinkClick, this);
  wxDataViewItem *root = new wxDataViewItem(NULL);
  tree_->AppendItem(*root, _("AAAAAAAAAAAAAAAAAAAAAAA"));
}

void NavigationDrawer::SetProperties() {
  this->SetBackgroundColour(wxColour(210, 230, 239));
}

void NavigationDrawer::DoLayout() {
  AddItem("Details", DataManager::PanelId::kDetailsPanel);
  AddItem("Passion----------------------", DataManager::PanelId::kPassionPanel);

  sizer_->Add(tree_, 1, wxEXPAND, 0);
  this->SetSizer(sizer_);
  sizer_->SetMinSize(tree_->GetBestSize());
  Fit();
  Layout();
}
