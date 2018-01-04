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
  list_unsorted_1_->Bind(wxEVT_LISTBOX,
                         &PrioritiesPanel::OnUnsortedListBoxSelectionChange,
                         this);
  unsorted_lists_[0] = list_unsorted_1_;

  list_unsorted_2_ = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                   wxSize(-1, -1), 0, NULL,
                                   wxLB_SINGLE);
  list_unsorted_2_->Bind(wxEVT_LISTBOX,
                         &PrioritiesPanel::OnUnsortedListBoxSelectionChange,
                         this);
  unsorted_lists_[1] = list_unsorted_2_;

  list_sorted_ = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                               wxSize(-1, -1), 0, NULL, wxLB_SINGLE);
  DoLayout();
}

PrioritiesPanel::~PrioritiesPanel() {
  wxLogDebug("PrioritiesPanel::~PrioritiesPanel()");
}

void PrioritiesPanel::GetItemHeight(wxListBox *list) {
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

  // +1 To correct for errors
  item_height_ = delta + 1;
}

void PrioritiesPanel::SetBestListHeight(wxListBox *list) {
  int best = (list->GetCount() + 1) * item_height_;
  list->SetMinSize(wxSize(-1, best));
}

void PrioritiesPanel::AddUnsortedPriority(std::string priority) {
  wxListBox *best_list = unsorted_lists_[0];
  size_t least_items = unsorted_lists_[0]->GetCount();

  for (size_t i = 1; i < 2; i++) {
    size_t items = unsorted_lists_[i]->GetCount();
    if (items < least_items) {
      least_items = items;
      best_list = unsorted_lists_[i];
    }
  }

  best_list->InsertItems(1, new wxString(priority), best_list->GetCount());
}

void PrioritiesPanel::OnButtonRemoveClick(wxCommandEvent &event) {
  int index = list_sorted_->GetSelection();

  if (index != wxNOT_FOUND) {
    wxString item = list_sorted_->GetString(index);
    RemoveItemFromListBox(list_sorted_, index);
    AddUnsortedPriority(item.ToStdString());
  }
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
  size_t count = list_sorted_->GetCount();

  auto panel_table = cpptoml::make_table();
  auto priorities_array = cpptoml::make_array();

  for (size_t i = 0; i < count; i++) {
    priorities_array->push_back(list_sorted_->GetString(i).ToStdString());
  }

  panel_table->insert("options", priorities_array);
  return panel_table;
}


bool PrioritiesPanel::SetUserState(std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());
  if (panel_table) {
    auto priorities_array = panel_table->get_array_of<std::string>("options");

    if (priorities_array) {
      for (const auto &item : *priorities_array) {
        if (!MoveItemToSorted(item)) {
          wxLogWarning(_("Could not move item ") +
                       _(item) +
                       _(" to the sorted list"));
        }
      }
    } else {
      wxLogDebug(_("options does not exist for table ") +
                 _(this->GetPanelName()));
      return false;
    }
  } else {
    wxLogDebug(_("No GUI table exists for panel ") + _(this->GetPanelName()));
    return false;
  }

  return true;
}

void PrioritiesPanel::RemoveItemFromListBox(wxListBox *list_box, int index) {
  list_box->Freeze();
  wxArrayString items;

  int count = list_box->GetCount();
  for (int i = 0; i < count; i++) {
    if (i != index) {
      items.Add(list_box->GetString(i));
    }
  }

  list_box->Clear();
  if (items.Count() > 0) {
    list_box->InsertItems(items, 0);
  }
  list_box->Thaw();
}

bool PrioritiesPanel::MoveItemToSorted(std::string item) {
  wxString priority = wxString(item);

  for (size_t i = 0; i < 2; i++) {
    size_t count = unsorted_lists_[i]->GetCount();
    for (size_t j = 0; j < count; j++) {
      if (unsorted_lists_[i]->GetString(j).IsSameAs(priority)) {
        list_sorted_->InsertItems(1, new wxString(item),
                                  list_sorted_->GetCount());
        RemoveItemFromListBox(unsorted_lists_[i], j);
        return true;
      }
    }
  }

  return false;
}

bool PrioritiesPanel::AddSelectedItemToSorted() {
  wxListBox *list_box = NULL;
  int index = wxNOT_FOUND;

  if (list_unsorted_1_->GetSelection() != wxNOT_FOUND) {
    list_box = list_unsorted_1_;
  } else if (list_unsorted_2_->GetSelection() != wxNOT_FOUND) {
    list_box = list_unsorted_2_;
  }

  if (list_box != NULL) {
    index = list_box->GetSelection();
    if (index != wxNOT_FOUND) {
      wxString str = list_box->GetString(list_box->GetSelection());
      list_sorted_->InsertItems(1, new wxString(str), list_sorted_->GetCount());
      RemoveItemFromListBox(list_box, index);
      return true;
    }
  }
  return false;
}

void PrioritiesPanel::OnButtonAddClick(wxCommandEvent &event) {
  if (AddSelectedItemToSorted()) {
    list_sorted_->SetSelection(list_sorted_->GetCount() - 1);
  }
}

void PrioritiesPanel::ChangeOrder(int index, int shift) {
  if (index == wxNOT_FOUND) {
    return;
  }

  // Collect all items
  wxArrayString items;
  int count = list_sorted_->GetCount();

  for (int i = 0; i < count; i++) {
    items.Add(list_sorted_->GetString(i));
  }

  int new_index = index + shift;

  // Handle edges
  if (new_index == -1 || new_index == count) {
    return;
  }

  wxString tmp = items[index];
  items[index] = items[new_index];
  items[new_index] = tmp;

  list_sorted_->Freeze();

  list_sorted_->Clear();
  list_sorted_->InsertItems(items, 0);
  list_sorted_->SetSelection(new_index);

  list_sorted_->Thaw();
}

void PrioritiesPanel::OnUnsortedListBoxSelectionChange(wxCommandEvent &event) {
  wxListBox *list_box = static_cast<wxListBox*>(event.GetEventObject());

  if (list_box == list_unsorted_1_) {
    list_unsorted_2_->SetSelection(wxNOT_FOUND);
  } else {
    list_unsorted_1_->SetSelection(wxNOT_FOUND);
  }
}

void PrioritiesPanel::OnButtonMoveUpClick(wxCommandEvent &event) {
  ChangeOrder(list_sorted_->GetSelection(), -1);
}

void PrioritiesPanel::OnButtonMoveDownClick(wxCommandEvent &event) {
  ChangeOrder(list_sorted_->GetSelection(), 1);
}

void PrioritiesPanel::DoLayout() {
  wxFlexGridSizer *sizer = new wxFlexGridSizer(1, 3, 0, 0);

  // Sorted
  wxBoxSizer *sizer_sorted = new wxBoxSizer(wxVERTICAL);
  wxStaticText *label_sorted = new wxStaticText(this, wxID_ANY,
                                                _("Sorted Priorities"));
  sizer_sorted->Add(label_sorted, 0, wxALIGN_CENTER, 0);
  sizer_sorted->Add(list_sorted_, 0, 0, 0);
  GetItemHeight(list_sorted_);

  sizer->Add(sizer_sorted, 0, 0, 0);

  // Controls
  wxBoxSizer *sizer_controls_h = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *sizer_controls = new wxBoxSizer(wxVERTICAL);
  wxButton *button_add_sorted = new wxButton(this, wxID_ANY,
                                             _("Add to sorted"),
                                             wxDefaultPosition,
                                             wxDefaultSize, wxBU_LEFT);
  // Errors when not included here
#include "images/keyboard_arrow_left.xpm"
  button_add_sorted->SetBitmap(wxBitmap(keyboard_arrow_left));

  button_add_sorted->Bind(wxEVT_BUTTON,
                          &PrioritiesPanel::OnButtonAddClick,
                          this);
  wxButton *button_remove_sorted = new wxButton(this, wxID_ANY,
                                                _("Remove from sorted"),
                                                wxDefaultPosition,
                                                wxDefaultSize, wxBU_LEFT);
#include "images/keyboard_arrow_right.xpm"
  button_remove_sorted->SetBitmap(wxBitmap(keyboard_arrow_right));
  button_remove_sorted->Bind(wxEVT_BUTTON,
                             &PrioritiesPanel::OnButtonRemoveClick,
                             this);
  sizer_controls->Add(button_add_sorted, 0, wxEXPAND, 0);
  sizer_controls->Add(button_remove_sorted, 0, wxEXPAND, 0);
  sizer_controls->AddSpacer(10);

  wxButton *button_move_up = new wxButton(this, wxID_ANY,
                                          _("Move Up"), wxDefaultPosition,
                                          wxDefaultSize, wxBU_LEFT);
#include "images/keyboard_arrow_up.xpm"
  button_move_up->SetBitmap(wxBitmap(keyboard_arrow_up));
  button_move_up->SetBitmapPosition(wxLEFT);
  button_move_up->Bind(wxEVT_BUTTON,
                       &PrioritiesPanel::OnButtonMoveUpClick,
                       this);
  sizer_controls->Add(button_move_up, 0, wxEXPAND, 0);

    wxButton *button_move_down = new wxButton(this, wxID_ANY,
                                              _("Move Down"),
                                              wxDefaultPosition,
                                              wxDefaultSize, wxBU_LEFT);
#include "images/keyboard_arrow_down.xpm"
    button_move_down->SetBitmap(wxBitmap(keyboard_arrow_down));
    button_move_down->Bind(wxEVT_BUTTON,
                         &PrioritiesPanel::OnButtonMoveDownClick,
                       this);
  sizer_controls->Add(button_move_down, 0, wxEXPAND, 0);
  sizer_controls_h->Add(sizer_controls, 0, wxALIGN_CENTER, 0);
  sizer->Add(sizer_controls_h, 0, wxALIGN_CENTER, 0);

  // Required to center the controls sizer
  sizer->AddGrowableRow(0);
  sizer->AddGrowableCol(1);

  // Unsorted
  wxBoxSizer *sizer_unsorted = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *sizer_unsorted_lists = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *label_unsorted = new wxStaticText(this, wxID_ANY,
                                                _("Priorities to select from"));
  sizer_unsorted->Add(label_unsorted, 0, wxALIGN_CENTER, 0);
  sizer_unsorted_lists->Add(list_unsorted_1_, 1, wxEXPAND, 0);
  sizer_unsorted_lists->Add(list_unsorted_2_, 1, wxEXPAND, 0);
  sizer_unsorted->Add(sizer_unsorted_lists, 0, 0, 0);

  sizer->Add(sizer_unsorted, 0, 0, 0);
  this->SetSizer(sizer);
  Layout();
}
