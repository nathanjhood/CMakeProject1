/*******************************************************************************
 * @file foo.h
 * @author Nathan J. Hood ( @StoneyDSP )
 * @brief Declaration of "foo".
 * @version 1.0.0.0
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 *******************************************************************************
*/

#pragma once

#ifndef FOO_H_INCLUDED
#define FOO_H_INCLUDED

#if defined(_WIN32)
#  if defined(EXPORTING_FOO)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

// Third-Party packages.
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"
#include "fmt/printf.h"

/** Foo
* @brief Message handler using fmt library.
*/
class Foo
{
public:
    Foo();

    ~Foo();

    void tool();

    void message(const char* string);

    void returnBar();

private:

    /** bar
    * @brief Generic integer value for testing purposes.
    */
    int bar {0};
};

#endif // FOO_H_INCLUDED
