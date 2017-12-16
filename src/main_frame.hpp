#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/treectrl.h>
#include <wx/statline.h>

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

 protected:
  wxFlexGridSizer *sizer_content_;
  wxButton *button_drawer_;
  wxButton *button_config_;
  wxStaticText *label_title_;
  wxTreeCtrl *tree_ctrl_drawer_;
  wxPanel *panel_config_button_;
  wxPanel *panel_title_;
  wxPanel *panel_drawer_button_;
  void OnClose(wxCloseEvent &e); // NOLINT

 private:
  void DoLayout();
  void SetProperties();
  DataManager::PanelId active_panel_id_;
  DataPanel *active_panel_ = NULL;
  wxFlexGridSizer *sizer_main_frame_master_ = NULL;

  /**
   * Display the given panel and adds it to the sizer
   */
  void DisplayPanel(DataPanel *panel);
};

#endif  // MAIN_FRAME_HPP_
