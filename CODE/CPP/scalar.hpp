#pragma once

// -- IMPORTS

#include "base.hpp"

// -- TYPES

namespace base
{
    union SCALAR
    {
        bool
            Boolean;
        char
            Character;
        uint8_t
            Natural8;
        uint16_t
            Natural16;
        uint32_t
            Natural32;
        uint64_t
            Natural64;
        int8_t
            Integer8;
        int16_t
            Integer16;
        int32_t
            Integer32;
        int64_t
            Integer64;
        float
            Real32;
        double
            Real64;
        uint8_t
            OneByteVector[ 1 ];
        uint8_t
            TwoByteVector[ 2 ];
        uint8_t
            FourByteVector[ 4 ];
        uint8_t
            EightByteVector[ 8 ];
    };
}
