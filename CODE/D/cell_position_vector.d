module pcf.cell_position_vector;

// -- IMPORTS

import base.base : GetText;
import base.stream;

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

    // ~~

    void Read(
        STREAM stream
        )
    {
        stream.ReadInteger64( X );
        stream.ReadInteger64( Y );
        stream.ReadInteger64( Z );
    }
}

// -- FUNCTIONS

string GetText(
    ref CELL_POSITION_VECTOR cell_position_vector
    )
{
    return GetText( cell_position_vector.X ) ~ " " ~ GetText( cell_position_vector.Y ) ~ " " ~ GetText( cell_position_vector.Z );
}
