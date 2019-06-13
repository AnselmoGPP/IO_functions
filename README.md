# IO-functions

Compilation of I/O functions that may be useful in different circumstances.

<< test.cpp, myClass.h >>

test.cpp contains a series of functions with different IO implementations. Any of them can be called from main() by uncommenting the corresponding function call. They are:
- Output functions:

void stringToFile():    Pass a string to file

void arithmToFile1():   Pass integers to file. Pass ints to a stringstream object and it to the file.

void arithmToFile2():   Pass integers to file. Convert ints to std::string, store them in a std::string and pass it to file.

- Input functions:

void getStrings():      Enter a single word or many words from standard input.

void getWholeFile():    Get all data that is in a file using rdbuf() and stringstream.

- More:

void op_overloading():  Custom operator>> and operator<< functions (operator overloading) to support stream input/output for custom classes. 

void manipulators():    Use of different manipulators from "iostream" and "iomanip" libraries.
