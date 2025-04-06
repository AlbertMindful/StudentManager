#ifndef __BASIC_INPUT_H__
#define __BASIC_INPUT_H__
#include <iostream>
#include <optional>
// 从键盘上获取一个数字
std::optional<int> getInteger(std::istream &in = std::cin);

#endif
