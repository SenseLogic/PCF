module pcf.cell_position_vector;

// -- IMPORTS

import pcf.stream;

// -- TYPES

struct CELL_POSITION_VECTOR
{
    // -- ATTRIBUTES

    long
        X,
        Y,
        Z;

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteInteger64( X );
        stream.WriteInteger64( Y );
        stream.WriteInteger64( Z );
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadInteger64( X );
        stream.ReadInteger64( Y );
        stream.ReadInteger64( Z );
    }

    // ~~

    void SetVector(
        long x,
        long y,
        long z
        )
    {
        X = x;
        Y = y;
        Z = z;
    }
}
