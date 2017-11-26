#ifndef PANELS_DETAILS_PANEL_HPP_
#define PANELS_DETAILS_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <memory>

#include "src/data_panel.hpp"

class DetailsPanel : public DataPanel {
 public:
  DetailsPanel(wxWindow *parent,
               wxWindowID id,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               int64_t style = 0);
  void ButtonNextOnClick(wxCommandEvent &event);  // NOLINT
  ~DetailsPanel();

  /**
   * Generate the GUI elements given a toml config
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state);

  /**
   * Get the toml state from the data the user provided
   */
  std::shared_ptr<cpptoml::table> GetUserState();

  /**
   * Set the user state after the GUI has been generated from a toml config
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state);

 private:
  // begin wxGlade: DetailsPanel::methods
  void set_properties();
  void do_layout();
  // end wxGlade

 protected:
  // begin wxGlade: DetailsPanel::attributes
  wxTextCtrl* text_ctrl_name;
  wxTextCtrl* text_ctrl_surname;
  wxSpinCtrl* spin_ctrl_age;
  wxDatePickerCtrl* datepicker_ctrl_1;
  wxButton* button_next;
  // end wxGlade

  DECLARE_EVENT_TABLE()
};

#endif  // PANELS_DETAILS_PANEL_HPP_
