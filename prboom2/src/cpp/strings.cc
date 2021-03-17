//
// Created by kyle on 3/17/21.
//

#include "chars.hh"
#include "strings.hh"
int str::caseInsensitiveCompare(std::string_view s1, std::string_view s2)
{
    for (int i = 0; i < std::min(s1.length(), s2.length()); i++)
    {
        if (chr::downcase(s1[i]) != chr::downcase(s2[i]))
        {
            return s2[i] - s1[i];
        }
    }

    return 0;
}
