#ifndef __SHEET_HANDLE_H__
#define __SHEET_HANDLE_H__
#include "student_database.h"

void deleteSheet(StudentDatabase &studentDatabase);
void changeSheet(StudentDatabase &studentDatabase);
void createSheet(StudentDatabase &studentDatabase) noexcept;
void createSheetStructure(Student &studentTemplate);
bool showSheetNames(const StudentDatabase &studentDatabase);
void handleSingleSheet(std::vector<StudentSheet>::iterator sheet);

#endif
