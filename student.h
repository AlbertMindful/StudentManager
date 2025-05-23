#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <algorithm>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

class GetVisitor {
public:
  template <typename T> decltype(auto) operator()(T &value) { return value; }
  template <typename T> decltype(auto) operator()(const T &value) const {
    return value;
  }
};

struct Field {
  using Var = std::variant<std::string, int, double, bool>;
  static const std::vector<std::string> FieldTypes;
  std::string name;
  Var value;
  template <typename T1, typename T2>
  requires std::is_convertible_v<T1, decltype(name)> &&
      std::is_convertible_v<T2, decltype(value)>
      Field(T1 &&fieldName, T2 &&fieldValue)
  noexcept
      : name(std::forward<T1>(fieldName)), value(std::forward<T2>(fieldValue)) {
  }
  bool operator==(const Field &rValue) const noexcept {
    return rValue.name == name && rValue.value == value;
  }
  static std::optional<Var> convertToVar(const std::string &fieldType) {
    size_t index = FieldTypes.size();
    for (size_t i = 0; i < FieldTypes.size(); ++i) {
      if (FieldTypes[i] == fieldType) {
        index = i;
        break;
      }
    }
    Var result;
    switch (index) {
    case 0:
      result = "";
      break;
    case 1:
      result = 0;
      break;
    case 2:
      result = 0.0;
      break;
    case 3:
      result = false;
      break;
    default:
      return std::nullopt;
    }
    return result;
  }
};

class Student {
public:
  constexpr static std::size_t MaxFieldNumber = 128;
  template <typename T>
  requires std::is_convertible_v<T, Field>
  void addField(T &&field) {
    if (studentInfo.size() < MaxFieldNumber &&
        !findField(field.name).has_value()) {
      studentInfo.emplace_back(std::forward<T>(field));
    }
  }
  // perfect forward，the type of fieldName and value is a reference.
  template <typename T1, typename T2>
  requires std::is_convertible_v<T1, std::string> &&
      std::is_convertible_v<T2, Field::Var>
  void addField(T1 &&fieldName, T2 &&value) {
    addField(Field(std::forward<T1>(fieldName), std::forward<T2>(value)));
  }
  void removeField(const std::string &fieldName) {
    auto it = findField(fieldName);
    if (!it.has_value()) {
      throw std::out_of_range("no " + fieldName + " field");
    }
    studentInfo.erase(it.value());
  }
  // 找不到字段则抛出异常(这里只能抛出异常，引用必须绑定对象)
  const Field::Var &getFieldValue(const std::string &fieldName) const {
    auto it = findField(fieldName);
    if (!it.has_value()) {
      throw std::out_of_range("Field not found" + fieldName);
    }
    return it.value()->value;
  }
  // 去除常量性
  Field::Var &getFieldValue(const std::string &fieldName) {
    return const_cast<Field::Var &>(
        static_cast<const Student &>(*this).getFieldValue(fieldName));
  }
  const Field::Var &operator[](const std::string &fieldName) const {
    return getFieldValue(fieldName);
  }
  Field::Var &operator[](const std::string &fieldName) {
    return getFieldValue(fieldName);
  }
  template <typename T1, typename T2>
  requires(std::is_same_v<T2, int> || std::is_same_v<T2, double> ||
           std::is_same_v<T2, std::string> || std::is_same_v<T2, bool>) &&
      std::is_convertible_v<T1, std::string> void setFieldValue(T1 &&fieldName,
                                                                T2 &&value) {
    if (!isExist(fieldName)) {
      // 不存在字段则自动创建
      addField(Field(std::forward<T1>(fieldName), std::forward<T2>(value)));
      return;
    }
    auto it = findField(fieldName);
    it.value()->value = value;
  }
  std::size_t size() const noexcept { return studentInfo.size(); }
  std::optional<std::vector<std::string>> getFieldNames() const {
    std::vector<std::string> result;
    for (const auto &field : studentInfo) {
      result.emplace_back(field.name);
    }
    return result.size()
               ? std::optional<std::vector<std::string>>(std::move(result))
               : std::nullopt;
  }
  std::optional<std::vector<int>> getFieldTypeIndexs() const {
    std::vector<int> result;
    for (const auto &field : studentInfo) {
      result.emplace_back(field.value.index());
    }
    return result.size() ? std::optional<std::vector<int>>(std::move(result))
                         : std::nullopt;
    ;
  }
  bool isExist(const std::string &fieldName) const {
    return findField(fieldName) != std::nullopt;
  }

private:
  std::optional<std::vector<Field>::const_iterator>
  findField(const std::string &fieldName) const {
    auto pred = [&fieldName](const Field &field) {
      return fieldName == field.name;
    };
    auto it = std::find_if(studentInfo.begin(), studentInfo.end(), pred);
    return studentInfo.end() == it
               ? std::optional<std::vector<Field>::const_iterator>(std::nullopt)
               : std::optional<std::vector<Field>::const_iterator>(it);
  }
  std::optional<std::vector<Field>::iterator>
  findField(const std::string &fieldName) {
    auto cit = static_cast<const Student &>(*this).findField(fieldName);
    if (!cit.has_value()) {
      return std::nullopt;
    }
    return studentInfo.begin() + (cit.value() - studentInfo.cbegin());
  }
  friend bool operator==(const Student &stu1, const Student &stu2);
  std::vector<Field> studentInfo;
};

bool operator==(const Student &stu1, const Student &stu2);

#endif
