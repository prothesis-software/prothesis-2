#ifndef DATA_MANAGER_HPP_
#define DATA_MANAGER_HPP_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dialog.h>

#include <wx/log.h>
#include <string>
#include <vector>

#include "include/cpptoml.h"

#include "data_panel.hpp"
#include "utilities.hpp"

#include "checkbox_panel.hpp"
#include "questions_panel.hpp"

#include "panels/details_panel.hpp"
#include "panels/external_panel.hpp"
#include "panels/priorities_panel.hpp"
#include "panels/theme_analysis_panel.hpp"
#include "panels/work_environment_panel.hpp"

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
  explicit DataManager(wxWindow* main_frame, wxWindow* assessments_window);

  ~DataManager();

  /**
   * Id correspond to index in panels_
   * FLAG: new-panel
   */
  enum PanelId {
    kDefaultPanel = -1,
    kDetailsPanel = 0,
    kPassionPanel = 1,
    kPeopleIdPanel = 2,
    kDreamsPanel = 3,
    kValuesPanel = 4,
    kSpokenWordsPanel = 5,
    kSkillsPanel = 6,
    kExternalPanel = 7,
    kWorkEnvironmentPanel = 8,
    kPrioritiesPanel = 9,
    kRolesPanel = 10,
    kPeopleOrientationPanel = 11,
    kThemeAnalysisPanel = 12,
    kPanelCount = 13
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
  DataPanel* GetPanelById(DataManager::PanelId panel_id);

  /**
   * Return a reference to a panel given its index
   */
  DataPanel* GetPanelByIndex(size_t index);

  PanelId GetIdFromIndex(size_t index);

  DataManager::PanelId GetIdFromName(std::string name);

 private:
  /**
   * Reads the user and gui config and initializes each panel
   * with the config data
   */
  bool Load();

  /**
   * All panels are declared in this function
   */
  void DeclarePanels();

  /**
   * Add a panel to the panel vector. Calls Hide() on the panel.
   * Required to initialise the index to enum array
   */
  void AddPanel(DataPanel* panel, PanelId id);

  DataPanel* panels_[PanelId::kPanelCount];
  DataManager::PanelId ids_[PanelId::kPanelCount];

  wxWindow* main_frame_ = NULL;
  wxWindow* assessments_window_ = NULL;

  // Paths are relative to the base directory of the binary
  std::string gui_config_path_ = "gui.toml";
  std::string user_config_path_ = "user.toml";
};
#endif  // DATA_MANAGER_HPP_
