#include "welcome_frame.hpp"

WelcomeFrame::WelcomeFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame((wxFrame *) NULL, -1, title, pos, size) {

  btnClose = new wxButton(this, btnCloseId, _T("Close"),
			  wxDefaultPosition, wxDefaultSize, 0);
  
  sizerA = new wxBoxSizer(wxHORIZONTAL);
  sizerA->Add(btnClose, 0, wxALIGN_CENTER, 0);

  wxBoxSizer *sizerB = new wxBoxSizer(wxVERTICAL);
  sizerB->Add(sizerA, 1, wxALIGN_CENTER, 0);
  
  SetSizerAndFit(sizerB);

}

void WelcomeFrame::OnExit(wxCommandEvent& event) {
  std::cout << "Bye" << std::endl;
  Close(TRUE);
}

// Needs to be declared in .cpp
BEGIN_EVENT_TABLE (WelcomeFrame, wxFrame)
EVT_BUTTON (btnCloseId, WelcomeFrame::OnExit ) // Tell the OS to run MainFrame::OnExit when
END_EVENT_TABLE() // The button is pressed
 
