#include "main_frame.hpp"

MainFrame::MainFrame(const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size)
  : wxFrame(reinterpret_cast<wxFrame*>(NULL), -1, title, pos, size) {
  // TODO(egeldenhuys) add content here
}
