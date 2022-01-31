module pcf.property;

// -- IMPORTS

import pcf.file;

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
        FILE file
        )
    {
        file.WriteText( Name );
        file.WriteText( Value );
        file.WriteText( Format );
    }

    // -- OPERATIONS

    void Read(
        FILE file
        )
    {
        file.ReadText( Name );
        file.ReadText( Value );
        file.ReadText( Format );
    }
}
