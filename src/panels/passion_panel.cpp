#include "passion_panel.hpp"
#include <memory>
#include <string>

PassionPanel::PassionPanel(wxWindow *parent,
                           wxWindowID id,
                           std::string panel_name,
                           std::string panel_title,
                           const wxPoint &pos,
                           const wxSize &size,
                           int64_t style)
  : QuestionsPanel(parent, id, panel_name, panel_title, pos, size, style) {
  // void
}

PassionPanel::~PassionPanel() {
    // void
}
