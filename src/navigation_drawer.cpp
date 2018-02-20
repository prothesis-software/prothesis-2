#include "navigation_drawer.hpp"

#include <string>

NavigationDrawer::NavigationDrawer(wxWindow* parent, wxWindowID id,
                                   const wxPoint& pos, const wxSize& size,
                                   int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  sizer_ = new wxGridSizer(0, 1, 0, 0);
  SetProperties();
  DoLayout();
}

void NavigationDrawer::SetProperties() {
  // void
}

void NavigationDrawer::OnItemClick(wxCommandEvent& event) {
  NavigationItem* item = static_cast<NavigationItem*>(event.GetEventObject());
  // MainFrame *main_frame = static_cast<MainFrame*>(wxTheApp->GetTopWindow());

  // \note triggers for clicking on nav buttons
  if (item->GetTarget() == DataManager::kWorkEnvironmentPanel) {
    wxLogDebug(_("Trigger for WorkEnvironmentPanel in ") +
               _("NavigationDrawer::OnItemClick()"));
    DataPanel* target = item->GetTargetPanel();
    if (target) {
      target->GetUserState();
    }
  }

  // main_frame->DisplayPanelById(item->GetTarget());
}

void NavigationDrawer::AddItem(std::string label, DataManager::PanelId target,
                               DataPanel* target_panel) {
  NavigationItem* btn =
      new NavigationItem(this, wxID_ANY, _(label), target, target_panel);
  sizer_->Add(btn, 1, wxEXPAND, 0);
  btn->Bind(wxEVT_BUTTON, &NavigationDrawer::OnItemClick, this);
}

void NavigationDrawer::DoLayout() {
  wxLogDebug("NavigationDrawer::DoLayout() START");
  this->SetSizer(sizer_);
  Layout();
  wxLogDebug("NavigationDrawer::DoLayout() END");
}
