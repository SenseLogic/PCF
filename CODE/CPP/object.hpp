#pragma once

// -- IMPORTS

#include "base.hpp"

// -- TYPES

struct OBJECT
{
    // -- ATTRIBUTES

    uint64_t
        LinkCount;

    // -- CONSTRUCTORS

    OBJECT(
        )
    {
        LinkCount = 0;
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
};
