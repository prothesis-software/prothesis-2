#include "coloured_button_container.hpp"

#include <memory>
#include <string>
#include <vector>

ColouredButtonContainer::ColouredButtonContainer(
    wxWindow* parent, wxWindowID id, std::string panel_name,
    std::string panel_title, const wxPoint& pos, const wxSize& size,
    int64_t style)
    : DataPanel(parent, id, panel_name, panel_title, pos, size, style) {
  DoLayout();
}

ColouredButtonContainer::~ColouredButtonContainer() {
  // void
}

bool ColouredButtonContainer::SetGuiState(
    std::shared_ptr<cpptoml::table> state) {
  return false;
}

std::shared_ptr<cpptoml::table> ColouredButtonContainer::GetUserState() {
  auto panel_table = cpptoml::make_table();

  auto button_table_array = cpptoml::make_table_array();

  for (size_t i = 0; i < items_.size(); i++) {
    auto button_table = cpptoml::make_table();
    button_table->insert("label", items_.at(i)->GetButtonLabel());

    wxColour colour = items_.at(i)->GetColour();
    if (colour.IsOk()) {
      button_table->insert("rgb", colour.GetRGB());
    } else {
      button_table->insert("rgb", -1);
    }

    button_table_array->push_back(button_table);
  }
  panel_table->insert("item", button_table_array);

  return panel_table;
}

bool ColouredButtonContainer::SetUserState(
    std::shared_ptr<cpptoml::table> state) {
  auto panel_table = state->get_table(this->GetPanelName());

  if (panel_table) {
    auto button_array = panel_table->get_table_array("item");
    if (button_array) {
      for (const auto& table : *button_array) {
        auto label = table->get_as<std::string>("label");
        std::string label_str = "";
        if (label) {
          label_str = *label;
        }
        wxUint32 colour_rgb;

        auto colour = table->get_as<int>("rgb");
        if (colour) {
          if (*colour != -1) {
            colour_rgb = *colour;
            this->AddItem(label_str, colour_rgb);
          } else {
            this->AddItem(label_str);
          }
        } else {
          this->AddItem(label_str);
        }
      }
    }
  }

  return true;
}

bool ColouredButtonContainer::RemoveItem(ColouredButton* item,
                                         bool delete_item) {
  for (size_t i = 0; i < items_.size(); i++) {
    if (items_.at(i) == item) {
      // Move to back so we can pop
      for (size_t j = i; j < items_.size() - 1; j++) {
        ColouredButton* tmp = items_.at(j);
        items_.at(j) = items_.at(j + 1);
        items_.at(j + 1) = tmp;
      }
      items_.pop_back();
      sizer_buttons_->Remove(i);

      if (delete_item) {
        wxLogDebug(_("Deleted item ") + _(item->GetButtonLabel()));
        delete item;
      } else {
        wxLogDebug(_("Detached item ") + _(item->GetButtonLabel()));
      }

      Layout();
      return true;
    }
  }

  wxLogDebug(_("Could not delete/detach item ") + _(item->GetButtonLabel()));
  return false;
}

void ColouredButtonContainer::AddItem(ColouredButton* item) {
  wxLogDebug(_("Adding existing item: ") + _(item->GetButtonLabel()));

  sizer_buttons_->Add(item, 1, wxEXPAND, wxALL, 0);
  items_.push_back(item);
}

ColouredButton* ColouredButtonContainer::AddItem(std::string label,
                                                 wxUint32 rgb) {
  wxColour colour = wxColour(rgb);
  ColouredButton* btn = AddItem(label);
  btn->SetColour(colour);
  return btn;
}

ColouredButton* ColouredButtonContainer::AddItem(std::string item) {
  wxLogDebug(_("Adding new item: ") + _(item));
  ColouredButton* btn =
      new ColouredButton(sizer_root_->GetStaticBox(), wxID_ANY, item);
  sizer_buttons_->Add(btn, 1, wxEXPAND | wxALL, 0);
  items_.push_back(btn);

  return btn;
}

std::vector<ColouredButton*> ColouredButtonContainer::GetColouredButtons() {
  return items_;
}

void ColouredButtonContainer::GetItemDeltas(
    std::vector<std::string> new_items,
    std::vector<ColouredButton*> existing_items,
    std::vector<ColouredButton*>* only_in_existing,
    std::vector<ColouredButton*>* in_new_and_existing) {
  for (size_t i = 0; i < existing_items.size(); i++) {
    bool found = false;
    for (size_t j = 0; j < new_items.size(); j++) {
      if (existing_items.at(i)->GetButtonLabel().compare(new_items.at(j)) ==
          0) {
        found = true;
        break;
      }
    }

    if (!found) {
      only_in_existing->push_back(existing_items.at(i));
    } else {
      in_new_and_existing->push_back(existing_items.at(i));
    }
  }
}

bool ColouredButtonContainer::ContainsItem(std::vector<ColouredButton*> buttons,
                                           std::string item) {
  bool found = false;
  for (size_t i = 0; i < buttons.size(); i++) {
    if (buttons.at(i)->GetButtonLabel().compare(item) == 0) {
      found = true;
      break;
    }
  }

  return found;
}

ColouredButton* ColouredButtonContainer::GetItemByLabel(
    std::vector<ColouredButton*> buttons, std::string label) {
  for (size_t i = 0; i < buttons.size(); i++) {
    if (buttons.at(i)->GetButtonLabel().compare(label) == 0) {
      return buttons.at(i);
    }
  }

  return NULL;
}

bool ColouredButtonContainer::ContainsItem(std::vector<std::string> items,
                                           std::string item) {
  for (size_t i = 0; i < items.size(); i++) {
    if (items.at(i).compare(item) == 0) {
      return true;
    }
  }

  return false;
}

std::vector<std::string> ColouredButtonContainer::RemoveDuplicates(
    std::vector<std::string> items) {
  wxLogDebug("Removing duplicates...");

  std::vector<std::string> result;

  for (size_t i = 0; i < items.size(); i++) {
    if (!ContainsItem(result, items.at(i))) {
      // auto it = result.begin();
      // result.insert(it, items.at(i));
      result.push_back(items.at(i));
    }
  }

  return result;
}

void ColouredButtonContainer::PrintVector(std::vector<ColouredButton*> items) {
  wxLogDebug("[");
  for (size_t i = 0; i < items.size(); i++) {
    wxLogDebug(_("\t") + _(items.at(i)->GetButtonLabel()));
  }
  wxLogDebug("]");
}

void ColouredButtonContainer::PrintVector(std::vector<std::string> items) {
  wxLogDebug("[");
  for (size_t i = 0; i < items.size(); i++) {
    wxLogDebug(_("\t") + _(items.at(i)));
  }
  wxLogDebug("]");
}

void ColouredButtonContainer::UpdateItems(std::vector<std::string> items) {
  std::vector<ColouredButton*> only_in_existing;
  std::vector<ColouredButton*> in_new_and_existing;

  wxLogDebug("items = ");
  PrintVector(items);

  items = RemoveDuplicates(items);

  wxLogDebug("items = ");
  PrintVector(items);

  GetItemDeltas(items, items_, &only_in_existing, &in_new_and_existing);
  wxLogDebug("only_in_existing = ");
  PrintVector(only_in_existing);

  wxLogDebug("in_new_and_existing = ");
  PrintVector(in_new_and_existing);

  // Delete old items
  wxLogDebug("Deleting old items...");
  for (size_t i = 0; i < only_in_existing.size(); i++) {
    RemoveItem(only_in_existing.at(i), true);
  }

  // Detach left over items
  wxLogDebug("Detaching items...");
  for (size_t i = 0; i < in_new_and_existing.size(); i++) {
    RemoveItem(in_new_and_existing.at(i), false);
  }

  // Add items back in the order of given items
  wxLogDebug("Adding items back in order");
  for (size_t i = 0; i < items.size(); i++) {
    ColouredButton* button = GetItemByLabel(in_new_and_existing, items.at(i));
    if (button) {
      AddItem(button);
    } else {
      AddItem(items.at(i));
    }
  }
}

void ColouredButtonContainer::DoLayout() {
  sizer_root_ = new wxStaticBoxSizer(wxHORIZONTAL, this, this->GetPanelTitle());
  sizer_buttons_ = new wxBoxSizer(wxVERTICAL);

  sizer_root_->Add(sizer_buttons_, 0, 0, 0);

  this->SetSizer(sizer_root_);
}
