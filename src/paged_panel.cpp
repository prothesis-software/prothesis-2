#include "paged_panel.hpp"
#include <wx/simplebook.h>

#include <memory>
#include <string>
#include <vector>

PagedPanel::PagedPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                       std::string panel_title, const wxPoint& pos,
                       const wxSize& size, int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  panel_page_numbers_ = new wxPanel(this, wxID_ANY);
  sizer_paged_panel_ = new wxFlexGridSizer(4, 3, 0, 0);
// i
#ifdef __APPLE__
  simple_book_ = new wxNotebook(this, wxID_ANY);
#else
  simple_book_ = new wxSimplebook(this, wxID_ANY);
#endif
}

void PagedPanel::AddPage(wxPanel* panel) {
  panels_.push_back(panel);
  panel->Reparent(simple_book_);
  // TODO(egeldenuys): lolwat? can't remember the purpose.
  simple_book_->AddPage(
      panel, std::to_string(panels_.size()));  // Convert the panel number to a
                                               // string and push this here.
  // shouldn't have any effect on linux
}

// TODO(egeldenhuys): Rename to GenerateLinks
void PagedPanel::Init() {
  wxLogDebug("PagedPanel::Init() START");
  if (panels_.size() == 0) {
    wxLogDebug("Nothing to display");
    return;
  }

#ifndef __APPLE__
  for (size_t i = 0; i < panels_.size(); i++) {
    wxButton* page_item =
        new wxButton(panel_page_numbers_, wxID_ANY, _(std::to_string(i + 1)),
                     wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    page_item->Bind(wxEVT_BUTTON, &PagedPanel::OnPageClick, this);
    page_items_.push_back(page_item);
  }
#endif
  DoLayout();
  DisplayPage(0);
  wxLogDebug("PagedPanel::Init() END");
}

PagedPanel::~PagedPanel() {
  // void
}

bool PagedPanel::Next() { return DisplayNextPage(); }

bool PagedPanel::DisplayNextPage() {
  if (active_panel_index_ + 1 < panels_.size()) {
    DisplayPage(++active_panel_index_);
    return true;
  } else {
    return false;
  }

  return false;
}

size_t PagedPanel::GetPageCount() { return panels_.size(); }

void PagedPanel::DisplayPage(size_t index) {
  wxLogDebug("PagedPanel::DisplayPanel() START");

  simple_book_->SetSelection(index);
  active_panel_index_ = index;
// n
#ifndef __APPLE__
  std::cout << "This shouldn't run" << std::endl;
  for (size_t i = 0; i < page_items_.size(); i++) {
    if (i != index) {
      wxColour default_colour =
          wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT);
      page_items_.at(i)->SetForegroundColour(default_colour);
    }
  }

  page_items_.at(index)->SetForegroundColour(wxColour(255, 0, 0));
#endif
  Layout();
  wxLogDebug("PagedPanel::DisplayPanel() END");
}

void PagedPanel::OnPageClick(wxCommandEvent& event) {
  wxLogDebug("PagedPanel::OnPageClick() START");

  wxButton* page_item = static_cast<wxButton*>(event.GetEventObject());
  wxString wxStr = page_item->GetLabel();
  std::string str = wxStr.ToStdString();
  size_t index = std::stoi(str) - 1;

  DisplayPage(index);
  wxLogDebug("PagedPanel::OnHyperlinkClick() END");
}

void PagedPanel::DoLayout() {
  // begin wxGlade: MainFrame::do_layout
  wxFlexGridSizer* sizer_page_numbers =
      new wxFlexGridSizer(1, page_items_.size() + 2, 0, 5);

  // Page numbers panel
  // Add col for spacing
  sizer_page_numbers->Add(0, 0, 0, 0, 0);

  // Add hyperlinks
// n
#ifndef __APPLE___
  for (size_t i = 0; i < page_items_.size(); i++) {
    sizer_page_numbers->Add(page_items_.at(i), 0, 0, 0);
    // page_items_.at(i)->SetMinSize(wxSize(35, -1));
  }
#endif

  // Spacing col
  sizer_page_numbers->Add(0, 0, 0, 0, 0);

  sizer_page_numbers->AddGrowableCol(0);
  sizer_page_numbers->AddGrowableCol(page_items_.size() + 1);
  panel_page_numbers_->SetSizer(sizer_page_numbers);

  // Page number panel to main sizer
  // Add col for spacing
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);
  sizer_paged_panel_->Add(panel_page_numbers_, 1, wxEXPAND, 0);
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);

  // line
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);
  wxStaticLine* static_line_1 = new wxStaticLine(this, wxID_ANY);
  sizer_paged_panel_->Add(static_line_1, 1, wxEXPAND, 0);
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);

  // content
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);
  // sizer_paged_panel_->Add(0, 0, 0, 0, 0);  // index 7
  sizer_paged_panel_->Add(simple_book_, 0, wxEXPAND, 0);
  sizer_paged_panel_->Add(0, 0, 0, 0, 0);

  // Footer
  sizer_paged_panel_->Add(0, 0, 0, 0);
  sizer_paged_panel_->Add(0, 0, 0, 0);
  sizer_paged_panel_->Add(0, 0, 0, 0);

  SetSizer(sizer_paged_panel_);
  sizer_paged_panel_->AddGrowableCol(1);
  sizer_paged_panel_->AddGrowableRow(2);

  sizer_paged_panel_->Fit(this);
  Layout();
  // end wxGlade
}
