#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
#include <iostream>
#include <stdexcept>
#pragma once

namespace Utils
{
	//removes all whitespace from the string and returns a new string
	std::string removeWhiteSpace(std::string s);
	//copys the string from start until the next white space and returns as a new string
	std::string copyUntilNextWhiteSpace(std::string s, size_t start = 0);
	//not templated because each function to turn a string into the various number type has
	//a diffrent name would have meant lots of template specilization one for each number type
	float getFloatFromStringWPrefix(std::string s, std::string preFix);
	int getIntFromStringWPreFix(std::string s, std::string preFix);
}
#endif
