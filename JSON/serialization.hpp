#pragma once
#include <string>

#include <nlohmann/json.hpp>

// Our types must be default constructible.
namespace s {
struct Struct {
  friend bool operator==(const Struct& lhs, const Struct& rhs);

  int         a;
  std::string text;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Struct, a, text)

class Employee {
public:
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(Employee, m_name, m_annualSalary, m_address)

  friend bool operator==(const Employee& lhs, const Employee& rhs);

  Employee();

  Employee(std::string name, int annualSalary, std::string address);

private:
  std::string m_name;
  int         m_annualSalary;
  std::string m_address;
};

void serializationTest();
} // namespace s
