#include <iomanip>
#include <iostream>
#include <utility>

#include "serialization.hpp"

namespace s {
bool operator==(const Struct& lhs, const Struct& rhs)
{
  return (lhs.a == rhs.a) && (lhs.text == rhs.text);
}

bool operator==(const Employee& lhs, const Employee& rhs)
{
  return (lhs.m_name == rhs.m_name)
         && (lhs.m_annualSalary == rhs.m_annualSalary)
         && (lhs.m_address == rhs.m_address);
}

Employee::Employee() : Employee{"Default name", 0, "No address"}
{
}

Employee::Employee(std::string name, int annualSalary, std::string address)
  : m_name{std::move(name)}
  , m_annualSalary{annualSalary}
  , m_address{std::move(address)}
{
}

void serializationTest()
{
  const Struct         s{12345, "sample text"};
  const nlohmann::json json = s;
  std::cout << std::setw(2) << json << '\n';
  const Struct s2{json.get<Struct>()};
  std::cout << "areEqual: " << (s == s2) << '\n';

  const Employee peter{
    "Peter Smith", 85'000, "7958 Lakewood St. Riverview, FL 33569"};
  const nlohmann::json json2 = peter;
  std::cout << "json2: " << std::setw(2) << json2 << '\n';
  const Employee deserializedPeter{json2.get<Employee>()};
  std::cout << "areEqual: " << (peter == deserializedPeter) << '\n';
}
} // namespace s
