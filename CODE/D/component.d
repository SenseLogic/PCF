module pcf.component;

// -- IMPORTS

import std.conv : to;
import std.math : floor;
import std.stdio : writeln;
import base.stream;
import pcf.compression;

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
        BaseValue = 0.0,
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
        double base_value = 0.0,
        double minimum_value = 0.0,
        double maximum_value = 0.0
        )
    {
        Name = name;
        Compression = compression;
        BitCount = bit_count;
        Precision = precision;
        BaseValue = base_value;
        MinimumValue = minimum_value;
        MaximumValue = maximum_value;
        OneOverPrecision = ( precision > 0.0 ) ? 1.0 / precision : 0.0;
    }

    // -- INQUIRIES

    long GetIntegerValue(
        double component_value
        )
    {
        return ( ( component_value - BaseValue ) * OneOverPrecision ).floor().to!long();
    }

    // ~~

    double GetRealValue(
        long integer_value
        )
    {
        return BaseValue + integer_value.to!double() * Precision;
    }

    // ~~

    void Dump(
        string indentation = ""
        )
    {
        writeln( indentation, "Name : ", Name );
        writeln( indentation, "Compression : ", Compression );
        writeln( indentation, "BitCount : ", BitCount );
        writeln( indentation, "Precision : ", Precision );
        writeln( indentation, "BaseValue : ", BaseValue );
        writeln( indentation, "MinimumValue : ", MinimumValue );
        writeln( indentation, "MaximumValue : ", MaximumValue );
        writeln( indentation, "OneOverPrecision : ", OneOverPrecision );
    }

    // ~~

    void Write(
        STREAM stream
        )
    {
        stream.WriteText( Name );
        stream.WriteNatural16( Compression );
        stream.WriteNatural16( BitCount );
        stream.WriteReal64( Precision );
        stream.WriteReal64( BaseValue );
        stream.WriteReal64( MinimumValue );
        stream.WriteReal64( MaximumValue );
        stream.WriteReal64( OneOverPrecision );
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
        stream.ReadReal64( BaseValue );
        stream.ReadReal64( MinimumValue );
        stream.ReadReal64( MaximumValue );
        stream.ReadReal64( OneOverPrecision );
    }
}
