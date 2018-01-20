#ifndef COMPONENTS_MBTI_INFO_HPP_
#define COMPONENTS_MBTI_INFO_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "include/cpptoml.h"

class MbtiInfoPanel : public wxPanel {
 public:
  MbtiInfoPanel(wxWindow* parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~MbtiInfoPanel(){};

  /**
   * Example: SetMbti("ISTJ");
   */
  void SetMbti(std::string mbti);

  /**
   * TOML SPEC:
   * [mbti_info]
   *   [[mbti_info.type]]
   *     key = "I"
   *     description_1 = ""
   *     description_2 = ""
   *
   * Where description_1 will always exist.
   * description_2 is optional.
   */
  void SetMbtiInfoData(std::shared_ptr<cpptoml::table>(gui_state));
};

#endif  // COMPONENTS_MBTI_INFO_HPP_
