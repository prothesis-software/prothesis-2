#ifndef COLOURED_BUTTON_HPP_
#define COLOURED_BUTTON_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

/**
 * Class used for simulate a coloured button.
 * Is actually a panel with a button in the middle.
 */
class ColouredButton : public wxPanel {
 public:
  ColouredButton(wxWindow* parent, wxWindowID id, std::string label,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~ColouredButton();

  wxButton* GetButton();
  void SetColour(wxColour colour);
  wxColour GetColour();
  std::string GetButtonLabel();

 private:
  void DoLayout();
  wxButton* button_ = NULL;
  wxColour colour_;
};

#endif  // COLOURED_BUTTON_HPP_
