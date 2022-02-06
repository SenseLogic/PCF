#pragma once

// -- IMPORTS

#include "stream.hpp"

// -- TYPES

namespace pcf
{
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

        bool operator==(
            const VECTOR_3 & vector
            ) const
        {
            return
                X == vector.X
                && Y == vector.Y
                && Z == vector.Z;
        }

        // ~~

        bool operator!=(
            const VECTOR_3 & vector
            ) const
        {
            return
                X != vector.X
                || Y != vector.Y
                || Z != vector.Z;
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
                     && Y == vector.Y
                     && Z < vector.Z );
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

        void SetNull(
            )
        {
            X = 0.0;
            Y = 0.0;
            Z = 0.0;
        }

        // ~~

        void SetUnit(
            )
        {
            X = 1.0;
            Y = 1.0;
            Z = 1.0;
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

        // ~~

        void AddVector(
            const VECTOR_3 & vector
            )
        {
            X += vector.X;
            Y += vector.Y;
            Z += vector.Z;
        }

        // ~~

        void AddScaledVector(
            const VECTOR_3 & vector,
            double factor
            )
        {
            X += vector.X * factor;
            Y += vector.Y * factor;
            Z += vector.Z * factor;
        }

        // ~~

        void MultiplyScalar(
            double scalar
            )
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
        }


        // ~~

        void Translate(
            double x_translation,
            double y_translation,
            double z_translation
            )
        {
            X += x_translation;
            Y += y_translation;
            Z += z_translation;
        }

        // ~~

        void Scale(
            double x_scaling,
            double y_scaling,
            double z_scaling
            )
        {
            X *= x_scaling;
            Y *= y_scaling;
            Z *= z_scaling;
        }

        // ~~

        void RotateAroundX(
            double x_angle_cosinus,
            double x_angle_sinus
            )
        {
            double
                y;

            y = Y;
            Y = Y * x_angle_cosinus - Z * x_angle_sinus;
            Z = y * x_angle_sinus + Z * x_angle_cosinus;
        }

        // ~~

        void RotateAroundY(
            double y_angle_cosinus,
            double y_angle_sinus
            )
        {
            double
                x;

            x = X;
            X = X * y_angle_cosinus + Z * y_angle_sinus;
            Z = Z * y_angle_cosinus - x * y_angle_sinus;
        }

        // ~~

        void RotateAroundZ(
            double z_angle_cosinus,
            double z_angle_sinus
            )
        {
            double
                x;

            x = X;
            X = X * z_angle_cosinus - Y * z_angle_sinus;
            Y = x * z_angle_sinus + Y * z_angle_cosinus;
        }

        // ~~

        void Transform(
            const VECTOR_3 & translation_vector,
            const VECTOR_3 & rotation_cosinus_vector,
            const VECTOR_3 & rotation_sinus_vector,
            const VECTOR_3 & scaling_vector
            )
        {
            Scale(
                scaling_vector.X,
                scaling_vector.Y,
                scaling_vector.Z
                );

            RotateAroundZ(
                rotation_cosinus_vector.Z,
                rotation_sinus_vector.Z
                );

            RotateAroundX(
                rotation_cosinus_vector.X,
                rotation_sinus_vector.X
                );

            RotateAroundY(
                rotation_cosinus_vector.Y,
                rotation_sinus_vector.Y
                );

            Translate(
                translation_vector.X,
                translation_vector.Y,
                translation_vector.Z
                );
        }
    };

    // -- FUNCTIONS

    inline string GetText(
        const VECTOR_3 & vector
        )
    {
        return GetText( vector.X ) + " " + GetText( vector.Y ) + " " + GetText( vector.Z );
    }
}
