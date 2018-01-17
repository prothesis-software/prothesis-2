#ifndef MBTI_PANEL_HPP_
#define MBTI_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

class MbtiPanel : public wxPanel {
 public:
  MbtiPanel(wxWindow* parent, wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~MbtiPanel();

  void SetMbti(std::string mbti);
  std::string GetMbti();

 private:
  void DoLayout();
  std::string mbti_;
  wxStaticText* label_mbti_ = NULL;
};
#endif  // MBTI_PANEL_HPP_
