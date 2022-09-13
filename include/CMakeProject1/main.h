/*******************************************************************************
 * @file main.h
 * @author your name (you@domain.com)
 * @brief Reference headers your program requires here.
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 *******************************************************************************
*/

#pragma once

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// Global app config header.
#include <CMakeProject1Config.h>

// Standard C++ Library.
#include <assert.h>
#include <iostream>
#include <string.h>

// Third-Party packages.
#include <fmt/format.h>

/** main.
 * @brief Entry point for program execution.
 *
 * @param argc Number of strings in array argv.
 * @param argv Array of command-line argument strings.
 * @return Exit code.
 */
int main(int argc, char** argv);

#endif // MAIN_H_INCLUDED
