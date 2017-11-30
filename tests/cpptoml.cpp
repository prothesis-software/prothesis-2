#define CATCH_CONFIG_MAIN  //  This tells Catch to
// provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "include/cpptoml.h"
#include <iostream>
#include <string>
#include <vector>

TEST_CASE("Simple Table") {
  std::shared_ptr<cpptoml::table> table = cpptoml::make_table();
  table->insert("key1", "value1");

  cpptoml::option<std::string> val = table->get_as<std::string>("key1");

  std::string retval = "ERROR";
  if (val) {
    retval = *val;
  }
  REQUIRE(retval.compare("value1") == 0);

  table = NULL;
}

// NOTE: Not a proper nested table!
TEST_CASE("Nested Table") {
  std::shared_ptr<cpptoml::table> table = cpptoml::make_table();
  std::shared_ptr<cpptoml::table> nested_table = cpptoml::make_table();

  std::string some_string = "lolcat";
  table->insert("key1", "value1");
  table->insert("key2", "value2");
  table->insert("key3", 69);
  table->insert("key4", some_string);

  nested_table->insert("mahTable", table);

  std::shared_ptr<cpptoml::table> mah_table =
    nested_table->get_table("mahTable");

  std::string retval = "ERROR";
  if (mah_table) {
    cpptoml::option<std::string> tmp =
      mah_table->get_as<std::string>("key4");
    if (tmp) {
      retval = *tmp;
    }
  }

  REQUIRE(retval.compare("lolcat") == 0);

  std::cout << "mah_table:" << std::endl << *mah_table << std::endl;
  std::cout << "nested_table:" << std::endl << *nested_table << std::endl;
}

TEST_CASE("Table Array") {
  std::shared_ptr<cpptoml::table> root = cpptoml::make_table();
  std::shared_ptr<cpptoml::table_array> table_array = cpptoml::make_table_array();

  std::shared_ptr<cpptoml::table> outer_table = cpptoml::make_table();

  std::shared_ptr<cpptoml::table> table_1 = cpptoml::make_table();
  table_1->insert("key1", "value1");
  table_1->insert("key2", 63);
  //outer_table->insert("some_table", table_1);

  table_array->push_back(table_1);
    std::cout << "table_array:" << std::endl << *table_array << std::endl;
  // outer_table = NULL;
  // outer_table = cpptoml::make_table();

  std::shared_ptr<cpptoml::table> outer_table_2 = cpptoml::make_table();
  std::shared_ptr<cpptoml::table> table_2 = cpptoml::make_table();
  table_2->insert("key1", "value1_2");
  table_2->insert("key2", 77);
  //outer_table_2->insert("some_table", table_2);

  table_array->push_back(table_2);
  std::cout << "table_array:" << std::endl << *table_array << std::endl;

  root->insert("mahTableArray", table_array);
  std::cout << "root:" << std::endl << *root << std::endl;

  std::shared_ptr<cpptoml::table> ret1 = table_array->get().back();
  std::string ret_string = "ERROR";

  if (ret1) {
    cpptoml::option<std::string> tmp = *ret1->get_as<std::string>("key1");
    if (tmp) {
      ret_string = *tmp;
    }
  }
  std::cout << ret_string << std::endl;
  std::cout << "table_array:" << std::endl << *table_array << std::endl;
  REQUIRE(ret_string.compare("value1_2") == 0);

  ret1 = NULL;
  std::cout << "table_array:" << std::endl << *table_array << std::endl;

  root->insert("mahTableArray", table_array);
  std::cout << "root:" << std::endl << *root << std::endl;

}

TEST_CASE("Given") {
  std::shared_ptr<cpptoml::table> root = cpptoml::make_table();
  root->insert("Integer", 1234L);
  root->insert("Double", 1.234);
  root->insert("String", std::string("ABCD"));

  auto table = cpptoml::make_table();
  table->insert("ElementOne", 1L);
  table->insert("ElementTwo", 2.0);
  table->insert("ElementThree", std::string("THREE"));

  auto nested_table = cpptoml::make_table();
  nested_table->insert("ElementOne", 2L);
  nested_table->insert("ElementTwo", 3.0);
  nested_table->insert("ElementThree", std::string("FOUR"));

  table->insert("Nested", nested_table);

  root->insert("Table", table);

  auto int_array = cpptoml::make_array();
  int_array->push_back(1L);
  int_array->push_back(2L);
  int_array->push_back(3L);
  int_array->push_back(4L);
  int_array->push_back(5L);

  root->insert("IntegerArray", int_array);

  auto double_array = cpptoml::make_array();
  double_array->push_back(1.1);
  double_array->push_back(2.2);
  double_array->push_back(3.3);
  double_array->push_back(4.4);
  double_array->push_back(5.5);

  root->insert("DoubleArray", double_array);

  auto string_array = cpptoml::make_array();
  string_array->push_back(std::string("A"));
  string_array->push_back(std::string("B"));
  string_array->push_back(std::string("C"));
  string_array->push_back(std::string("D"));
  string_array->push_back(std::string("E"));

  root->insert("StringArray", string_array);

  auto table_array = cpptoml::make_table_array();
  table_array->push_back(table);
  table_array->push_back(table);
  table_array->push_back(table);

  root->insert("TableArray", table_array);

  auto array_of_arrays = cpptoml::make_array();
  array_of_arrays->push_back(int_array);
  array_of_arrays->push_back(double_array);
  array_of_arrays->push_back(string_array);

  root->insert("ArrayOfArrays", array_of_arrays);

  std::cout << (*root);
}
