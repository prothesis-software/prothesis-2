#ifndef PANELS_PRIORITIES_PANEL_HPP_
#define PANELS_PRIORITIES_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/listctrl.h>

#include <memory>
#include <string>

#include "src/data_panel.hpp"

class PrioritiesPanel : public DataPanel {
 public:
  PrioritiesPanel(wxWindow *parent,
                  wxWindowID id,
                  std::string panel_name,
                  std::string panel_title,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize,
                  int64_t style = 0);
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
  void AddUnsortedPriority(std::string priority);

  /**
   * Ad hoc method to calculate the height of a listbox item.
   * Used for setting the best size.
   * \warning Hack
   */
  int GetItemHeight(wxListCtrl *list);
  void SetBestListHeight(wxListCtrl *list);
  void OnUnsortedListBoxSelectionChange(wxListEvent &event);  // NOLINT
  void OnButtonAddClick(wxCommandEvent &event);  // NOLINT
  void AddSelectedItemToSorted();
  wxListCtrl *list_unsorted_1_ = NULL;
  wxListCtrl *list_unsorted_2_ = NULL;
  wxListCtrl *list_sorted_ = NULL;
  wxListCtrl *unsorted_lists_[2];
  int item_height_ = -1;
};

#endif  // PANELS_PRIORITIES_PANEL_HPP_
