module pcf.vector_3;

// -- IMPORTS

import pcf.file;

// -- TYPES

struct VECTOR_3
{
    // -- ATTRIBUTES

    double
        X = 0.0,
        Y = 0.0,
        Z = 0.0;

    // -- INQUIRIES

    void Write(
        FILE file
        )
    {
        file.WriteReal( X );
        file.WriteReal( Y );
        file.WriteReal( Z );
    }

    // -- OPERATIONS

    void Read(
        FILE file
        )
    {
        file.ReadReal( X );
        file.ReadReal( Y );
        file.ReadReal( Z );
    }

    // ~~

    void SetVector(
        double x,
        double y,
        double z
        )
    {
        X = x;
        Y = y;
        Z = z;
    }

    // ~~

    void SetInverseVector(
        ref VECTOR_3 vector
        )
    {
        X = 1.0 / vector.X;
        Y = 1.0 / vector.Y;
        Z = 1.0 / vector.Z;
    }
}
