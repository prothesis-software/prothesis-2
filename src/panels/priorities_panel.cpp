#include "priorities_panel.hpp"

#include <memory>
#include <string>

PrioritiesPanel::PrioritiesPanel(wxWindow *parent,
                           wxWindowID id,
                           std::string panel_name,
                           std::string panel_title,
                           const wxPoint &pos,
                           const wxSize &size,
                                 int64_t style)
  : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  list_unsorted_1_ = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                   wxSize(-1, -1), 0, NULL,
                                   wxLB_SINGLE);
  unsorted_lists_[0] = list_unsorted_1_;

  list_unsorted_2_ = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                   wxSize(-1, -1), 0, NULL,
                                   wxLB_SINGLE);
  unsorted_lists_[1] = list_unsorted_2_;

  list_sorted_ = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                               wxSize(-1, -1), 0, NULL, wxLB_SINGLE);
  DoLayout();
}

PrioritiesPanel::~PrioritiesPanel() {
  // void
}

int PrioritiesPanel::GetItemHeight(wxListBox *list) {
  wxLogDebug("Finding item height...");

  wxLogDebug(_("Original: ") +
             _(std::to_string(list->GetBestHeight(-1))));

  // Add items until we start increasing in size
  int best_height = list->GetBestHeight(-1);
  size_t count = 15;

  while (best_height == list->GetBestHeight(-1) && count > 0) {
    list->InsertItems(1, new wxString("test_item"), 0);
    count--;
  }
  int initial_height = list->GetBestHeight(-1);

  wxLogDebug(_("initial: ") +
             _(std::to_string(initial_height)));
  list->InsertItems(1, new wxString("test_item"), 0);

  int final_height = list->GetBestHeight(-1);
  wxLogDebug(_("final: ") +
             _(std::to_string(final_height)));

  int delta = final_height - initial_height;
  wxLogDebug(_("delta: ") +
             _(std::to_string(delta)));

  if (delta <= 0) {
    wxLogWarning("Could not calculate the height of a wxListBox item!");
  }

  list->Clear();

  // To correct for errors
  return delta + 1;
}

void PrioritiesPanel::SetBestListHeight(wxListBox *list) {
  int best = (list->GetCount() + 1) * item_height_;
  list->SetMinSize(wxSize(-1, best));
}

void PrioritiesPanel::AddUnsortedPriority(std::string priority) {
  // Get list with least items

  wxListBox *best_list = unsorted_lists_[0];
  size_t least_items = unsorted_lists_[0]->GetCount();

  for (size_t i = 1; i < 2; i++) {
    size_t items = unsorted_lists_[i]->GetCount();
    if (items < least_items) {
      least_items = items;
      best_list = unsorted_lists_[i];
    }
  }

  best_list->InsertItems(1, new wxString(priority), 0);
}

bool PrioritiesPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  // Get root table from state
  if (panel_table) {
    auto priorities_array = panel_table->get_array_of<std::string>("options");

    if (priorities_array) {
      for (const auto& priority_string : *priorities_array) {
        AddUnsortedPriority(priority_string);
      }
      SetBestListHeight(unsorted_lists_[0]);
      // GetSize() does not seem to return the actual size,
      // so these hacks are used.
      unsorted_lists_[1]->SetMinSize(unsorted_lists_[0]->GetSize());
      list_sorted_->SetMinSize(wxSize(unsorted_lists_[0]->GetBestWidth(-1),
                                      unsorted_lists_[0]->GetMinSize().y));
    } else {
      wxLogDebug("Key 'options' was not found for panel Priorities.");
    }
  } else {
    wxLogDebug(_("No GUI table exists for panel ") + _(this->GetPanelName()));
    return false;
  }  // panel_table

return true;
}

std::shared_ptr<cpptoml::table> PrioritiesPanel::GetUserState() {
  return NULL;
}

bool PrioritiesPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  return false;
}

void PrioritiesPanel::DoLayout() {
  wxFlexGridSizer *sizer = new wxFlexGridSizer(1, 3, 0, 0);

  // Sorted
  wxBoxSizer *sizer_sorted = new wxBoxSizer(wxVERTICAL);
  wxStaticText *label_sorted = new wxStaticText(this, wxID_ANY,
                                                _("Sorted Priorities"));
  sizer_sorted->Add(label_sorted, 0, 0, 0);
  sizer_sorted->Add(list_sorted_, 0, 0, 0);
  item_height_ = GetItemHeight(list_sorted_);

  sizer->Add(sizer_sorted, 0, 0, 0);

  // Controls
  wxBoxSizer *sizer_controls = new wxBoxSizer(wxVERTICAL);
  wxButton *button_add_sorted = new wxButton(this, wxID_ANY,
                                             _("<- Add to sorted"));
  wxButton *button_remove_sorted = new wxButton(this, wxID_ANY,
                                                _("-> Remove from sorted"));
  sizer_controls->Add(button_add_sorted, 0, wxEXPAND, 0);
  sizer_controls->Add(button_remove_sorted, 0, wxEXPAND, 0);

  sizer->Add(sizer_controls, 0, 0, 0);

  // Unsorted
  wxBoxSizer *sizer_unsorted = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizer_unsorted_lists = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *label_unsorted = new wxStaticText(this, wxID_ANY,
                                                _("Priorities to select from"));
  sizer_unsorted->Add(label_unsorted, 0, 0, 0);
  sizer_unsorted_lists->Add(list_unsorted_1_, 1, wxEXPAND, 0);
  sizer_unsorted_lists->Add(list_unsorted_2_, 1, wxEXPAND, 0);
  sizer_unsorted->Add(sizer_unsorted_lists, 0, 0, 0);

  sizer->Add(sizer_unsorted, 0, 0, 0);
  this->SetSizer(sizer);
  Layout();
}
