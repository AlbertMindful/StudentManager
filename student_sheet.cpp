#include "student_sheet.h"
#include <filesystem>
#include <fstream>

void printStudentFields(std::ostream &out, const Student &student) {
  auto names = student.getFieldNames();
  if (!names.has_value()) {
    return;
  }
  for (const auto &fieldName : names.value()) {
    const Field::Var &fieldValue = student.getFieldValue(fieldName);
    out << fieldName + " : ";
    std::visit(GetVisitor{}, fieldValue);
    Field::Var a = 10;
    std::visit(GetVisitor{}, a);
    switch (fieldValue.index()) {
    case 0:
      std::cout << std::get<std::string>(fieldValue);
      break;
    case 1:
      std::cout << std::get<int>(fieldValue);
      break;
    case 2:
      std::cout << std::get<double>(fieldValue);
      break;
    case 3:
      std::cout << std::get<bool>(fieldValue);
      break;
    }
  }
}

void StudentSheet::print(std::ostream &out) const {
  // field name : value        field name : value
  // ......
  //
  try {
    for (const auto &student : studentInfos) {
      printStudentFields(out, student);
    }
  } catch (const std::out_of_range &except) {
    out << except.what();
  }
}
//删除此sheet中的所有学生信息以及sheetName.dat
void StudentSheet::clear() {
  std::filesystem::remove(name + ".dat");
  studentInfos.clear();
}
//从sheetName.dat中读取学生信息
void StudentSheet::read() {
  std::ifstream file;
  file.exceptions();
  file.open(name + ".dat"); //打开失败自动抛出std::ios_base::failure异常
}

static void writeFieldAttr(std::ofstream &out,
                           const std::vector<std::string> &names,
                           const std::vector<int> &indexs) {
  for (size_t i = 0; i < names.size(); ++i) {
    out << names[i] << " " << indexs[i] << '\n';
  }
}

static void writeRecord(std::ostream &out,
                        const std::vector<std::string> &fieldNames,
                        const Student &stu) {
  auto indexs = stu.getFieldTypeIndexs();
  if (!indexs.has_value()) {
    return;
  }
  const std::vector<int> &fieldIndexs = indexs.value();
  for (size_t i = 0; i < stu.size(); ++i) {
    auto fieldValue = stu.getFieldValue(fieldNames[i]);
    // TODO
  }
}

//写入sheetName.dat中
void StudentSheet::write() {
  std::ofstream file;
  file.exceptions();
  file.open(name + ".dat"); //打开失败自动抛出std::ios_base::failure异常
  auto names = studentTemplate.getFieldNames();
  auto indexs = studentTemplate.getFieldTypeIndexs();
  if (!names.has_value() || !indexs.has_value()) {
    return;
  }
  std::vector<std::string> fileNames = names.value();
  std::vector<int> typeIndexs = indexs.value();
  // 待写入数据：主关键字段名、各个字段的名称及类型索引（用以构建studentTemplate）、数据
  file << keyField + '\n';
  writeFieldAttr(file, fileNames, typeIndexs);

  for (const auto &student : studentInfos) {
    writeRecord(file, fileNames, student);
  }
  file.close();
}
