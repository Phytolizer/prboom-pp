//
// Created by kyle on 3/17/21.
//

#include <cctype>

#include "chars.hh"

char chr::downcase(char c)
{
    return static_cast<char>(std::tolower(static_cast<int>(c)));
}
