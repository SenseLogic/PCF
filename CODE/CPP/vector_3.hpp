#pragma once

// -- IMPORTS

#include "stream.hpp"

// -- TYPES

struct VECTOR_3
{
    // -- ATTRIBUTES

    double
        X,
        Y,
        Z;

    // -- CONSTRUCTORS

    VECTOR_3(
        ) :
        X( 0.0 ),
        Y( 0.0 ),
        Z( 0.0 )
    {
    }

    // ~~

    VECTOR_3(
        const VECTOR_3 & vector
        ) :
        X( vector.X ),
        Y( vector.Y ),
        Z( vector.Z )
    {
    }

    // ~~

    VECTOR_3(
        double x,
        double y,
        double z
        ) :
        X( x ),
        Y( y ),
        Z( z )
    {
    }

    // -- OPERATORS

    VECTOR_3 & operator=(
        const VECTOR_3 & vector
        )
    {
        X = vector.X;
        Y = vector.Y;
        Z = vector.Z;

        return *this;
    }

    // ~~

    bool operator<(
        const VECTOR_3 & vector
        ) const
    {
        return
            X < vector.X
            || ( X == vector.X
                 && Y < vector.Y )
            || ( X == vector.X
                 && Z == vector.Z
                 && Y < vector.Y );

    }

    // -- INQUIRIES

    void Write(
        STREAM & stream
        ) const
    {
        stream.WriteReal64( X );
        stream.WriteReal64( Y );
        stream.WriteReal64( Z );
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
        )
    {
        stream.ReadReal64( X );
        stream.ReadReal64( Y );
        stream.ReadReal64( Z );
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
        const VECTOR_3 & vector
        )
    {
        X = 1.0 / vector.X;
        Y = 1.0 / vector.Y;
        Z = 1.0 / vector.Z;
    }
};
