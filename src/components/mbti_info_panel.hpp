#ifndef COMPONENTS_MBTI_INFO_HPP_
#define COMPONENTS_MBTI_INFO_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/gbsizer.h>
#include <wx/statline.h>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "include/cpptoml.h"

#define DESC_1_WRAP_PX 300
#define DESC_2_WRAP_PX 300

class MbtiInfoPanel : public wxPanel {
 public:
  MbtiInfoPanel(wxWindow* parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~MbtiInfoPanel(){};

  struct MbtiInfo {
    std::vector<std::string> descriptions_1;
    std::vector<std::string> descriptions_2;
  };

  struct MbtiEntry {
    std::string key;
    std::string desc1;
    std::string desc2;
  };

  struct MbtiInfo GetMbtiInfo(std::string mbti);

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
  struct MbtiInfoPanel::MbtiEntry GetMbtiEntry(std::string key);
  std::vector<std::string> GetMbtiAsVector();
  std::string GetMbti();
  void SetMbti(std::vector<std::string> mbti);

 private:
  void OnMbtiChange(wxCommandEvent& event);  // NOLINT
  void DoLayout();
  std::string mbti_;
  std::vector<struct MbtiEntry> mbti_entries_;
  wxStaticText* labels_mbti_[4];
  wxStaticText* descriptions_1_[4];
  wxStaticText* descriptions_2_[3];
  wxGridBagSizer* sizer_ = NULL;
  wxChoice* choice_boxes_mbti_[4];
  wxStaticBoxSizer* sizer_root_ = NULL;
  void AddMbtiTuple(std::vector<wxArrayString>* source_vector, std::string str1,
                    std::string str2);
};

#endif  // COMPONENTS_MBTI_INFO_HPP_
