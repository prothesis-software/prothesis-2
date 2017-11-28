#ifndef PANELS_DETAILS_PANEL_HPP_
#define PANELS_DETAILS_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <wx/utils.h>
#include <memory>

#include "src/data_panel.hpp"


class DetailsPanel : public DataPanel {
 public:
  DetailsPanel(wxWindow *parent,
               wxWindowID id,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               int64_t style = 0);
  ~DetailsPanel();

  void OnButtonNextClick(wxCommandEvent &event);  // NOLINT
  virtual bool SetGuiState(std::shared_ptr<cpptoml::table> state);
  virtual std::shared_ptr<cpptoml::base> GetUserState();
  virtual bool SetUserState(std::shared_ptr<cpptoml::table> state);

 private:
  void SetProperties();
  void DoLayout();

 protected:
  wxTextCtrl *text_ctrl_name_;
  wxTextCtrl *text_ctrl_surname_;
  wxSpinCtrl *spin_ctrl_age_;
  wxDatePickerCtrl *datepicker_ctrl_;
  wxButton *button_next_;

  enum {
    kButtonNextId = wxID_ANY
  };

  DECLARE_EVENT_TABLE()
};

#endif  // PANELS_DETAILS_PANEL_HPP_
