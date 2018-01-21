#include "mbti_info_panel.hpp"

#include <memory>
#include <string>
#include <vector>

MbtiInfoPanel::MbtiInfoPanel(wxWindow* parent, wxWindowID id,
                             const wxPoint& pos, const wxSize& size,
                             int64_t style)
    : wxPanel(parent, id, pos, size, style) {
  DoLayout();
}
