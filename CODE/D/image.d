module pcf.image;

// -- IMPORTS

import pcf.stream;
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
