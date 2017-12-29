#ifndef CHECKBOX_PANEL_HPP_
#define CHECKBOX_PANEL_HPP_

#include <wx/checkbox.h>

#include <memory>
#include <string>
#include <vector>

#include "data_panel.hpp"

class CheckBoxPanel : public DataPanel {
 public:
  CheckBoxPanel(wxWindow* parent,
            wxWindowID id,
            std::string panel_name,
            std::string panel_title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int64_t style = 0);
  ~CheckBoxPanel();

  /**
   * TOML Specification for Setting the GUI State
   *
   * [panel_name]
   *     checked = ["Cats", "Dogs", "Rabbits"]
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification for Getting the User state:
   *
   * [panel_name]
   *     options = ["Cats", "Dogs", "Rabbits", "Krokodile"]
   *     limit = 3
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML Specification is the same as for GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void SetProperties();
  void DoLayout();
  void SetCheckboxStateByLabel(std::string label, bool checked);

  /**
   * Create a new checkbox (unchecked) and add it to the panel
   */
  void AddCheckBox(std::string label);

  std::vector<wxCheckBox> checkboxes_;
};

#endif  // CHECKBOX_PANEL_HPP_
