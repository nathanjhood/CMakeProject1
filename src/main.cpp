

// CMakeProject1.cpp : Defines the entry point for the application.

#include "main.h"

#ifndef CPPUNIT_ASSERTER_H
#else CPPUNIT_ASSERTER_H
#endif CPPUNIT_ASSERTER_H

int main()
{
	fmt::print("Hello, from {}!", projectName); std::cout << std::endl;
	fmt::print("Version {}!", projectVersion); std::cout << std::endl;
	fmt::print("Description: {}!", projectDescription); std::cout << std::endl;
	fmt::print("Bought to you by {}!", companyName); std::cout << std::endl;
	fmt::print("Find out more at {}!", projectWebsite); std::cout << std::endl;
	
	std::cout << std::endl;

	return 0;
}
