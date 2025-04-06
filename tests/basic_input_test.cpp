#include "../basic_input.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

TEST(GetIntegerTest, HaveNotBlankRedundantInput_ReturnNullopt) {
  std::vector<std::string> strsToTest = {"5 a", "63sd", "23,a"};
  std::istringstream strIn;
  std::optional<int> result;
  for (auto &strToTest : strsToTest) {
    std::string strTested = strToTest + '\n';
    strIn.str(strTested);
    ASSERT_EQ(strIn.str(), strTested);
    result = getInteger(strIn);
    EXPECT_EQ(result, std::nullopt);
  }
}

TEST(GetIntegerTest, CorrectInput_ReturnCorrectValue) {
  std::istringstream strIn;
  std::vector<std::string> strsToTest = {"5", "5 ", "524\t", "23   "};
  std::optional<int> result;
  // 测试
  for (auto &strToTest : strsToTest) {
    strToTest += '\n';
    strIn.str(strToTest);
    ASSERT_EQ(strIn.str(), strToTest);
    int intToTest = std::atoi(strToTest.c_str());
    result = getInteger(strIn);
    ASSERT_EQ(result.has_value(), true);
    EXPECT_EQ(result.value(), intToTest);
  }
}

TEST(GetIntegerTest, BeNotCorrectInputAtTheBegin_ReturnNullopt) {
  std::vector<std::string> strsToTest = {"a", "", "a124", "da34"};
  std::istringstream strIn;
  std::optional<int> result;
  for (auto &strToTest : strsToTest) {
    strToTest += '\n';
    strIn.str(strToTest);
    ASSERT_EQ(strIn.str(), strToTest);
    result = getInteger(strIn);
    EXPECT_EQ(result, std::nullopt);
  }
}
