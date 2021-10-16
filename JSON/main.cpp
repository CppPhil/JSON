#include <cstdlib>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

#include "serialization.hpp"

// JSON (JavaScript Object Notation)
// XML
// REST
// RPC (remote procedure call) / JSON-RPC
// Save configuration data (.ini)

namespace nl = nlohmann;

// https://github.com/nlohmann/json
// https://json.nlohmann.me/doxygen/index.html
int main()
{
  std::cout << std::boolalpha;

  // Do not use uniform initialization

  const nl::json jsonObject = {
    {"firstName", "John"},
    {"lastName", "Smith"},
    {"phoneNumbers",
     nl::json::array(
       {nl::json::object({{"type", "home"}, {"number", "123"}}),
        nl::json::object({{"type", "office"}, {"number", "456"}})})}};
  std::cout << std::setw(4) << jsonObject << '\n';

  const std::map<std::string, int> map{{"one", 1}, {"two", 2}, {"three", 3}};
  const nl::json                   jsonObject2 = map;
  std::cout << std::setw(2) << jsonObject2 << '\n';

  // const nl::json json(nl::json::parse(R"({"text": 15, "hello": "world"})"));
  const nl::json json = "{\"text\": 15, \"hello\": \"world\"}"_json;
  std::cout << std::setw(2) << json << '\n';

  // Read from a file
  std::ifstream ifs{"../../../../JSON/example.json"};

  if (!ifs) {
    std::cerr << "Couldn't open file\n";
    return EXIT_FAILURE;
  }

  nl::json json2;
  ifs >> json2;
  ifs.close();

  std::cout << std::setw(2) << json2 << '\n';

  json2["key"] = "value";
  std::ofstream ofs{"../../../../JSON/output.json"};

  if (!ofs) {
    std::cerr << "Couldn't open file for writing.\n";
    return EXIT_FAILURE;
  }

  ofs << std::setw(8) << json2;

  const std::string string{json.dump(4)};
  std::cout << "string: " << string << '\n';

  nl::json object;
  object["version"] = "2.3.4";
  object["value"]   = 15;

  for (const auto& [key, value] : object.items()) {
    std::cout << key << " => " << value << '\n';
  }

  const std::string              searchKey{"value"};
  const nl::json::const_iterator it{object.find(searchKey)};

  if (it != object.end()) {
    std::cout << "Found " << searchKey << ": " << it.key() << " => "
              << it.value() << '\n';
  }

  object.erase("value");

  if (object.contains("value")) {
    std::cout << "object contains \"value\".\n";
  }

  const nl::json ary = nl::json::array({{"test", "text"}, {"val", 235.6}});
  std::cout << ary << '\n';

  nl::json json3;
  json3.push_back("text");
  json3.push_back(5.7);
  json3.push_back(42);
  json3.push_back(true);
  std::cout << json3 << '\n';

  const nl::json::value_t type{json3.type()};

  switch (type) {
  case nl::json::value_t::null:
    std::cout << "null\n";
    break;
  case nl::json::value_t::object:
    std::cout << "object\n";
    break;
  case nl::json::value_t::array:
    std::cout << "array\n";
    break;
  case nl::json::value_t::string:
    std::cout << "string\n";
    break;
  case nl::json::value_t::boolean:
    std::cout << "boolean\n";
    break;
  case nl::json::value_t::number_integer:
    std::cout << "number_integer\n";
    break;
  case nl::json::value_t::number_unsigned:
    std::cout << "number_unsigned\n";
    break;
  case nl::json::value_t::number_float:
    std::cout << "number_float\n";
    break;
  case nl::json::value_t::binary:
    std::cout << "binary\n";
    break;
  case nl::json::value_t::discarded:
    std::cout << "discarded\n";
    break;
  }

  json3.is_null();
  json3.is_boolean();
  json3.is_number();
  json3.is_object();
  json3.is_array();
  json3.is_string();

  for (const auto& e : json3) {
    std::cout << e << '\n';
  }

  const std::string str{json3[0].get<std::string>()};
  std::cout << "str: " << str << '\n';
  json3[2] = false;
  std::cout << json3[2] << '\n';
  const bool b{json3.at(3)};
  std::cout << "b: " << b << '\n';

  std::cout << "size: " << json3.size() << '\n'
            << "empty: " << json3.empty() << '\n';

  json3.clear();
  std::cout << "json3: " << json3 << '\n';

  s::serializationTest();

  return EXIT_SUCCESS;
}
