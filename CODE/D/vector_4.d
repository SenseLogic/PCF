module base.vector_4;

// -- IMPORTS

import std.math : sqrt;
import base.base : GetText;
import base.stream;
import base.vector_3;

// -- TYPES

struct VECTOR_4
{
    // -- ATTRIBUTES

    double
        X = 0.0,
        Y = 0.0,
        Z = 0.0,
        W = 0.0;

    // -- INQUIRIES

    void GetAxisVectors(
        ref VECTOR_3 x_axis_vector,
        ref VECTOR_3 y_axis_vector,
        ref VECTOR_3 z_axis_vector
        )
    {
        x_axis_vector.SetVector(
            1.0 - 2.0 * ( Y * Y + Z * Z ),
            2.0 * ( X * Y + W * Z ),
            2.0 * ( X * Z - W * Y )
            );

        y_axis_vector.SetVector(
            2.0 * ( X * Y - W * Z ),
            1.0 - 2.0 * ( X * X + Z * Z ),
            2.0 * ( Y * Z + W * X )
            );

        z_axis_vector.SetVector(
            2.0 * ( X * Z + W * Y ),
            2.0 * ( Y * Z - W * X ),
            1.0 - 2.0 * ( X * X + Y * Y )
            );
    }

    // ~~

    void Write(
        STREAM stream
        )
    {
        stream.WriteReal64( X );
        stream.WriteReal64( Y );
        stream.WriteReal64( Z );
        stream.WriteReal64( W );
    }

    // -- OPERATIONS

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
        ref VECTOR_4 vector
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

    void SetFromAxisVectors(
        ref VECTOR_3 x_axis_vector,
        ref VECTOR_3 y_axis_vector,
        ref VECTOR_3 z_axis_vector
        )
    {
        double
            square_root,
            trace;

        trace = x_axis_vector.X + y_axis_vector.Y + z_axis_vector.Z;

        if ( trace > 0 )
        {
            square_root = 0.5 / sqrt( trace+ 1.0 );

            X = ( z_axis_vector.Y - y_axis_vector.Z ) * square_root;
            Y = ( x_axis_vector.Z - z_axis_vector.X ) * square_root;
            Z = ( y_axis_vector.X - x_axis_vector.Y ) * square_root;
            W = 0.25 / square_root;
        }
        else if ( x_axis_vector.X > y_axis_vector.Y && x_axis_vector.X > z_axis_vector.Z )
        {
            square_root = 2.0 * sqrt( 1.0 + x_axis_vector.X - y_axis_vector.Y - z_axis_vector.Z );

            X = 0.25 * square_root;
            Y = ( x_axis_vector.Y + y_axis_vector.X ) / square_root;
            Z = ( x_axis_vector.Z + z_axis_vector.X ) / square_root;
            W = ( z_axis_vector.Y - y_axis_vector.Z ) / square_root;
        }
        else if ( y_axis_vector.Y > z_axis_vector.Z )
        {
            square_root = 2.0 * sqrt( 1.0 + y_axis_vector.Y - x_axis_vector.X - z_axis_vector.Z );

            X = ( x_axis_vector.Y + y_axis_vector.X ) / square_root;
            Y = 0.25 * square_root;
            Z = ( y_axis_vector.Z + z_axis_vector.Y ) / square_root;
            W = ( x_axis_vector.Z - z_axis_vector.X ) / square_root;
        }
        else
        {
            square_root = 2.0 * sqrt( 1.0 + z_axis_vector.Z - x_axis_vector.X - y_axis_vector.Y );

            X = ( x_axis_vector.Z + z_axis_vector.X ) / square_root;
            Y = ( y_axis_vector.Z + z_axis_vector.Y ) / square_root;
            Z = 0.25 * square_root;
            W = ( y_axis_vector.X - x_axis_vector.Y ) / square_root;
        }
    }

    // ~~

    void Read(
        STREAM stream
        )
    {
        stream.ReadReal64( X );
        stream.ReadReal64( Y );
        stream.ReadReal64( Z );
        stream.ReadReal64( W );
    }
}

// -- FUNCTIONS

string GetText(
    ref VECTOR_4 vector
    )
{
    return GetText( vector.X ) ~ " " ~ GetText( vector.Y ) ~ " " ~ GetText( vector.Z ) ~ " " ~ GetText( vector.W );
}
