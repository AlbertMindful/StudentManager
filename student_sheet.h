#ifndef __STUDENT_SHEET_H__
#define __STUDENT_SHEET_H__
#include "student.h"
#include <algorithm>
#include <iostream>
#include <istream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <vector>

class StudentSheet {
public:
  StudentSheet(const std::string &sheetName, const Student &stuTemplate,
               const std::string &keyField)
      : name(sheetName), studentTemplate(stuTemplate), keyField(keyField) {}
  void print(std::ostream &out = std::cout) const;
  void clear(); //删除此sheet中的所有学生信息以及sheetName.dat
  void read();  //从sheetName.dat中读取学生信息
  void write(); //写入sheetName.dat中
  void add(const Student &stu) {
    // 不能有两条完全相同的记录
    if (std::find(studentInfos.begin(), studentInfos.end(), stu) ==
        studentInfos.end()) {
      studentInfos.emplace_back(stu);
    }
  }
  // 移除关键字值为keyFieldValue的记录
  void remove(const std::string &keyFieldValue) {
    auto it = find(keyFieldValue);
    if (!it.has_value()) {
      return;
    }
    studentInfos.erase(it.value());
  }
  // 查找关键字值为keyFieldValue的记录
  std::optional<std::vector<Student>::const_iterator>
  find(const std::string &keyFieldValue) const {
    try {
      return _find(keyFieldValue);
    } catch (
        const std::out_of_range &except) { // 表中不存在keyField字段(不可能)
      std::cout << except.what() << std::endl;
    }
    return std::nullopt;
  }
  std::optional<std::vector<Student>::iterator>
  find(const std::string &keyFieldValue) {
    auto cit = static_cast<const StudentSheet &>(*this).find(keyFieldValue);
    if (!cit.has_value()) {
      return std::nullopt;
    }
    return studentInfos.begin() + (cit.value() - studentInfos.begin());
  }
  const std::string &getName() const noexcept { return name; }
  const std::string &getKeyField() const noexcept { return keyField; }
  Student getStudentTemplate() const noexcept { return studentTemplate; }
  // void setIndex();
  // void deleteIndex();
  // void createIndex();
  //
private:
  std::optional<std::vector<Student>::const_iterator>
  _find(const std::string &keyFieldValue) const {
    auto pred = [&keyFieldValue, this](const Student &stu) {
      return std::get<std::string>(stu.getFieldValue(keyField)) ==
             keyFieldValue;
    };
    auto it = std::find_if(studentInfos.begin(), studentInfos.end(), pred);
    return it == studentInfos.end()
               ? std::optional<std::vector<Student>::const_iterator>(
                     std::nullopt)
               : it;
  }

  Student studentTemplate;
  std::vector<Student> studentInfos;
  std::string keyField;
  std::string name;
};

#endif
