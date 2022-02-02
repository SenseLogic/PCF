#pragma once

// -- IMPORTS

#include "base.hpp"
#include "stream.hpp"
#include "property.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "vector_.hpp"

// -- TYPES

struct IMAGE :
    public OBJECT
{
    // -- ATTRIBUTES

    string
        Name,
        Role,
        Format;
    VECTOR_<LINK_<PROPERTY>>
        PropertyVector;
    VECTOR_<uint8_t>
        ByteVector;

    // -- CONSTRUCTORS

    IMAGE(
        ) :
        OBJECT(),
        Name(),
        Role(),
        Format(),
        PropertyVector(),
        ByteVector()
    {
    }

    // ~~

    IMAGE(
        const IMAGE & image
        ) :
        OBJECT( image ),
        Name( image.Name ),
        Role( image.Role ),
        Format( image.Format ),
        PropertyVector( image.PropertyVector ),
        ByteVector( image.ByteVector )
    {
    }

    // -- DESTRUCTORS

    virtual ~IMAGE(
        )
    {
    }

    // ~~

    IMAGE & operator=(
        const IMAGE & image
        )
    {
        Name = image.Name;
        Role = image.Role;
        Format = image.Format;
        PropertyVector = image.PropertyVector;
        ByteVector = image.ByteVector;

        return *this;
    }

    // -- INQUIRIES

    void Write(
        STREAM & stream
        )
    {
        stream.WriteText( Name );
        stream.WriteText( Role );
        stream.WriteText( Format );
        stream.WriteObjectVector( PropertyVector );
        stream.WriteScalarVector( ByteVector );
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
        )
    {
        stream.ReadText( Name );
        stream.ReadText( Role );
        stream.ReadText( Format );
        stream.ReadObjectVector( PropertyVector );
        stream.ReadScalarVector( ByteVector );
    }
};
