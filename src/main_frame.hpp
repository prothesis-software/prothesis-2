#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/treectrl.h>
#include <wx/statline.h>
#include <wx/notebook.h>

#include <string>

#include "data_panel.hpp"
#include "data_manager.hpp"

class MainFrame: public wxFrame {
 public:
  MainFrame(wxWindow *parent,
            wxWindowID id,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            int64_t style = wxDEFAULT_FRAME_STYLE,
            const wxString name = wxFrameNameStr);
  /**
   * Display the panel with the given ID
   */
  void DisplayPanelById(DataManager::PanelId id);

  bool DisplayNextPanel();

  /**
   * Set the title displayed in the header
   */
  void SetHeaderTitle(std::string title);
  static void OnKill(int sig);
  DataManager *data_manager_;
  ~MainFrame();

  /**
   * Returns the minimun size that will fit every page
   */
  wxSize GetOverallMinSize();

 private:
  void DoLayout();
  void SetProperties();
  void OnClose(wxCloseEvent &e); // NOLINT
  void OnButtonNextClick(wxCommandEvent &event);  // NOLINT
  void OnNotebookSelectionChange(wxBookCtrlEvent& event);  // NOLINT
  wxNotebook *notebook_ = NULL;
  DataManager::PanelId active_panel_id_;
  DataPanel *active_panel_ = NULL;
  wxFlexGridSizer *sizer_main_frame_ = NULL;
  wxFlexGridSizer *sizer_content_ = NULL;
  wxStaticText *label_title_ = NULL;
  wxPanel *panel_main_ = NULL;

  /**
   * Display the given panel and adds it to the sizer
   */
  void DisplayPanel_deprecated(DataPanel *panel);
};

#endif  // MAIN_FRAME_HPP_
