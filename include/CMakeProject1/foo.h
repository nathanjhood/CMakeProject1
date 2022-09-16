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

// Third-Party packages.
#include <fmt/format.h>

class Foo
{
public:
    Foo();

    ~Foo();

    void message(const char* string);

    void returnBar();

private:

    int bar {1};
};

#endif // FOO_H_INCLUDED
