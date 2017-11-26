#include "data_manager.hpp"

DataManager::DataManager(MainFrame *main_frame) {
  main_frame_ = main_frame;

  DetailsPanel *details_panel = new DetailsPanel(main_frame_, wxID_ANY);
  panels_[0] = details_panel;
}

void DataManager::DisplayPanel(PanelId panel_id) {
  main_frame_->DisplayPanel(panels_[panel_id]);
}
