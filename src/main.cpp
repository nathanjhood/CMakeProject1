/*******************************************************************************
 * @file main.cpp
 * @author Nathan J. Hood ( @StoneyDSP )
 * @brief Defines the main execution routine of the application.
 * @version 1.0.0.0
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 *******************************************************************************
*/

#include "main.h"

// Global app config header.
#include "CMakeProject1Config.h"

/** main.
 * @brief Entry point for program execution.
 *
 * @param argc Number of strings in array argv.
 * @param argv Array of command-line argument strings.
 * @return Exit code.
 */
int main(int argc, char** argv)
{
	// fmt::print("Using {}...", fmt); std::cout << std::endl;
	// fmt::print("Hello, from {}!", projectName); std::cout << std::endl;
	// fmt::print("Version {}!", projectVersion); std::cout << std::endl;
	// fmt::print("Description: {}!", projectDescription); std::cout << std::endl;
	// fmt::print("Bought to you by {}!", companyName); std::cout << std::endl;
	// fmt::print("Find out more at {}!", projectWebsite); std::cout << std::endl;

	std::cout << "Using std::cout..." << std::endl;
	std::cout << projectName << std::endl;
	std::cout << projectVersion << std::endl;
	std::cout << projectDescription << std::endl;
	std::cout << companyName << std::endl;
	std::cout << projectWebsite << std::endl;

	std::cout << std::endl;

	return 0;
}
