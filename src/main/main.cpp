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

/** main.
 * @brief Entry point for program execution.
 * @return Exit code.
 */
int main()
{
	// Confirm is using "std::iostream" or "fmt::format"...
	foo.tool();

	// Gather variables from configuration process into an array...
	std::string text[] = {
		"\n",
		PROJECT_NAME,
		PROJECT_VERSION,
		PROJECT_VENDOR,
		PROJECT_HOMEPAGE_URL,
		PROJECT_DESCRIPTION
	};

	// Cycle-print through the variables using a ranged "for" loop...
	for (const auto& text : text)
	{
		foo.message(text);
	}

	// Random variable for testing, etc...
	foo.returnBar();

	// Line break...
	foo.message("\n");

	// Keep app running (if you want...)
	// while (true)
	// {
	// }

	// Exit application...
	return 0;
}
