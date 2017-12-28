#include "navigation_drawer.hpp"

#include <string>

NavigationDrawer::NavigationDrawer(wxWindow* parent,
                                   wxWindowID id,
                                   const wxPoint& pos,
                                   const wxSize& size,
                                   int64_t style)
  : wxPanel(parent, id, pos, size, style) {
  sizer_ = new wxGridSizer(0, 1, 0, 0);
  SetProperties();
  DoLayout();
}

void NavigationDrawer::SetProperties() {
  // void
}

void NavigationDrawer::OnItemClick(wxCommandEvent &event) {
  NavigationItem *item = static_cast<NavigationItem*>(event.GetEventObject());
  MainFrame *main_frame = static_cast<MainFrame*>(wxTheApp->GetTopWindow());

  main_frame->DisplayPanelById(item->GetTarget());
}

void NavigationDrawer::AddItem(std::string label, DataManager::PanelId target) {
  NavigationItem *btn = new NavigationItem(this, wxID_ANY, _(label), target);
  sizer_->Add(btn, 1, wxEXPAND, 0);
  btn->Bind(wxEVT_BUTTON, &NavigationDrawer::OnItemClick, this);
}

void NavigationDrawer::DoLayout() {
  wxLogDebug("NavigationDrawer::DoLayout() START");
  AddItem("Details", DataManager::PanelId::kDetailsPanel);
  AddItem("Passions", DataManager::PanelId::kPassionPanel);
  AddItem("Dreams", DataManager::PanelId::kDreamsPanel);
  AddItem("People ID", DataManager::PanelId::kPeopleIdPanel);
  AddItem("Values", DataManager::PanelId::kValuesPanel);
  AddItem("Spoken Words", DataManager::PanelId::kSpokenWordsPanel);
  this->SetSizer(sizer_);
  Layout();
  wxLogDebug("NavigationDrawer::DoLayout() END");
}
