
#include "foo.h"

Foo::Foo() : bar(1)
{

}

Foo::~Foo()
{
    bar = 0;
}

void Foo::message(const char* string = {"null"})
{
    fmt::print("{}", string);
    fmt::print("{}", "\n");
}

void Foo::returnBar()
{
    fmt::print("Foo::bar equals {}", bar);
}
