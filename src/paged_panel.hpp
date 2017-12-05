#ifndef PAGED_PANEL_HPP_
#define PAGED_PANEL_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/hyperlink.h>
#include <wx/statline.h>

#include <vector>
#include <memory>
#include <string>

#include "data_panel.hpp"

class PagedPanel : public DataPanel {
 public:
  PagedPanel(wxWindow* parent,
             wxWindowID id,
             std::string panel_name,
             std::string panel_title,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             int64_t style = 0);
  ~PagedPanel();

  /**
   * Initializes the panel layout. First need to call AddPages() to
   * set the panel references.
   */
  void Init();

  /**
   * Display panel given its index.
   */
  void DisplayPage(size_t index);

  /**
   * Increases the active panel index and display it.
   * If there are no further pages, returns false.
   */
  bool DisplayNextPage();

  /**
   * Add a panel to the list of pages to be initialised
   * when Init() is called
   */
  void AddPage(wxPanel * panel);

  size_t GetPageCount();

  virtual bool SetGuiState(std::shared_ptr<cpptoml::table> state) = 0;
  virtual std::shared_ptr<cpptoml::table> GetUserState() = 0;
  virtual bool SetUserState(std::shared_ptr<cpptoml::table> state) = 0;

 private:
  void DoLayout();
  void SetProperties();
  void OnHyperlinkClick(wxHyperlinkEvent &event);  // NOLINT
  void OnButtonNextClick(wxCommandEvent &event);  // NOLINT
  size_t active_panel_index_ = 0;
  std::vector<wxPanel*> panels_;
  std::vector<wxHyperlinkCtrl*> hyperlinks_;

  wxFlexGridSizer *sizer_paged_panel_ = NULL;
  wxPanel *active_panel_ = NULL;
  wxButton *button_next_ = NULL;
  wxPanel* panel_page_numbers_;
};
#endif  // PAGED_PANEL_HPP_
