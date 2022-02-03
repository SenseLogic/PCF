#pragma once

// -- IMPORTS

#include "base.hpp"
#include "stream.hpp"

// -- TYPES

namespace pcf
{
    struct CELL_POSITION_VECTOR
    {
        // -- ATTRIBUTES

        int64_t
            X,
            Y,
            Z;

        // -- CONSTRUCTORS

        CELL_POSITION_VECTOR(
            ) :
            X( 0 ),
            Y( 0 ),
            Z( 0 )
        {
        }

        // ~~

        CELL_POSITION_VECTOR(
            const CELL_POSITION_VECTOR & vector
            ) :
            X( vector.X ),
            Y( vector.Y ),
            Z( vector.Z )
        {
        }

        // ~~

        CELL_POSITION_VECTOR(
            int64_t x,
            int64_t y,
            int64_t z
            ) :
            X( x ),
            Y( y ),
            Z( z )
        {
        }

        // -- OPERATORS

        CELL_POSITION_VECTOR & operator=(
            const CELL_POSITION_VECTOR & vector
            )
        {
            X = vector.X;
            Y = vector.Y;
            Z = vector.Z;

            return *this;
        }

        // ~~

        bool operator<(
            const CELL_POSITION_VECTOR & vector
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
            stream.WriteInteger64( X );
            stream.WriteInteger64( Y );
            stream.WriteInteger64( Z );
        }

        // -- OPERATIONS

        void Read(
            STREAM & stream
            )
        {
            stream.ReadInteger64( X );
            stream.ReadInteger64( Y );
            stream.ReadInteger64( Z );
        }

        // ~~

        void SetVector(
            int64_t x,
            int64_t y,
            int64_t z
            )
        {
            X = x;
            Y = y;
            Z = z;
        }
    };
}
