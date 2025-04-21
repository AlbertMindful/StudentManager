LIB =  -lgtest -lgtest_main
STANDARD = c++20

StudentTest : student_test.cpp ../student.cpp
	g++ -o $@ student_test.cpp ../student.cpp $(LIB) -std=$(STANDARD)
StudentSheetTest : student_sheet_test.cpp
	g++ -o $@ student_sheet_test.cpp $(LIB)  -std=$(STANDARD)
StudentDatabaseTest : student_database_test.cpp
	g++ -o $@  student_database_test.cpp $(LIB) -std=$(STANDARD)
BasicInputTest : basic_input_test.cpp ../basic_input.cpp
	g++ -o $@  basic_input_test.cpp ../basic_input.cpp $(LIB) -std=$(STANDARD)
