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
        Precision = 0.0;
    uint16_t
        BitCount,
        Compression;
    double
        MinimumValue = 0.0,
        OneOverPrecision = 0.0;

    // -- CONSTRUCTORS

    COMPONENT(
        )
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
