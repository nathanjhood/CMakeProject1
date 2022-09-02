/*******************************************************************************
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief Defines the main execution routine of the application.
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 *******************************************************************************
*/

#include "main.h"

/** Main.
 * @brief Entry point for program execution.
 *
 * @param argc int
 * @param argv char**
 * @return int
 */
int main(int argc, char** argv)
{
	fmt::print("Hello, from {}!", projectName); std::cout << std::endl;
	fmt::print("Version {}!", projectVersion); std::cout << std::endl;
	fmt::print("Description: {}!", projectDescription); std::cout << std::endl;
	fmt::print("Bought to you by {}!", companyName); std::cout << std::endl;
	fmt::print("Find out more at {}!", projectWebsite); std::cout << std::endl;

	std::cout << std::endl;

	return 0;
}
