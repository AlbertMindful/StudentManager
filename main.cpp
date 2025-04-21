#include "basic_input.h"
#include "sheet_handle.h"
#include "student_database.h"
#include <iostream>

using std::cout;
using std::endl;

void showMainMenu() {
  cout << "-------学生管理系统--------\n";
  cout << "1.切换sheet\n";
  cout << "2.新建sheet\n";
  cout << "3.删除sheet\n";
  cout << "4.退出系统" << endl;
}

void execMenuChoose(int choose, bool &quit, StudentDatabase &studentDatabase) {
  switch (choose) {
  case 1:
    changeSheet(studentDatabase);
    break;
  case 2:
    createSheet(studentDatabase);
    break;
  case 3:
    deleteSheet(studentDatabase);
    break;
  case 4:
    quit = true;
    break;
  default:
    cout << "输入有误!" << endl;
  }
}

void runStudentSystem() noexcept {
  StudentDatabase studentDatabase;
  while (true) {
    showMainMenu();
    auto choose = getInteger();
    while (!choose.has_value()) {
      cout << "输入有误!请重新输入:" << endl;
      choose = getInteger();
    }
    bool quit = false;
    execMenuChoose(choose.value(), quit, studentDatabase);
    if (quit) {
      break;
    }
  }
}

int main() {
  try {
    runStudentSystem();
  } catch (const std::bad_alloc &exp) {
    cout << exp.what() << endl;
    cout << "内存不足,程序被迫终止!" << endl;
    return EXIT_FAILURE;
  }
  return 0;
}
