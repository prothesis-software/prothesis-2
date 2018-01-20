#include "about_frame.hpp"

#include <string>

AboutFrame::AboutFrame(wxWindow* parent, wxWindowID id, const wxString& title,
                       const wxPoint& pos, const wxSize& size, int64_t style,
                       const wxString name)
    : wxDialog(parent, id, title, pos, size, style, name) {
  DoLayout();
}

AboutFrame::~AboutFrame() { wxLogDebug("FREE"); }

void AboutFrame::AddHyperlink(wxSizer* sizer, wxWindow* parent,
                              std::string label, std::string url) {
  wxHyperlinkCtrl* link = new wxHyperlinkCtrl(parent, wxID_ANY, label, url);
  sizer->Add(link, 0, 0, 0);
}

void AboutFrame::OnButtonCloseClick(wxCommandEvent& event) { this->Destroy(); }

void AboutFrame::DoLayout() {
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

  wxPanel* panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer* sizer_panel = new wxBoxSizer(wxVERTICAL);

#ifdef PROTHESIS_VERSION
  std::string version = PROTHESIS_VERSION;
#else
  std::string version = "<version>";
#endif

  wxStaticText* bin_info =
      new wxStaticText(panel, wxID_ANY, "Prothesis " + version);
  wxFont bin_info_font = bin_info->GetFont();
  bin_info_font.SetPointSize(17);
  bin_info->SetFont(bin_info_font);
  sizer_panel->Add(bin_info, 0, wxALL | wxALIGN_CENTER, 6);

  wxHyperlinkCtrl* link_source =
      new wxHyperlinkCtrl(panel, wxID_ANY, "prothesis-2 source code on GitHub",
                          "https://github.com/prothesis-software/prothesis-2");
  sizer_panel->Add(link_source, 0, wxALL | wxALIGN_CENTER, 6);
  wxStaticLine* static_line = new wxStaticLine(panel, wxID_ANY);

  sizer_panel->Add(static_line, 0, wxEXPAND, 0);

  wxBoxSizer* sizer_row_1 = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* sizer_links = new wxBoxSizer(wxVERTICAL);
  wxStaticText* label_dev = new wxStaticText(panel, wxID_ANY, "Developers:");
  label_dev->SetFont(label_dev->GetFont().MakeBold());

  sizer_links->Add(label_dev, 0, wxALL, 0);
  AddHyperlink(sizer_links, panel, "Charles de Villiers",
               "https://github.com/Camelghost");
  AddHyperlink(sizer_links, panel, "Armand du Plooy",
               "https://github.com/RagingGrim");
  AddHyperlink(sizer_links, panel, "Evert Geldenhuys",
               "https://github.com/egeldenhuys");
  AddHyperlink(sizer_links, panel, "Johan Nel", "https://github.com/Jtfnel");
  AddHyperlink(sizer_links, panel, "Thomas Scholtz",
               "https://github.com/Quantum-Sicarius");

  sizer_row_1->Add(sizer_links, 0, wxALL, 6);

  wxBoxSizer* sizer_third_party = new wxBoxSizer(wxVERTICAL);
  wxStaticText* label_third_party =
      new wxStaticText(panel, wxID_ANY, "Third-party projects used:");
  label_third_party->SetFont(label_third_party->GetFont().MakeBold());

  sizer_third_party->Add(label_third_party, 0, wxALL, 0);
  AddHyperlink(sizer_third_party, panel, "wxWidgets",
               "https://www.wxwidgets.org/");
  AddHyperlink(sizer_third_party, panel, "cpptoml",
               "https://github.com/skystrife/cpptoml");

  sizer_row_1->AddSpacer(20);
  sizer_row_1->Add(sizer_third_party, 0, wxALL | wxALIGN_RIGHT, 6);

  sizer_panel->Add(sizer_row_1);

  wxButton* button_close = new wxButton(panel, wxID_ANY, "Close");
  button_close->Bind(wxEVT_BUTTON, &AboutFrame::OnButtonCloseClick, this);

  sizer_panel->Add(button_close, 0, wxALIGN_CENTER | wxALL, 6);

  sizer->Add(sizer_panel);
  sizer->Fit(this);
  this->SetSizer(sizer);
  Layout();
  Fit();
}
