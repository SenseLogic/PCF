#pragma once

// -- IMPORTS

#include <map>

// -- TYPES

template <typename _KEY_, typename _ELEMENT_>
struct MAP_ :
    public std::map<_KEY_, _ELEMENT_>
{
};
