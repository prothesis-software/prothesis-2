#ifndef DATA_MANAGER_HPP_
#define DATA_MANAGER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/log.h>
#include <vector>
#include <string>

#include "include/cpptoml.h"
#include "data_panel.hpp"
#include "utilities.hpp"

/**
 * The Data Manager class is responsible for storing reference
 * to the frames containing data, as well as to save and restore their
 * state.
 */
class DataManager {
 public:
  /**
   * Initializes all panels from the GUI config and the User config and adds
   * them as children to the MainFrame
   */
  explicit DataManager(wxFrame *main_frame);

  ~DataManager();

  /** The PanelId corresponds to the index of the panel in the panels_ array
   */
  enum PanelId {
    kDetailsPanel = 0,
    kPassionPanel = 1,
    kPeopleIdPanel = 2,
    kPanelCount = 3
  };

  /**
   * Save the User config
   */
  void SaveUserConfig();

  /**
   * Returns the path to the directory where the executable is in
   */
  std::string GetBasePath();

  /**
   * Return a reference to the panel given its ID
   */
  DataPanel *GetPanelById(DataManager::PanelId panel_id);

  /**
   * Return a reference to a panel given its index
   */
  DataPanel *GetPanelByIndex(size_t index);

 private:
  /**
   * Reads the user and gui config and initializes each panel
   * with the config data
   */
  void Load();

  /**
   * All panels are declared in this function
   */
  void DeclarePanels();
  DataPanel *panels_[3];
  // Paths are relative to the base directory of the binary
  std::string gui_config_path_ = "gui.toml";
  std::string user_config_path_ = "user.toml";
  wxFrame *main_frame_ = NULL;
};
#endif  // DATA_MANAGER_HPP_
