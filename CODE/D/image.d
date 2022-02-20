module pcf.image;

// -- IMPORTS

import std.stdio : writeln;
import base.stream;
import pcf.property;

// -- TYPES

class IMAGE
{
    // -- ATTRIBUTES

    string
        Name,
        Role,
        Format;
    PROPERTY[]
        PropertyArray;
    ubyte[]
        ByteArray;

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteText( Name );
        stream.WriteText( Role );
        stream.WriteText( Format );
        stream.WriteObjectArray( PropertyArray );
        stream.WriteScalarArray( ByteArray );
    }

    // ~~

    void Dump(
        string indentation = ""
        )
    {
        writeln( indentation, "Name : ", Name );
        writeln( indentation, "Role : ", Role );
        writeln( indentation, "Format : ", Format );

        foreach ( property_index, property; PropertyArray )
        {
            writeln( indentation, "Property[", property_index, "] :" );

            property.Dump( indentation ~ "    " );
        }
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadText( Name );
        stream.ReadText( Role );
        stream.ReadText( Format );
        stream.ReadObjectArray( PropertyArray );
        stream.ReadScalarArray( ByteArray );
    }
}
