
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>	// stringstream
#include <iomanip>
#include "myClass.h"

// Output functions ----------
void stringToFile();		// Pass a string to file
void arithmToFile1();		// Pass integers to file: Pass ints to a stringstream object and it to the file.
void arithmToFile2();		// Pass integers to file: Convert ints to std::string, store them in a std::string and pass it to file.
// Input functions -----------
void getStrings();		// Enter a single word or many words from standard input.
void getWholeFile();		// Get all the data from the file
// More ----------------------
void op_overloading();		// Custom operator>> and operator<< functions (operator overloading) to support stream input/output for custom classes. 
void manipulators();		// Use of different manipulators from <iostream> and <iomanip>.

//----------------------------

int main() {

	//stringToFile();
	//arithmToFile1();
	//arithmToFile2();

	//getStrings();

	//op_overloading();
	manipulators();

	system("pause");
	return 0;
}

// Output functions --------------------

void stringToFile() {

	std::string str{ "Hello world !\nGoodbye!" };

	std::ofstream ofile;
	ofile.open("C:\\Users\\Hanks\\Desktop\\files\\Data_0.txt");
	ofile << str << " abc";										// 	if (ofile.is_open()){} else{}
	ofile.close();
}

void arithmToFile1() {

	int a = 64, b = 128, c = 256;

	std::ofstream ofile;
	ofile.open("C:\\Users\\Hanks\\Desktop\\files\\Data_1.txt");
	std::stringstream sstream;									// 	if (ofile.is_open()){} else{}
	sstream << a << " " << b << "\n" << c << "\n";
	ofile << sstream.str();
	ofile.close();
}

void arithmToFile2() {

	int a = 64, b = 128, c = 256;
	std::string str;
	str += std::to_string((unsigned long long)a);
	str += " ";
	str += std::to_string((unsigned long long)b);
	str += "\n";
	str += std::to_string((unsigned long long)c);
	str += "\n";

	std::ofstream ofile;
	ofile.open("C:\\Users\\Hanks\\Desktop\\files\\Data_2.txt");
	ofile << str;											// 	if (ofile.is_open()){} else{}
	ofile.close();
}

// Input functions --------------------

void getStrings() {
	std::cout << "Enter one word: ";
	std::string single;
	std::cin >> single;					// Store a single word (stops at first whitespace character)

	std::cin.ignore();		// https://stackoverflow.com/questions/12691316/getline-does-not-work-if-used-after-some-inputs

	std::cout << "Enter many words: ";
	std::string many;
	std::getline(std::cin, many);		// Store many words in a string (doesn't stops at whitespaces)

	std::cout << "Single word: " << single << std::endl << "Many words: " << many << std::endl;
}

void getWholeFile() {
	std::ifstream ifile("C:\\Users\\Hanks\\Desktop\\files\\Data_2.txt", std::ios::in);		// 	if (ofile.is_open()){} else{}
	
	std::string data;
        std::stringstream sstr;
	
	sstr << ifile.rdbuf();
	data = sstr.str();
	ifile.close();
}

// More -------------------------------

void op_overloading() {
	
	myClass A, B;

	std::cout << "Enter values for objects A and B (x, y): " << std::endl;
	std::cin >> A >> B;
	std::cout << A << " " << B << std::endl;
}

void manipulators() {
	/*
		<iostream>
			std::endl:		Output end-of-line character.
			std::flush:		Tells the stream to flush its internal buffer to the physical device (e.g. the console) immediately.

		<iomanip>
			std::setw():			Sets minimum field width for the next value displayed on the stream (only applies to the next value). Doesn't cause truncation.
			std::left, std::right:	Control justification (right by default). Applies to subsequent outputs.
			std::internal:			Justifies numeric values within the field width (sign is left-justified, number is right-justified). Applies to subsequent outputs. 
			
			Format floating-point values:		(Applies to subsequent outputs)
				std::fixed:													3.14159265358979
				std::scientific:											1.23e5
				std::cout.unsetf(std::ios::fixed | std::ios::scientific):	Fixed or scientific, depending on number size.
			std::setprecision()
			std::showpos, std::noshowpos:		Show + symbols with positive numbers (noshowpos by default).
			
			std::dec, std::oct, std::hex:		Format numbers on decimal, octal or hexadecimal.
			std::showbase, std::nonshowbase:	Displays number base (leading 0 for octals, leading 0x for hexadecimals).
			std::uppercase, std::nouppercase:	Format numbers with uppercase letters.

	*/

	const char * message = "Hi there";
	std::cout << "[" << std::setw(5)  << message << "]" << std::endl;			// std::setw()
	std::cout << "[" << std::setw(10) << message << "]" << std::endl;
	std::cout << std::left;														// std::left;
	std::cout << "[" << std::setw(10) << message << "]" << std::endl;
	std::cout << std::internal;													// std::internal
	std::cout << "[" << std::setw(10) << -1066 << "]" << std::endl << std::endl;
	
	double pi = 3.14159265358979;
	std::cout << pi << std::endl;
	std::cout << std::setprecision(5);											// std::setprecision()
	std::cout << pi << std::endl;
	std::cout << std::fixed;													// std::fixed
	std::cout << pi << std::endl;
	std::cout << std::scientific;												// std::scientific
	std::cout << pi << std::endl;
	std::cout.unsetf(std::ios::fixed | std::ios::scientific);					// std::cout.unsetf()
	std::cout << pi << std::endl;
	std::cout << std::showpos;													// std::showpos
	std::cout << 5 << std::endl;
	std::cout << std::noshowpos;												// std::noshowpos
	std::cout << 5 << std::endl << std::endl;

	int val = 30;
	std::cout << std::dec;														// std::dec
	std::cout << val << std::endl;
	std::cout << std::oct;														// std::oct
	std::cout << val << std::endl;
	std::cout << std::hex;														// std::hex
	std::cout << val << std::endl;
	std::cout << std::uppercase;												// std::uppercase
	std::cout << val << std::endl;
	std::cout << std::nouppercase;												// std::nouppercase
	std::cout << std::showbase;													// std::showbase
	std::cout << val << std::endl;
	std::cout << std::noshowbase;												// std::noshowbase

}
