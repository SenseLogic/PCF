#pragma once

// -- IMPORTS

#include "base.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "object.hpp"

// -- TYPES

struct COMPONENT :
    public OBJECT
{
    // -- ATTRIBUTES

    string
        Name;
    double
        Precision;
    uint16_t
        BitCount,
        Compression;
    double
        MinimumValue,
        OneOverPrecision;

    // -- CONSTRUCTORS

    COMPONENT(
        ) :
        Name(),
        Precision( 0.0 ),
        BitCount( 0 ),
        Compression( COMPRESSION_None ),
        MinimumValue( 0.0 ),
        OneOverPrecision( 0.0 )
    {
    }

    // ~~

    COMPONENT(
        string name,
        double precision = 1.0,
        uint16_t bit_count = 8,
        uint16_t compression = COMPRESSION_Discretization,
        double minimum_value = 0.0
        )
    {
        Name = name;
        Precision = precision;
        BitCount = bit_count;
        Compression = compression;
        MinimumValue = minimum_value;
        OneOverPrecision = 1.0 / precision;
    }

    // -- DESTRUCTORS

    virtual ~COMPONENT(
        )
    {
    }

    // -- INQUIRIES

    void Write(
        STREAM & stream
        )
    {
        stream.WriteText( Name );
        stream.WriteReal64( Precision );
        stream.WriteNatural16( BitCount );
        stream.WriteNatural16( Compression );
        stream.WriteReal64( MinimumValue );
        stream.WriteReal64( OneOverPrecision );
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
        )
    {
        stream.ReadText( Name );
        stream.ReadReal64( Precision );
        stream.ReadNatural16( BitCount );
        stream.ReadNatural16( Compression );
        stream.ReadReal64( MinimumValue );
        stream.ReadReal64( OneOverPrecision );
    }
};
