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
	foo.tool();

	foo.message(projectName);
	foo.message(projectVersion);
	foo.message(projectDescription);
	foo.message(companyName);
	foo.message(projectWebsite);

	foo.returnBar();

	foo.message("\n");
	return 0;
}
