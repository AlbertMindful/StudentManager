#include "student.h"
const std::vector<std::string> Field::FieldTypes = {"C", "N", "F", "L"};

bool operator==(const Student &stu1, const Student &stu2) {
  return stu1.studentInfo == stu2.studentInfo;
}
