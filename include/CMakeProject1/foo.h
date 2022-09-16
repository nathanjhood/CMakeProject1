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

class Foo
{
    Foo() : bar(1)
    {}
    ~Foo()
    {
        bar = 0;
    }

    int returnBar()
    {
        return bar;
    }

    int bar {1};
};

#endif // FOO_H_INCLUDED
