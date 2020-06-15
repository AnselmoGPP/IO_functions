#pragma once

#include <iostream>

class myClass {
public:
	int x;
	int y;
};

std::istream & operator >> (std::istream & is, myClass & p) {
	is >> p.x >> p.y;
	return is;
}

std::ostream & operator << (std::ostream & os, const myClass & p) {
	os << "[" << p.x << ", " << p.y << "]";
	return os;
}