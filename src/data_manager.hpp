#ifndef DATA_MANAGER_HPP_
#define DATA_MANAGER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <vector>

#include "data_panel.hpp"
#include "main_frame.hpp"

/**
 * The Data Manager class is responsible for storing reference
 * to the frames containing data, as well as to save and restore their
 * state.
 */
class DataManager {
 public:
  /**
   * Given a reference to the main frame, create the panels defined in
   * the constructor and set the main_frame as the parent
   */
  explicit DataManager(MainFrame *main_frame);

  /** The PanelId corresponds to the index of the panel in the panels_ array
   */
  enum PanelId {
    kDetailsPanel = 0
  };

  /**
   * Display the panel with the given ID on the Main Frame.
   * This is a wrapper for MainFrame::DisplayPanel(DataPanel *panel)
   */
  void DisplayPanel(PanelId panel_id);


 private:
  MainFrame *main_frame_;
  DataPanel *panels_[1];
};
#endif  // DATA_MANAGER_HPP_
