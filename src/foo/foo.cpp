
#include "../../include/CMakeProject1/foo/foo.h"

Foo::Foo() : bar(1)
{

}

Foo::~Foo()
{
    bar = 0;
}

void Foo::tool()
{
    fmt::print("Using {}...", "fmt::format");
    fmt::print("{}", "\n");
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
