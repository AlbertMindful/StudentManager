#ifndef __STUDENT_HANDLE__
#define __STUDENT_HANDLE__
#include "student_sheet.h"
void addStudent(std::vector<StudentSheet>::iterator sheet);
void deleteStudent(std::vector<StudentSheet>::iterator sheet);
void findStudent(std::vector<StudentSheet>::iterator sheet);
void searchStudent(std::vector<StudentSheet>::iterator sheet);
void createIndex(std::vector<StudentSheet>::iterator sheet);
void deleteIndex(std::vector<StudentSheet>::iterator sheet);
void setIndex(std::vector<StudentSheet>::iterator sheet);

#endif
