module pcf.image;

// -- IMPORTS

import pcf.file;

// -- TYPES

class IMAGE
{
    // -- ATTRIBUTES

    string
        Name,
        Role,
        Format,
        Data;
    ubyte[]
        ByteArray;

    // -- INQUIRIES

    void Write(
        FILE file
        )
    {
        file.WriteText( Name );
        file.WriteText( Role );
        file.WriteText( Format );
        file.WriteText( Data );
        file.WriteScalarArray( ByteArray );
    }

    // -- OPERATIONS

    void Read(
        FILE file
        )
    {
        file.ReadText( Name );
        file.ReadText( Role );
        file.ReadText( Format );
        file.ReadText( Data );
        file.ReadScalarArray( ByteArray );
    }
}
