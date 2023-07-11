#include "../../include/application/runtime/main.h"

int main()
{
    // application::Configuration Configuration;

#ifndef APPLICATION_CONFIGURATION_H_INCLUDED

    std::cout << "cli configuration header not found!" << std::endl;
    std::cout << "Nothing to report." << "\n" << std::endl;

#else

    #ifdef application_VERSION_TWEAK

    #  define application_VERSION_INFO_CHECKED 1

    char const* versionString = "Version" ":" " " application_VERSION;
    char const* sourceString = "Source" ":" " " application_REPOSITORY;

    std::cout << "\n" << std::endl;
    std::cout << "StoneyDSP" << std::endl;
    std::cout << "CMakeProject1" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "A simple CMake project for testing build configs, toolchains, and more." << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "MIT License" << std::endl;
    std::cout << "Copyright (c) 2022 - 2023, StoneyDSP" << std::endl;
    std::cout << "All rights reserved." << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << versionString << std::endl;
    std::cout << sourceString << std::endl;
    std::cout << "\n" << std::endl;

    #else

    #  define application_VERSION_INFO_CHECKED 0

    std::cout << "Version header not found!" << std::endl;
    std::cout << "Nothing to report." << "\n" << std::endl;

    #endif

#endif // APPLICATION_CONFIGURATION_H_INCLUDED

    std::cout << "Press 'enter' to exit the program." << "\n" << std::endl;
    std::cin.get();
    return 0;
};
