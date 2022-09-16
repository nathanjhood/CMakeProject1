/*******************************************************************************
 * @file main.h
 * @author Nathan J. Hood ( @StoneyDSP )
 * @brief Declares the main execution routine of the application.
 * @version 1.0.0.0
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 * Reference headers your program requires here.
 *
 *******************************************************************************
*/

#pragma once

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// Global app config header.
#include "CMakeProject1Config.h"

// Standard C++ Library.
#include <assert.h>
#include <iostream>
#include <string.h>

// Third-Party packages.
//#include <fmt/format.h>

#include "foo.h"

/** main.
 * @brief Entry point for program execution.
 *
 * @param argc Number of strings in array argv.
 * @param argv Array of command-line argument strings.
 * @return Exit code.
 */
int main(int argc, char** argv);

Foo foo;

#endif // MAIN_H_INCLUDED
