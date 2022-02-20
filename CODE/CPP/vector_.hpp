#pragma once

// -- IMPORTS

#include <vector>

using namespace std;

// -- TYPES

namespace base
{
    template <typename _ELEMENT_>
    struct VECTOR_ :
        public vector<_ELEMENT_>
    {
    };
}
