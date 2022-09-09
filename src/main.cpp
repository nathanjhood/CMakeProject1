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

/** main.
 * @brief Entry point for program execution.
 *
 * @param argc Number of strings in array argv.
 * @param argv Array of command-line argument strings.
 * @return Exit code.
 */
int main(int argc, char** argv)
{
	fmt::print("Hello, from {}!", (ProjectInfo::projectName)); std::cout << std::endl;
	fmt::print("Version {}!", (ProjectInfo::projectVersion)); std::cout << std::endl;
	fmt::print("Description: {}!", ProjectInfo::projectDescription); std::cout << std::endl;
	fmt::print("Bought to you by {}!", ProjectInfo::companyName); std::cout << std::endl;
	fmt::print("Find out more at {}!", ProjectInfo::projectWebsite); std::cout << std::endl;

	std::cout << std::endl;

	return 0;
}
