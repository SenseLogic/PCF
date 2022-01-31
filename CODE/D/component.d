module pcf.component;

// -- IMPORTS

import pcf.compression;
import pcf.file;

// -- TYPES

class COMPONENT
{
    // -- ATTRIBUTES

    string
        Name;
    double
        Precision = 0.0;
    ushort
        BitCount,
        Compression;
    double
        MinimumValue = 0.0,
        OneOverPrecision = 0.0;

    // -- CONSTRUCTORS

    this(
        )
    {
    }

    // ~~

    this(
        string name,
        double precision = 1.0,
        ushort bit_count = 8,
        ushort compression = COMPRESSION.Discretization,
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
        FILE file
        )
    {
        file.WriteText( Name );
        file.WriteReal64( Precision );
        file.WriteNatural16( BitCount );
        file.WriteNatural16( Compression );
        file.WriteReal64( MinimumValue );
        file.WriteReal64( OneOverPrecision );
    }

    // -- OPERATIONS

    void Read(
        FILE file
        )
    {
        file.ReadText( Name );
        file.ReadReal64( Precision );
        file.ReadNatural16( BitCount );
        file.ReadNatural16( Compression );
        file.ReadReal64( MinimumValue );
        file.ReadReal64( OneOverPrecision );
    }
}
