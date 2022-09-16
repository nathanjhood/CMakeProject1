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

// Including locally-defined class "Foo" which returns "bar"
#ifdef USE_FOO

    #include "foo.h"

#else

    #include <iostream>
    #include <string.h>

    class Foo
    {
    public:
        Foo() : bar{5} {}

        ~Foo(){ bar = 0; }

        void tool() { std::cout << "Using std::iostream..." << std::endl; }

        void message(std::string string) { std::cout << string << std::endl; }

        void returnBar() { std::cout << bar << std::endl; }

    private:
        int bar {0};
    };

#endif

/** main.
 * @brief Entry point for program execution.
 *
 * @param argc Number of strings in array argv.
 * @param argv Array of command-line argument strings.
 * @return Exit code.
 */
int main(int argc, char** argv);

/** Foo.
 * @brief Object for handling config.h messages
 *
 */
Foo foo;

#endif // MAIN_H_INCLUDED
