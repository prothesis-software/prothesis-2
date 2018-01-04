#include "paged_panel.hpp"
#include <wx/simplebook.h>

#include <string>
#include <memory>
#include <vector>

#include "main_frame.hpp"

PagedPanel::PagedPanel(wxWindow* parent,
             wxWindowID id,
             std::string panel_name,
             std::string panel_title,
             const wxPoint& pos,
             const wxSize& size,
             int64_t style)
  : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  panel_page_numbers_ = new wxPanel(this, wxID_ANY);
  sizer_paged_panel_ = new wxFlexGridSizer(4, 3, 0, 0);
  simple_book_ = new wxSimplebook(this, wxID_ANY);
}

void PagedPanel::AddPage(wxPanel *panel) {
  panels_.push_back(panel);
  panel->Reparent(simple_book_);
  // TODO(egeldenuys): lolwat? can't remember the purpose.
  simple_book_->AddPage(panel, "LOLWAT");
}

// TODO(egeldenhuys): Rename to GenerateLinks
void PagedPanel::Init() {
  wxLogDebug("PagedPanel::Init() START");

  if (panels_.size() == 0) {
    wxLogDebug("Nothing to display");
    return;
  }

  for (size_t i = 0; i < panels_.size(); i++) {
    wxHyperlinkCtrl *link = new wxHyperlinkCtrl(panel_page_numbers_, wxID_ANY,
                                                _(std::to_string(i + 1)),
                                                wxEmptyString);
    link->Bind(wxEVT_HYPERLINK, &PagedPanel::OnHyperlinkClick, this);
    hyperlinks_.push_back(link);
  }

  DoLayout();
  SetProperties();
  DisplayPage(0);
  wxLogDebug("PagedPanel::Init() END");
}

PagedPanel::~PagedPanel() {
  // wxLogDebug("PagedPanel::~PagedPanel()");
}

bool PagedPanel::Next() {
  return DisplayNextPage();
}

bool PagedPanel::DisplayNextPage() {
  if (active_panel_index_ + 1 < panels_.size()) {
    DisplayPage(++active_panel_index_);
    return true;
  } else {
    return false;
  }
  return true;
}

size_t PagedPanel::GetPageCount() {
  return panels_.size();
}

void PagedPanel::DisplayPage(size_t index) {
  wxLogDebug("PagedPanel::DisplayPanel() START");

  simple_book_->SetSelection(index);
  active_panel_index_ = index;
  Layout();
  wxLogDebug("PagedPanel::DisplayPanel() END");
}

// TODO(egeldenhuys): Error handling for int <-> string conversions
void PagedPanel::OnHyperlinkClick(wxHyperlinkEvent &event) {
  wxLogDebug("PagedPanel::OnHyperlinkClick() START");

  wxHyperlinkCtrl *link = static_cast<wxHyperlinkCtrl*>(event.GetEventObject());
  wxString wxStr = link->GetLabel();
  std::string str = wxStr.ToStdString();
  size_t index = std::stoi(str) - 1;

  DisplayPage(index);
  wxLogDebug("PagedPanel::OnHyperlinkClick() END");
}

void PagedPanel::SetProperties() {
  for (size_t i = 0; i < hyperlinks_.size(); i++) {
    hyperlinks_.at(i)->SetMinSize(wxSize(35, -1));
  }
}

void PagedPanel::DoLayout() {
  // begin wxGlade: MainFrame::do_layout
  wxFlexGridSizer* sizer_page_numbers =
    new wxFlexGridSizer(1, hyperlinks_.size() + 2, 0, 0);

  // Page numbers panel
  // Add col for spacing
  sizer_page_numbers->Add(0, 0, 0, 0, 0);

  // Add hyperlinks
  for (size_t i = 0; i < hyperlinks_.size(); i++) {
    sizer_page_numbers->Add(hyperlinks_.at(i), 0, 0, 0);
  }

  // Spacing col
  sizer_page_numbers->Add(0, 0, 0, 0, 0);

  sizer_page_numbers->AddGrowableCol(0);
  sizer_page_numbers->AddGrowableCol(hyperlinks_.size() + 1);
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
