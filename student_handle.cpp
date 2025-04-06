#include "student_handle.h"
#include <iostream>

using namespace std;

void addStudent(std::vector<StudentSheet>::iterator sheet) {
  Student studentAdded = sheet->getStudentTemplate();
  auto fieldNames = studentAdded.getFieldNames();
  if (!fieldNames.has_value()) {
    // 没有字段
    // TODO  错误处理，出现此错误，意味着什么？
    cerr << sheet->getName() + "表没有字段存在!\n";
    return;
  }
  for (const auto &fieldName : fieldNames.value()) {
    cout << "请输入" + fieldName + ":";
    // TODO 字段值输入处理
  }
  sheet->add(studentAdded);
}
void deleteStudent(std::vector<StudentSheet>::iterator sheet) {}
void findStudent(std::vector<StudentSheet>::iterator sheet) {}
void searchStudent(std::vector<StudentSheet>::iterator sheet) {}
void createIndex(std::vector<StudentSheet>::iterator sheet) {}
void deleteIndex(std::vector<StudentSheet>::iterator sheet) {}
void setIndex(std::vector<StudentSheet>::iterator sheet) {}
