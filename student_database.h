#ifndef __STUDENT_SYSTEM__
#define __STUDENT_SYSTEM__
#include "student_sheet.h"
class StudentDatabase {
public:
  constexpr static size_t MaxSheetNumber = 128;
  std::optional<std::vector<StudentSheet>::iterator>
  findSheet(const std::string &sheetName) {
    auto pred = [&sheetName](const StudentSheet &sheet) {
      return sheet.getName() == sheetName;
    };

    return std::find_if(sheets.begin(), sheets.end(), pred);
  }
  void createSheet(const std::string &sheetName, const Student &studentTemplate,
                   const std::string &keyField) {
    if (sheets.size() < sheets.max_size()) {
      sheets.emplace_back(StudentSheet(sheetName, studentTemplate, keyField));
    }
    throw std::bad_alloc();
  }
  void deleteSheet(const std::string &sheetName) {
    auto sheetToDelete = findSheet(sheetName);
    if (!sheetToDelete.has_value()) {
      return;
    }
    sheets.erase(sheetToDelete.value());
  }
  void deleteSheet(std::vector<StudentSheet>::const_iterator sheetIt) {
    sheets.erase(sheetIt);
  }
  std::optional<std::vector<std::string>> getAllSheetNames() const {
    std::vector<std::string> sheetNames;
    for (const auto &sheet : sheets) {
      sheetNames.push_back(sheet.getName());
    }

    return sheetNames.size() == 0
               ? std::nullopt
               : std::optional<std::vector<std::string>>(sheetNames);
  }

private:
  std::vector<StudentSheet> sheets;
};

#endif
