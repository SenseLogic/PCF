#pragma once

// -- IMPORTS

#include <map>

using namespace std;

// -- TYPES

namespace base
{
    template <typename _KEY_, typename _ELEMENT_>
    struct MAP_ :
        public map<_KEY_, _ELEMENT_>
    {
    };
}
