#ifndef DATA_PANEL_HPP_
#define DATA_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "include/cpptoml.h"

/**
 * Base class for all custom panels that store user data
 */
class DataPanel : public wxScrolled<wxPanel> {
 public:
  DataPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
            std::string panel_title, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, int64_t style = 0);

  /**
   * Generate the GUI elements from a TOML config
   */
  virtual bool SetGuiState(std::shared_ptr<cpptoml::table> state) = 0;

  /**
   * Return the user data as a TOML config.
   *
   * The returned config should be of the form:
   * [panel_name]
   *   key = value
   *
   *   [[panel_name.buttons]]
   *     key = value
   *   [[panel_name.buttons]]
   *     key = value
   */
  virtual std::shared_ptr<cpptoml::table> GetUserState() = 0;

  /**
   * Populate the GUI with the user TOML config.
   * SetGUIState() needs to be called before SetUserState()
   */
  virtual bool SetUserState(std::shared_ptr<cpptoml::table> state) = 0;

  std::string GetPanelName();
  std::string GetPanelTitle();
  DataPanel* GetPanelByName(std::string panel_name);

  static std::vector<DataPanel*> panels_;

  /**
   * Instruct the panel to display it's next page if suported.
   * Returns false if at end or not supported
   */
  virtual bool Next();

  /**
   * Called when the tab is activated in MainFrame
   */
  virtual void OnTabActivate();

 protected:
  std::string panel_name_;
  std::string panel_title_;
  void OnSizeChange(wxSizeEvent& event);  // NOLINT
};

#endif  // DATA_PANEL_HPP_
