#ifndef DATA_PANEL_HPP_
#define DATA_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <memory>
#include "include/cpptoml.h"


/**
 * Base class for all custom panels that store user data
 */
class DataPanel : public wxPanel {
 public:
  DataPanel(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int64_t style = 0);

  /**
   * Generate the GUI elements from a TOML config
   */
  virtual bool SetGuiState(std::shared_ptr<cpptoml::table> state) = 0;

  /**
   * Return the user data as a TOML config
   */
  virtual std::shared_ptr<cpptoml::table> GetUserState() = 0;

  /**
   * Populate the GUI with the user TOML config.
   * SetGUIState() needs to be called before SetUserState()
   */
  virtual bool SetUserState(std::shared_ptr<cpptoml::table> state) = 0;
};

#endif  // DATA_PANEL_HPP_
