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
  DoLayout();
}

PrioritiesPanel::~PrioritiesPanel() {
  // void
}

bool PrioritiesPanel::SetGuiState(std::shared_ptr<cpptoml::table> state) {
  return false;
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

  wxListBox *list_sorted = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                         wxDefaultSize, 0, NULL, wxLB_SINGLE);
  sizer_sorted->Add(list_sorted, 0, 0, 0);

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
  wxListBox *list_unsorted_1 = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                            wxDefaultSize, 0, NULL,
                                            wxLB_SINGLE);
  wxListBox *list_unsorted_2 = new wxListBox(this, wxID_ANY, wxDefaultPosition,
                                             wxDefaultSize, 0, NULL,
                                             wxLB_SINGLE);
  sizer_unsorted->Add(label_unsorted, 0, 0, 0);
  sizer_unsorted_lists->Add(list_unsorted_1, 0, 0, 0);
  sizer_unsorted_lists->Add(list_unsorted_2, 0, 0, 0);
  sizer_unsorted->Add(sizer_unsorted_lists, 0, 0, 0);

  sizer->Add(sizer_unsorted, 0, 0, 0);
  this->SetSizer(sizer);
  Layout();
}
