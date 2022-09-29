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
	foo.tool();

	foo.message(PROJECT_NAME);
	foo.message(PROJECT_VERSION);
	foo.message(PROJECT_DESCRIPTION);
	foo.message(PROJECT_VENDOR);
	foo.message(PROJECT_HOMEPAGE_URL);

	foo.returnBar();

	foo.message("\n");
	return 0;
}
