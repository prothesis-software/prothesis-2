#include <iostream>
#include "cpptoml.h"
#include "gui_generator.hpp"

int GuiGenerator::injectButtons(wxWindow *window, wxBoxSizer *sizer, std::string configFile) {
  
  // Look, Python!
  try {
    
    auto config = cpptoml::parse_file(configFile);
    auto tableArray = config->get_table_array("buttons");

    // Black magic!
    for (const auto& table : *tableArray) {
      // *table is a cpptoml::table
      //std::cout << "READING..." << std::endl;
      auto text = table->get_as<std::string>("text").value_or("ERROR");
      //std::cout << "Creating a button..." << std::endl;

      // Create and inject button
      wxString tmpString = wxString(text);
    
      wxButton *btn = new wxButton(window, wxID_ANY, tmpString,
				   wxDefaultPosition, wxDefaultSize, 0);

		      
      sizer->Add(btn, 0, wxALIGN_CENTER, 0);
    
    }
  } catch (const std::exception &e) {
    std::cout << "gui.toml not found in current directory" << std::endl;
    std::cout << e.what() << std::endl;
  }

  return 0;
}
