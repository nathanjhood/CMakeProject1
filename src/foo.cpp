
#include "foo.h"

Foo::Foo() : bar(1)
{

}

Foo::~Foo()
{
    bar = 0;
}

int Foo::returnBar()
{
    return bar;
}
