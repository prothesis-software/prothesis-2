#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/treectrl.h>

#include <string>
#include <vector>

#include "about_frame.hpp"
#include "data_manager.hpp"
#include "data_panel.hpp"

class MainFrame : public wxFrame {
 public:
  MainFrame(wxWindow* parent, wxWindowID id, const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            int64_t style = wxDEFAULT_FRAME_STYLE,
            const wxString name = wxFrameNameStr);
  ~MainFrame();

  bool DisplayNextPanel();
  static void OnKill(int sig);
  DataManager* data_manager_;

  /**
   * Returns the minimun size that will fit every page
   */
  wxSize GetOverallMinSize();

  void TriggerRefresh();

 private:
  void DoLayout();
  void OnSizeChange(wxSizeEvent& event);                   // NOLINT
  void OnClose(wxCloseEvent& e);                           // NOLINT
  void OnNotebookSelectionChange(wxBookCtrlEvent& event);  // NOLINT
  void OnMenuClick(wxCommandEvent& event);                 // NOLINT
  wxNotebook* notebook_ = NULL;
  wxNotebook* notebook_assessments_ = NULL;
  wxFlexGridSizer* sizer_main_frame_ = NULL;
  wxFlexGridSizer* sizer_content_ = NULL;
  wxPanel* panel_main_ = NULL;
  bool exit_requested_ = false;
  std::string active_panel_name_ = "";

  /**
   * [0][i] - Top notebook
   * [1][i] - Assessment notebook
   */
  std::vector<std::vector<DataPanel*>> index_layout_;
};

#endif  // MAIN_FRAME_HPP_
