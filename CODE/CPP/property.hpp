#pragma once

// -- IMPORTS

#include "base.hpp"
#include "stream.hpp"
#include "object.hpp"

// -- TYPES

struct PROPERTY :
    public OBJECT
{
    // -- ATTRIBUTES

    string
        Name,
        Value,
        Format;

    // -- CONSTRUCTORS

    PROPERTY(
        ) :
        Name(),
        Value(),
        Format()
    {
    }

    // -- DESTRUCTORS

    virtual ~PROPERTY(
        )
    {
    }

    // -- INQUIRIES

    void Write(
        STREAM & stream
        )
    {
        stream.WriteText( Name );
        stream.WriteText( Value );
        stream.WriteText( Format );
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
        )
    {
        stream.ReadText( Name );
        stream.ReadText( Value );
        stream.ReadText( Format );
    }
};
