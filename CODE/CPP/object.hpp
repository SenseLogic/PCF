#pragma once

// -- IMPORTS

#include "base.hpp"

// -- TYPES

namespace base
{
    struct OBJECT
    {
        // -- ATTRIBUTES

        uint32_t
            LinkCount,
            PointerCount;

        // -- CONSTRUCTORS

        OBJECT(
            )
        {
            LinkCount = 0;
            PointerCount = 0;
        }

        // ~~

        OBJECT(
            const OBJECT & object
            )
        {
        }

        // -- DESTRUCTORS

        virtual ~OBJECT(
            )
        {
        }

        // -- OPERATORS

        void operator=(
            const OBJECT & object
            )
        {
        }

        // -- OPERATIONS

        void AddLink(
            )
        {
            ++LinkCount;
        }

        // ~~

        void RemoveLink(
            )
        {
            if ( LinkCount > 1 )
            {
                --LinkCount;
            }
            else
            {
                LinkCount = 0;

                delete this;
            }
        }

        // ~~

        void AddPointer(
            )
        {
            ++PointerCount;
        }

        // ~~

        void RemovePointer(
            )
        {
            assert ( PointerCount > 1 );

            --PointerCount;
        }
    };
}
