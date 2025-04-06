#include "basic_input.h"
#include <iostream>
#include <limits>
using namespace std;

// "5\n"

// 从键盘上获取一个数字
optional<int> getInteger(istream &in) {
  int result;
  // 读取失败
  if (!(in >> result)) {
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    return nullopt;
  }
  // 判断后续有没有其他字符
  while (in.peek() != '\n') {
    if (!std::isspace(in.get())) {
      in.ignore(numeric_limits<streamsize>::max(), '\n');
      return nullopt;
    }
  }
  return result;
}
