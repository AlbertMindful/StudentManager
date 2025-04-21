#include "student_test.h"
#include "../student.h"
#include <gtest/gtest.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

TEST_F(StudentTest, DefaultConstruct_SizeIsZero) { EXPECT_EQ(stu1.size(), 0); }

TEST_F(StudentTest, AddFieldNotToExist_SizeImcreaseByOne) {
  EXPECT_EQ(stu2.size(), 1);
  EXPECT_EQ(stu3.size(), 2);
}

TEST_F(StudentTest, AddFieldToExist_SizeUnchange) {
  stu2.addField(Field("name", "jay"));
  EXPECT_EQ(stu2.size(), 1);
  stu3.addField(Field("age", 20));
  EXPECT_EQ(stu3.size(), 2);
}

TEST_F(StudentTest, AddFieldToExist_FieldDoNotChange) {
  stu2.addField("name", "jay");
  EXPECT_EQ(std::get<std::string>(stu2["name"]), "keli");
  stu3.addField("age", 20);
  EXPECT_EQ(std::get<int>(stu3["age"]), 18);
}

TEST_F(StudentTest, AddFieldNotToExist_FieldAdded) {
  stu2.addField("age", 20);
  EXPECT_EQ(std::get<int>(stu2["age"]), 20);
  stu2.addField("birthday", 2007);
  EXPECT_EQ(std::get<int>(stu2["birthday"]), 2007);
  stu3.addField("birthday", 2007);
  EXPECT_EQ(std::get<int>(stu3["birthday"]), 2007);
}

TEST_F(StudentTest, FieldExist_IsExistIsTrue) {
  EXPECT_EQ(stu2.isExist("name"), true);
  EXPECT_EQ(stu3.isExist("name"), true);
  EXPECT_EQ(stu3.isExist("age"), true);
}

TEST_F(StudentTest, FieldDoNotExist_IsExistIsFalse) {
  EXPECT_EQ(stu2.isExist("age"), false);
  EXPECT_EQ(stu2.isExist("birthday"), false);
  EXPECT_EQ(stu3.isExist(""), false);
}

TEST_F(StudentTest, RemoveFieldToExist_SizeDecreaseByOne) {
  stu2.removeField("name");
  EXPECT_EQ(stu2.size(), 0);
  stu3.removeField("name");
  EXPECT_EQ(stu3.size(), 1);
  stu3.removeField("age");
  EXPECT_EQ(stu3.size(), 0);
}

TEST_F(StudentTest, RemoveFieldNotToExist_SizeUnchangeAndThrowException) {
  EXPECT_THROW(stu2.removeField("age"), std::out_of_range);
  EXPECT_EQ(stu2.size(), 1);
  EXPECT_THROW(stu3.removeField("birthday"), std::out_of_range);
  EXPECT_EQ(stu3.size(), 2);
  EXPECT_THROW(stu2.removeField(""), std::out_of_range);
  EXPECT_EQ(stu2.size(), 1);
}

TEST_F(StudentTest, RemoveFieldToExist_FieldIsDeleted) {
  stu2.removeField("name");
  EXPECT_EQ(stu2.isExist("name"), false);
  stu3.removeField("age");
  EXPECT_EQ(stu3.isExist("age"), false);
}

TEST_F(StudentTest, GetFieldValueNotToExist_ThrowException) {
  EXPECT_THROW(stu2["test"], std::out_of_range);
  EXPECT_THROW(stu2[""], std::out_of_range);
}

TEST_F(StudentTest, GetFieldValueToExist_ReturnCorrectValue) {
  EXPECT_EQ(std::get<std::string>(stu2["name"]), "keli");
  EXPECT_EQ(std::get<std::string>(stu3["name"]), "jack");
  EXPECT_EQ(std::get<int>(stu3["age"]), 18);
}

TEST_F(StudentTest, GetFieldNamesNotToBeEmpty_ReturnCorrectNames) {
  EXPECT_EQ(stu2.getFieldNames().value(), std::vector<std::string>{"name"});
  std::vector<std::string> expect = {"name", "age"};
  EXPECT_EQ(stu3.getFieldNames().value(), expect);
}

TEST_F(StudentTest, GetFieldNamesToBeEmpty_ReturnNullopt) {
  EXPECT_EQ(stu1.getFieldNames(), std::nullopt);
}

TEST_F(StudentTest, GetFieldTypeIndexsToBeEmpty_ReturnNullopt) {
  EXPECT_EQ(stu1.getFieldTypeIndexs(), std::nullopt);
}

TEST_F(StudentTest, GetFieldTypeIndexsNotToBeEmpty_ReturnCorrectIndexs) {
  EXPECT_EQ(stu2.getFieldTypeIndexs(), std::vector<int>{0});
  std::vector<int> expect = {0, 1};
  EXPECT_EQ(stu3.getFieldTypeIndexs(), expect);
}

TEST(ConvertToVarTest, EmptyString_ReturnNullopt) {
  EXPECT_EQ(Field::convertToVar(""), std::nullopt);
}

TEST(ConvertToVarTest, TypeOfNoExisting_ReturnNullopt) {
  EXPECT_EQ(Field::convertToVar("M"), std::nullopt);
  EXPECT_EQ(Field::convertToVar("W"), std::nullopt);
}

TEST(ConvertToVarTest, CorrectInput_ReturnVarOfCorrectType) {
  std::optional<Field::Var> result = Field::convertToVar("C");
  ASSERT_EQ(result.has_value(), true);
  EXPECT_EQ(std::get<std::string>(result.value()), "");
  result = Field::convertToVar("N");
  ASSERT_EQ(result.has_value(), true);
  EXPECT_EQ(std::get<int>(result.value()), 0);
  result = Field::convertToVar("F");
  ASSERT_EQ(result.has_value(), true);
  EXPECT_EQ(std::get<double>(result.value()), 0.0);
  result = Field::convertToVar("L");
  ASSERT_EQ(result.has_value(), true);
  EXPECT_EQ(std::get<bool>(result.value()), false);
}
