#ifndef ABOUT_FRAME_HPP_
#define ABOUT_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/hyperlink.h>
#include <wx/statline.h>

#include <string>

class AboutFrame : public wxDialog {
 public:
  AboutFrame(wxWindow* parent, wxWindowID id, const wxString& title,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             int64_t style = wxDEFAULT_FRAME_STYLE,
             const wxString name = wxFrameNameStr);
  ~AboutFrame();

 private:
  void AddHyperlink(wxSizer* sizer, wxWindow* parent, std::string label,
                    std::string url);
  void OnButtonCloseClick(wxCommandEvent& event);  // NOLINT

  void DoLayout();
};

#endif  // ABOUT_FRAME_HPP_
