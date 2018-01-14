#ifndef THEME_PANEL_HPP_
#define THEME_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/gbsizer.h>

#include <memory>
#include <string>
#include <vector>

#include "data_panel.hpp"

#include "coloured_button.hpp"

class ThemePanel : public DataPanel {
 public:
  ThemePanel(wxWindow* parent, wxWindowID id, std::string panel_name,
             std::string panel_title, const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~ThemePanel();

  /**
   * Not used.
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML SPEC:
   * [panel_name]
   *   what = "lol"
   *   how = "cat"
   *   principle = "dog"
   *   rgb = 1285223
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML SPEC:
   *   Same as GetUserState();
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

  ColouredButton* GetButton();

  wxColour GetColour();
  void SetColour(wxColour);

 private:
  void DoLayout();
  wxTextCtrl* text_what_ = NULL;
  wxTextCtrl* text_how_ = NULL;
  wxTextCtrl* text_principle_ = NULL;
  const wxSize kTextBoxSize = wxSize(400, 50);
  ColouredButton* button_ = NULL;
  wxColour colour_;
  wxStaticText* label_title_ = NULL;
};

#endif  // THEME_PANEL_HPP_
