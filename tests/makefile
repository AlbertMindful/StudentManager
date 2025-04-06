.PHONY : StudentTest StudentSheetTest  StudentDatabaseTest BasicInputTest
LIB =  -lgtest -lgtest_main
STANDARD = c++20

StudentTest : 
	g++ -o $@ student_test.cpp ../student.cpp $(LIB) -std=$(STANDARD)
StudentSheetTest :
	g++ -o $@ student_sheet_test.cpp $(LIB)  -std=$(STANDARD)
StudentDatabaseTest :
	g++ -o $@  student_database_test.cpp $(LIB) -std=$(STANDARD)
BasicInputTest : 
	g++ -o $@  basic_input_test.cpp ../basic_input.cpp $(LIB) -std=$(STANDARD)
