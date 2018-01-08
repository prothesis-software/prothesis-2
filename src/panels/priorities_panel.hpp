#ifndef PANELS_PRIORITIES_PANEL_HPP_
#define PANELS_PRIORITIES_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/gdicmn.h>
#include <wx/listbox.h>

#include <memory>
#include <string>

#include "src/data_panel.hpp"

class PrioritiesPanel : public DataPanel {
 public:
  PrioritiesPanel(wxWindow *parent, wxWindowID id, std::string panel_name,
                  std::string panel_title,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize, int64_t style = 0);
  ~PrioritiesPanel();

  /**
   * TOML Specification:
   * [priorities]
   *   options = ["a", "b", "c"]
   */
  bool SetGuiState(std::shared_ptr<cpptoml::table> state) override;

  /**
   * TOML Specification:
   * [priorities]
   *   options = ["c", "a", "b"]
   */
  std::shared_ptr<cpptoml::table> GetUserState() override;

  /**
   * TOML Specifcation:
   *   The same as GetUserState()
   */
  bool SetUserState(std::shared_ptr<cpptoml::table> state) override;

 private:
  void DoLayout();

  /**
   * Add the item to the unsorted list with the least number of items
   */
  void AddUnsortedPriority(std::string priority);

  /**
   * Ad hoc method to calculate the height of a listbox item.
   * Used for setting the best size.
   */
  void GetItemHeight(wxListBox *list);

  /**
   * Set the height of the ListBox according to the result obtained from
   * GetItemHeight.
   */
  void SetBestListHeight(wxListBox *list);

  void OnUnsortedListBoxSelectionChange(wxCommandEvent &event);  // NOLINT
  void OnButtonAddClick(wxCommandEvent &event);                  // NOLINT
  void OnButtonRemoveClick(wxCommandEvent &event);               // NOLINT
  void OnButtonMoveUpClick(wxCommandEvent &event);               // NOLINT
  void OnButtonMoveDownClick(wxCommandEvent &event);             // NOLINT

  /**
   * Find the given string in the unsorted lists and move it
   * to the sorted list at the end
   */
  bool MoveItemToSorted(std::string item);

  /**
   * Move an item up or down in the sorted list.
   * -1 is up. 1 is down for the shift
   */
  void ChangeOrder(int index, int shift);

  /**
   * Move the selected item from a unsorted list to the sorted list
   * and select it
   */
  bool AddSelectedItemToSorted();

  /**
   * Remove the item ad the given index from the ListBox
   */
  void RemoveItemFromListBox(wxListBox *list_box, int index);

  wxListBox *list_unsorted_1_ = NULL;
  wxListBox *list_unsorted_2_ = NULL;
  wxListBox *list_sorted_ = NULL;
  wxListBox *unsorted_lists_[2];
  int item_height_ = -1;
};

#endif  // PANELS_PRIORITIES_PANEL_HPP_
