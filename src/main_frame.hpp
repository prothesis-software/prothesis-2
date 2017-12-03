#ifndef MAIN_FRAME_HPP_
#define MAIN_FRAME_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data_panel.hpp"
#include "panels/details_panel.hpp"
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
   * Display the given panel and adds it to the sizer
   */
  void DisplayPanel(DataPanel *panel);
  DataManager *data_manager_;
  static void OnKill(int sig);
  ~MainFrame();

 private:
  void DoLayout();
  void SetProperties();

 protected:
  DetailsPanel *details_panel_;
  wxFlexGridSizer *main_frame_sizer_;
  DataPanel *active_panel_;
  void OnClose(wxCloseEvent &e); // NOLINT
};

#endif  // MAIN_FRAME_HPP_
