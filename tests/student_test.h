#include "../student.h"
#include <gtest/gtest.h>

class StudentTest : public testing::Test {
protected:
  StudentTest() {
    // stu1 is empty
    stu2.addField(Field({"name", "keli"}));
    stu3.addField(Field({"name", "jack"}));
    stu3.addField(Field({"age", 18}));
  }
  Student stu1;
  Student stu2;
  Student stu3;
};
