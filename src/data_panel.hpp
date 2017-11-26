#ifndef DATA_PANEL_HPP_
#define DATA_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <memory>

#include "include/cpptoml.h"

/**
 * Abstract base class for panels with an associated state.
 * All panels should inherit from this class.
 */
class DataPanel : public wxPanel {
 public:
  DataPanel(wxWindow* parent,
            wxWindowID id,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int64_t style = 0);

  /**
   * Generate the GUI elements given a toml config
   */
  virtual bool SetGuiState(std::shared_ptr<cpptoml::table> state) = 0;
  /**
   * Get the toml state from the data the user provided
   */
  virtual std::shared_ptr<cpptoml::table> GetUserState() = 0;
  /**
   * Set the user state after the GUI has been generated from a toml config
   */
  virtual bool SetUserState(std::shared_ptr<cpptoml::table> state) = 0;
};

#endif  // DATA_PANEL_HPP_
