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

 private:
  void DoLayout();
  void OnClose(wxCloseEvent& e);                           // NOLINT
  void OnNotebookSelectionChange(wxBookCtrlEvent& event);  // NOLINT
  wxNotebook* notebook_ = NULL;
  wxNotebook* notebook_assessments_ = NULL;
  wxFlexGridSizer* sizer_main_frame_ = NULL;
  wxFlexGridSizer* sizer_content_ = NULL;
  wxPanel* panel_main_ = NULL;
  bool exit_requested_ = false;
  std::vector<std::vector<DataPanel*>> index_layout_;
};

#endif  // MAIN_FRAME_HPP_
