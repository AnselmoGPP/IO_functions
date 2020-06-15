
#include "iolib.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>	// stringstream
#include <iomanip>
#include "myClass.h"


// Output functions ----------
void stringToFile();		
void arithmToFile1();		
void arithmToFile2();		
// Input functions -----------
void getWholeFile();		 
// More ----------------------
void getStrings();
void IO_for_custom_classes();	
void manipulators();            
void file_open_modes();
//----------------------------
std::string getCurrentDirectory();

int main()
{
    std::ofstream ofile("data", std::ios_base::binary);
    double a = 4.2442;
    int b = 84;
    char c[3] = {'a', 'b', 'c'};
    ofile.write((char*)&a, sizeof(double));
    ofile.write((char*)&b, sizeof(int));
    ofile.write(c, 3);
    ofile.close();

    std::ifstream ifile("data", std::ios_base::binary);
    double aa;
    int bb;
    char cc[3];
    ifile.read((char*)&aa, sizeof(double));
    ifile.read((char*)&bb, sizeof(int));
    ifile.read(cc, 3);
    ifile.close();

    std::cout << aa << ' ' << bb << ' ' << cc[0] << ' ' << cc[1] << ' ' << cc[2] << std::endl;
}


int main3() {

	std::cout << "Current directory: " << std::flush << getCurrentDirectory() << std::endl;

	std::cout << "\n\n"
		  << " 0 - Exit \n"
		  // Output to file -----------------
		  << " 1 - stringToFile \n"		// Pass a string to file
		  << " 2 - arithmToFile1 \n"		// Pass integers to file: Pass ints to a stringstream object and it to the file
		  << " 3 - arithmToFile2 \n"		// Pass integers to file: Convert ints to std::string, store them in a std::string and pass it to file
		  // Input to file ------------------
		  << " 4 - getWholeFile \n"		// Get all the data from the file with rdbuf()
		  // More ---------------------------
		  << " 5 - getStrings \n"		// Enter a single word or many words from standard input
		  << " 6 - IO_for_custom_classes \n"	// Custom operator>> and operator<< functions (operator overloading) to support stream input/output for custom classes
		  << " 7 - manipulators \n"		// Use of different manipulators from <iostream> and <iomanip>
		  << " 8 - file_open_modes \n"		// Use some modes for opening a file (in, out, binary, ate, app, trunc)
		  << std::endl;
    int val;

    while(1){

        std::cout << "Enter value: ";
        std::cin >> val;

        switch(val){
	// Output to file
        case 1:
            stringToFile();
            break;
        case 2:
            arithmToFile1();
         break;
        case 3:
            arithmToFile2();
            break;
        case 4:
            getWholeFile();
            break;
        case 5:
            getStrings();
            break;
        case 6:
            IO_for_custom_classes();
            break;
        case 7:
            manipulators();
            break;
	case 8:
	    file_open_modes();
	    break;

        default:
            return 0;
        }

        std::cout << std::endl << "-------------------------" << std::endl;
    }
}

std::string getCurrentDirectory(){

	std::string dir = "";

	// For Windows	
	dir = system("cd");
	
	// For Linux
	dir = system("pwd");
	std::string test = dir.substr(0, dir.size() - 10);
	dir = test;
	//std::cout << dir.substr(0, dir.size() - 10) << std::endl;
	//std::cout << dir.size() << std::endl;

	return dir;
}

// Output file functions --------------------

void stringToFile() {

	std::string str{ "Hello world !\nGoodbye!" };

	std::ofstream ofile;
	ofile.open("C:\\Users\\Hanks\\Desktop\\files\\Data_0.txt");

    if(ofile.is_open()){
        ofile << str << " abc";
        ofile.close();
    }
    else std::cout << "Cannot open file" << std::endl;
}

void arithmToFile1() {

	int a = 64, b = 128, c = 256;

	std::ofstream ofile;
	ofile.open("C:\\Users\\Hanks\\Desktop\\files\\Data_1.txt");
    	std::stringstream sstream;

    	if(ofile.is_open()){
        	sstream << a << " " << b << "\n" << c << "\n";
        	ofile << sstream.str();
        	ofile.close();
    	}
    	else std::cout << "Cannot open file" << std::endl;
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

	std::ofstream ofile("C:\\Users\\Hanks\\Desktop\\files\\Data_2.txt");

	if(ofile.is_open())
	{
        	ofile << str;
        	ofile.close();
    	}
    	else std::cout << "Cannot open file" << std::endl;
}

// Input file functions --------------------

void getWholeFile() {
    std::ifstream ifile("C:\\Users\\Hanks\\Desktop\\files\\Data_2.txt", std::ios::in);		// 	if (ofile.is_open()){} else{}

    std::string data;
    std::stringstream sstr;

    if(ifile.is_open()){
        sstr << ifile.rdbuf();
        data = sstr.str();
        ifile.close();
    }
    else std::cout << "Cannot open file" << std::endl;
}

// More -------------------------------

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

void IO_for_custom_classes() {
	
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
            std::setprecision()                 Number of digits after decimal point (for fixed and scientific formats) or number of significant digits (for general format)
			std::showpos, std::noshowpos:		Show + symbols with positive numbers (noshowpos by default).
			
			std::dec, std::oct, std::hex:		Format numbers on decimal, octal or hexadecimal.
			std::showbase, std::nonshowbase:	Displays number base (leading 0 for octals, leading 0x for hexadecimals).
			std::uppercase, std::nouppercase:	Format numbers with uppercase letters.

	*/

    // Allignment
	const char * message = "Hi there";
	std::cout << "[" << std::setw(5)  << message << "]" << std::endl;			// std::setw()
	std::cout << "[" << std::setw(10) << message << "]" << std::endl;
    std::cout << std::left;														// std::left;  (by default, it's std::right)
	std::cout << "[" << std::setw(10) << message << "]" << std::endl;
    std::cout << std::setw(10) << 123 << std::setw(10) << 456 << std::setw(10) << 789 << std::endl;
	std::cout << std::internal;													// std::internal
	std::cout << "[" << std::setw(10) << -1066 << "]" << std::endl << std::endl;

    // Precision formats
	double pi = 3.14159265358979;
	std::cout << pi << std::endl;
	std::cout << std::setprecision(5);											// std::setprecision()
	std::cout << pi << std::endl;
	std::cout << std::fixed;													// std::fixed
	std::cout << pi << std::endl;
	std::cout << std::scientific;												// std::scientific
	std::cout << pi << std::endl;
	std::cout.unsetf(std::ios::fixed | std::ios::scientific);					// std::cout.unsetf() (re-stablish general formatting)
	std::cout << pi << std::endl;
	std::cout << std::showpos;													// std::showpos
	std::cout << 5 << std::endl;
	std::cout << std::noshowpos;												// std::noshowpos
	std::cout << 5 << std::endl << std::endl;

    // Base formats
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

void file_open_modes(){
	// pag 62	
	std::string dir = getCurrentDirectory() + "//Data_0.txt";
	std::cout << dir << std::endl;	
	std::cout << dir.size() << std::endl;
	//std::fstream(getCurrentDirectory + "\\Data_0.txt");
}
