#include "sheet_handle.h"
#include "basic_input.h"
#include "student_handle.h"

using namespace std;
constexpr size_t NumberForPerLine = 5;

static void _createSheet(StudentDatabase &studentDatabase) {
  string newSheetName;
  string newkeyField;
  Student studentTemplate;
  cout << "请输入表名:";
  cin >> newSheetName;
  createSheetStructure(studentTemplate);
  cout << "请输入关键字段:";
  cin >> newkeyField;
  auto fieldNames = studentTemplate.getFieldNames().value();
  while (find(fieldNames.begin(), fieldNames.end(), newkeyField) ==
         fieldNames.end()) {
    cout << "不存在" + newkeyField + ",请重新输入关键字段:";
    cin >> newkeyField;
    fieldNames = studentTemplate.getFieldNames().value();
  }
  studentDatabase.createSheet(newSheetName, studentTemplate, newkeyField);
  handleSingleSheet(studentDatabase.findSheet(newSheetName).value());
}

void createSheet(StudentDatabase &studentDatabase) noexcept {
  try {
    _createSheet(studentDatabase);
  } catch (const bad_alloc &exp) {
    cout << "表数量已达到内存上限!" << endl;
    cout << exp.what() << endl;
  } catch (const exception &exp) {
    // TODO
    cout << "happend exception" << endl;
    cout << exp.what() << endl;
  }
}

void deleteSheet(StudentDatabase &studentDatabase) {
  if (!showSheetNames(studentDatabase)) {
    // TODO
    return;
  }
  cout << "请输入要删除的表的名称:";
  string sheetNameToDelete;
  cin >> sheetNameToDelete;
  auto actualSheet = studentDatabase.findSheet(sheetNameToDelete);
  if (!actualSheet.has_value()) {
    cout << "不存在表" + sheetNameToDelete + "!" << endl;
    cout << "请重新尝试!" << endl;
    return;
  }
  studentDatabase.deleteSheet(actualSheet.value());
}
void createSheetStructure(Student &studentTemplate) {
  while (true) {
    string fieldName;
    string fieldType;
    Field::Var fieldValue;
    cout << "请输入字段名:";
    cin >> fieldName;
  reinput:
    cout << "请输入字段类型(N,C,L,F)";
    cin >> fieldType;
    // 根据输入字符定义字段类型
    try {
      fieldValue = Field::convertToVar(fieldType).value();
    } catch (const std::bad_optional_access &except) {
      cout << except.what();
      goto reinput;
    }
    studentTemplate.addField(Field(fieldName, fieldValue));
    string ctrl;
    cout << "是否继续创建字段?(Y/N)" << std::endl;
    cin >> ctrl;
    if (ctrl.empty()) {
      continue;
    }
    if (toupper(ctrl[0]) == 'N') {
      break;
    }
  }
}
void changeSheet(StudentDatabase &studentDatabase) {
  if (!showSheetNames(studentDatabase)) {
    return;
  }
  cout << "请输入要切换的表的名称:";
  string sheetNameToChange;
  cin >> sheetNameToChange;
  auto actualSheet = studentDatabase.findSheet(sheetNameToChange);
  if (!actualSheet.has_value()) {
    cout << "不存在表" + sheetNameToChange + "!" << endl;
    cout << "请重新尝试!" << endl;
    return;
  }
  handleSingleSheet(actualSheet.value());
}
bool showSheetNames(const StudentDatabase &studentDatabase) {
  auto sheetNames = studentDatabase.getAllSheetNames();
  if (!sheetNames.has_value()) {
    cout << "请先创建表" << endl;
    return false;
  }
  cout << "所有表:" << endl;
  int i = 0;
  for (const auto &sheetName : sheetNames.value()) {
    cout << sheetName << " ";
    if (++i % NumberForPerLine == 0) {
      cout << "\n";
    }
  }
  cout << endl;
  return true;
}

void handleSingleSheet(std::vector<StudentSheet>::iterator sheet) {
  bool isQuit = false;
  while (!isQuit) {
    cout << "1.添加学生\n";
    cout << "2.删除学生\n";
    cout << "3.查询学生\n";
    cout << "4.打印Sheet\n";
    cout << "5.建立索引\n";
    cout << "6.删除索引\n";
    cout << "7.指定主控索引\n";
    cout << "8.返回首页" << endl;
    cout << "选择:";
    auto choose = getInteger();
    while (!choose.has_value()) {
      cout << "输入有误，请重新输入:";
      choose = getInteger();
    }
    switch (choose.value()) {
    case 1:
      addStudent(sheet);
      break;
    case 2:
      deleteStudent(sheet);
      break;
    case 3:
      findStudent(sheet);
      break;
    case 4:
      searchStudent(sheet);
      break;
    case 5:
      createIndex(sheet);
      break;
    case 6:
      deleteIndex(sheet);
      break;
    case 7:
      setIndex(sheet);
      break;
    case 8:
      isQuit = true;
      break;
    default:
      cout << "无效选项!" << endl;
      break;
    }
  }
}
