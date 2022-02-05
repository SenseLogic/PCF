#pragma once

// -- IMPORTS

#include "stream.hpp"
#include "vector_3.hpp"

// -- TYPES

namespace pcf
{
    struct VECTOR_4
    {
        // -- ATTRIBUTES

        double
            X,
            Y,
            Z,
            W;

        // -- CONSTRUCTORS

        VECTOR_4(
            ) :
            X( 0.0 ),
            Y( 0.0 ),
            Z( 0.0 ),
            W( 0.0 )
        {
        }

        // ~~

        VECTOR_4(
            const VECTOR_4 & vector
            ) :
            X( vector.X ),
            Y( vector.Y ),
            Z( vector.Z ),
            W( vector.W )
        {
        }

        // ~~

        VECTOR_4(
            double x,
            double y,
            double z,
            double w
            ) :
            X( x ),
            Y( y ),
            Z( z ),
            W( w )
        {
        }

        // -- OPERATORS

        VECTOR_4 & operator=(
            const VECTOR_4 & vector
            )
        {
            X = vector.X;
            Y = vector.Y;
            Z = vector.Z;
            W = vector.W;

            return *this;
        }

        // ~~

        bool operator==(
            const VECTOR_4 & vector
            ) const
        {
            return
                X == vector.X
                && Y == vector.Y
                && Z == vector.Z
                && W == vector.W;
        }

        // ~~

        bool operator!=(
            const VECTOR_4 & vector
            ) const
        {
            return
                X != vector.X
                || Y != vector.Y
                || Z != vector.Z
                || W != vector.W;
        }

        // ~~

        bool operator<(
            const VECTOR_4 & vector
            ) const
        {
            return
                X < vector.X
                || ( X == vector.X
                     && Y < vector.Y )
                || ( X == vector.X
                     && Y == vector.Y
                     && Z < vector.Z )
                || ( X == vector.X
                     && Y == vector.Y
                     && Z == vector.Z
                     && W < vector.W );
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            ) const
        {
            stream.WriteReal64( X );
            stream.WriteReal64( Y );
            stream.WriteReal64( Z );
            stream.WriteReal64( W );
        }

        // -- OPERATIONS

        void Read(
            STREAM & stream
            )
        {
            stream.ReadReal64( X );
            stream.ReadReal64( Y );
            stream.ReadReal64( Z );
            stream.ReadReal64( W );
        }

        // ~~

        void SetNull(
            )
        {
            X = 0.0;
            Y = 0.0;
            Z = 0.0;
            W = 0.0;
        }

        // ~~

        void SetUnit(
            )
        {
            X = 1.0;
            Y = 1.0;
            Z = 1.0;
            W = 1.0;
        }

        // ~~

        void SetVector(
            double x,
            double y,
            double z,
            double w
            )
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        // ~~

        void AddVector(
            const VECTOR_4 & vector
            )
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
            W += vector.W;
        }

        // ~~

        void MultiplyScalar(
            double scalar
            )
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            W *= scalar;
        }

        // ~~

        void Translate(
            double x_translation,
            double y_translation,
            double z_translation,
            double w_translation
            )
        {
            X += x_translation;
            Y += y_translation;
            Z += z_translation;
            W += w_translation;
        }

        // ~~

        void Scale(
            double x_scaling,
            double y_scaling,
            double z_scaling,
            double w_scaling
            )
        {
            X *= x_scaling;
            Y *= y_scaling;
            Z *= z_scaling;
            W *= w_scaling;
        }

        // ~~

        void GetAxisVectors(
            VECTOR_3 & x_axis_vector,
            VECTOR_3 & y_axis_vector,
            VECTOR_3 & z_axis_vector
            )
        {
            x_axis_vector.SetVector(
                1.0 - 2.0 * Y * Y - 2.0 * Z * Z,
                2.0 * X * Y + 2.0 * Z * W,
                2.0 * X * Z - 2.0 * Y * W
                );

            y_axis_vector.SetVector(
                2.0 * X * Y - 2.0 * Z * W,
                1.0 - 2.0 * X * X - 2.0 * Z * Z,
                2.0 * Y * Z + 2.0 * X * W
                );

            z_axis_vector.SetVector(
                2.0 * X * Z + 2.0 * Y * W,
                2.0 * Y * Z - 2.0 * X * W,
                1.0 - 2.0 * X * X - 2.0 * Y * Y
                );
        }
    };
}
