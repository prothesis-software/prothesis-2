#ifndef COLOURED_BUTTON_CONTAINER_HPP_
#define COLOURED_BUTTON_CONTAINER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <string>
#include <vector>

#include "coloured_button.hpp"
#include "data_panel.hpp"
#include "utilities.hpp"

class ColouredButtonContainer : public DataPanel {
 public:
  ColouredButtonContainer(wxWindow* parent, wxWindowID id,
                          std::string panel_name, std::string panel_title,
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxDefaultSize,
                          int64_t style = 0);
  ~ColouredButtonContainer();

  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML SPEC:
   * [panel_name]
   *   [[panel_name.item]]
   *     label = "label"
   *     r = 255
   *     g = 255
   *     b = 255
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * SetUserState should be called to create the buttons
   * from the previous save. The state will then be
   * synced with the external panels through the
   * ThemeAnalysisPanel.
   *
   * TOML SPEC:
   * The same as GetUserState
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * Add an existing ColouredButton
   */
  void AddItem(ColouredButton* item);

  /**
   * Add the item to the container by
   * creating ColouredButton object
   */
  ColouredButton* AddItem(std::string item);
  ColouredButton* AddItem(std::string label, wxUint32 rgb);

  /**
   * Remove the given item from the widget.
   * Does not destroy the item unless delete_item == true
   */
  bool RemoveItem(ColouredButton* item, bool delete_item = false);

  /**
   * Set items from the checkbox panels.
   * If the item already exists, it is ignored.
   * If the item does not exist, it is added.
   * Items not in the new list are deleted.
   */
  void UpdateItems(std::vector<std::string> items);

  /**
   * Return all the coloured buttons in this container
   */
  std::vector<ColouredButton*> GetColouredButtons();

 protected:
  wxBoxSizer* sizer_buttons_ = NULL;
  wxStaticBoxSizer* sizer_root_ = NULL;

 private:
  void PrintVector(std::vector<ColouredButton*> items);
  void PrintVector(std::vector<std::string> items);
  std::vector<std::string> RemoveDuplicates(std::vector<std::string> items);
  ColouredButton* GetItemByLabel(std::vector<ColouredButton*> buttons,
                                 std::string label);
  bool ContainsItem(std::vector<std::string> items, std::string item);
  bool ContainsItem(std::vector<ColouredButton*> buttons, std::string item);
  void GetItemDeltas(std::vector<std::string> new_items,
                     std::vector<ColouredButton*> existing_items,
                     std::vector<ColouredButton*>* only_in_existing,
                     std::vector<ColouredButton*>* in_new_and_existing);
  std::vector<ColouredButton*> items_;
  void DoLayout();
};

#endif  // COLOURED_BUTTON_CONTAINER_HPP_
