module pcf.property;

// -- IMPORTS

import std.stdio : writeln;
import base.stream;

// -- TYPES

class PROPERTY
{
    // -- ATTRIBUTES

    string
        Name,
        Value,
        Format;

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteText( Name );
        stream.WriteText( Value );
        stream.WriteText( Format );
    }

    // ~~

    void Dump(
        string indentation = ""
        )
    {
        writeln( indentation, "Name : ", Name );
        writeln( indentation, "Value : ", Value );
        writeln( indentation, "Format : ", Format );
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadText( Name );
        stream.ReadText( Value );
        stream.ReadText( Format );
    }
}
