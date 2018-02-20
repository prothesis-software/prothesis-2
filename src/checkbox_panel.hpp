#ifndef CHECKBOX_PANEL_HPP_
#define CHECKBOX_PANEL_HPP_
#define MAX_ITEMS 10
#define MAX_CHECKED_ITEMS 7

#include <wx/checkbox.h>

#include <memory>
#include <string>
#include <vector>

#include "data_panel.hpp"

class CheckBoxPanel : public DataPanel {
 public:
  CheckBoxPanel(wxWindow* parent, wxWindowID id, std::string panel_name,
                std::string panel_title, const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize, int64_t style = 0);
  ~CheckBoxPanel();

  /**
   * TOML Specification for Setting the GUI State
   *
   * [panel_name]
   *   [[panel_name.question]]
   *     question = "Example"
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification for Getting the User state:
   *
   * [panel_name]
   *   [[panel_name.question]]
   *     question = "Example"
   *    checked = "true"
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  std::vector<std::string> GetCheckedItems();

  /**
   * TOML Specification is the same as for GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();
  void SetCheckboxStateByLabel(std::string label, bool checked);
  void OnCheckBoxListSelectionChange(wxCommandEvent& event);  // NOLINT
  void OnCheckBoxChange(wxCommandEvent& event);               // NOLINT
  int checked_item_count_ = 0;
  wxStaticText* label_limit_ = NULL;

  /**
   * Create a new checkbox (unchecked) and add it to the panel
   */
  void AddCheckBox(std::string label);

  std::vector<wxCheckBox> checkboxes_;
  wxCheckListBox* list_box_a_;
  wxCheckListBox* list_box_b_;
  wxCheckListBox* list_box_c_;
  wxCheckListBox* boxes_[3];
};

#endif  // CHECKBOX_PANEL_HPP_
