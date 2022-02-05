module pcf.component;

// -- IMPORTS

import std.conv: to;
import std.math: floor;
import pcf.compression;
import pcf.stream;

// -- TYPES

class COMPONENT
{
    // -- ATTRIBUTES

    string
        Name;
    ushort
        Compression,
        BitCount;
    double
        Precision = 0.0,
        MinimumValue = 0.0,
        MaximumValue = 0.0,
        OneOverPrecision = 0.0;

    // -- CONSTRUCTORS

    this(
        )
    {
    }

    // ~~

    this(
        string name,
        COMPRESSION compression = COMPRESSION.Discretization,
        ushort bit_count = 8,
        double precision = 1.0,
        double minimum_value = 0.0,
        double maximum_value = 0.0
        )
    {
        Name = name;
        Compression = compression;
        BitCount = bit_count;
        Precision = precision;
        MinimumValue = minimum_value;
        MaximumValue = maximum_value;
        OneOverPrecision = 1.0 / precision;
    }

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteText( Name );
        stream.WriteNatural16( Compression );
        stream.WriteNatural16( BitCount );
        stream.WriteReal64( Precision );
        stream.WriteReal64( MinimumValue );
        stream.WriteReal64( MaximumValue );
        stream.WriteReal64( OneOverPrecision );
    }

    // ~~

    long GetIntegerValue(
        double component_value
        )
    {
        return ( ( component_value - MinimumValue ) * OneOverPrecision ).floor().to!long();
    }

    // ~~

    double GetRealValue(
        long integer_value
        )
    {
        return MinimumValue + integer_value.to!double() * Precision;
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadText( Name );
        stream.ReadNatural16( Compression );
        stream.ReadNatural16( BitCount );
        stream.ReadReal64( Precision );
        stream.ReadReal64( MinimumValue );
        stream.ReadReal64( MaximumValue );
        stream.ReadReal64( OneOverPrecision );
    }
}
