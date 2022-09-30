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

    #include "../foo/foo.h"

#else

    #include <iostream>
    #include <string.h>

    class Foo
    {
    public:
        inline Foo() : bar(0) {}

        inline ~Foo() noexcept { bar = 0; }

        inline void tool() { std::cout << "Using std::iostream..." << std::endl; }

        inline void message(const char* string = { "null" }) { std::cout << string << std::endl; }

        inline void message(std::string string = { "null" }) { std::cout << string << std::endl; }

        //inline void incBar(int inc) { bar += inc; }

        inline void returnBar() { std::cout << "Foo::bar is " << bar << std::endl; }

    private:
        int bar {0};
    };

#endif

/** main.
 * @brief Entry point for program execution.
 * @return Exit code.
 */
int main();

/** Foo.
 * @brief Object for handling config.h messages
 *
 */
Foo foo;

#endif // MAIN_H_INCLUDED
