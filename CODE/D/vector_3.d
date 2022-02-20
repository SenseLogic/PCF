module base.vector_3;

// -- IMPORTS

import std.math : cos, sin, sqrt;
import base.base : Abort, GetText;
import base.stream;

// -- TYPES

struct VECTOR_3
{
    // -- ATTRIBUTES

    double
        X = 0.0,
        Y = 0.0,
        Z = 0.0;

    // -- INQUIRIES

    double GetComponent(
        char axis_component_letter
        )
    {
        if ( axis_component_letter == 'x' )
        {
            return -X;
        }
        else if ( axis_component_letter == 'X' )
        {
            return X;
        }
        else if ( axis_component_letter == 'y' )
        {
            return -Y;
        }
        else if ( axis_component_letter == 'Y' )
        {
            return Y;
        }
        else if ( axis_component_letter == 'z' )
        {
            return -Z;
        }
        else if ( axis_component_letter == 'Z' )
        {
            return Z;
        }
        else
        {
            Abort( "Invalid component letter" );

            return 0.0;
        }
    }

    // ~~

    void GetComponentVector(
        ref VECTOR_3 vector,
        char x_axis_component_letter,
        char y_axis_component_letter,
        char z_axis_component_letter
        )
    {
        vector.X = GetComponent( x_axis_component_letter );
        vector.Y = GetComponent( y_axis_component_letter );
        vector.Z = GetComponent( z_axis_component_letter );
    }

    // ~~

    double GetDistance(
        ref VECTOR_3 position_vector
        )
    {
        double
            x_distance,
            y_distance,
            z_distance;

        x_distance = position_vector.X - X;
        y_distance = position_vector.Y - Y;
        z_distance = position_vector.Z - Z;

        return sqrt( x_distance * x_distance + y_distance * y_distance + z_distance * z_distance );
    }

    // ~~

    void Write(
        STREAM stream
        )
    {
        stream.WriteReal64( X );
        stream.WriteReal64( Y );
        stream.WriteReal64( Z );
    }

    // -- OPERATIONS

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
        ref VECTOR_3 vector
        )
    {
        X = 1.0 / vector.X;
        Y = 1.0 / vector.Y;
        Z = 1.0 / vector.Z;
    }

    // ~~

    void SetFromCylindricalPosition(
        double distance,
        double azimuth_angle,
        double elevation,
        bool z_is_up
        )
    {
        double
            azimuth_angle_cosinus,
            azimuth_angle_sinus;

        azimuth_angle_cosinus = cos( azimuth_angle );
        azimuth_angle_sinus = sin( azimuth_angle );

        if ( z_is_up )
        {
            X = distance * azimuth_angle_cosinus;
            Y = distance * azimuth_angle_sinus;
            Z = distance * elevation;
        }
        else
        {
            X = distance * azimuth_angle_cosinus;
            Y = distance * elevation;
            Z = distance * azimuth_angle_sinus;
        }
    }

    // ~~

    void SetFromSphericalPosition(
        double distance,
        double azimuth_angle,
        double elevation_angle,
        bool z_is_up
        )
    {
        double
            azimuth_angle_cosinus,
            azimuth_angle_sinus,
            elevation_angle_cosinus,
            elevation_angle_sinus;

        azimuth_angle_cosinus = cos( azimuth_angle );
        azimuth_angle_sinus = sin( azimuth_angle );
        elevation_angle_cosinus = cos( elevation_angle );
        elevation_angle_sinus = sin( elevation_angle );

        if ( z_is_up )
        {
            X = distance * elevation_angle_cosinus * azimuth_angle_cosinus;
            Y = distance * elevation_angle_cosinus * azimuth_angle_sinus;
            Z = distance * elevation_angle_sinus;
        }
        else
        {
            X = distance * elevation_angle_cosinus * azimuth_angle_cosinus;
            Y = distance * elevation_angle_sinus;
            Z = distance * elevation_angle_cosinus * azimuth_angle_sinus;
        }
    }

    // ~~

    void AddVector(
        ref VECTOR_3 vector
        )
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    // ~~

    void AddScaledVector(
        ref VECTOR_3 vector,
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

    void ApplyTranslationRotationScalingTransform(
        ref VECTOR_3 translation_vector,
        ref VECTOR_3 rotation_cosinus_vector,
        ref VECTOR_3 rotation_sinus_vector,
        ref VECTOR_3 scaling_vector
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

    // ~~

    void ApplyTranslationRotationScalingTransform(
        ref VECTOR_3 translation_vector,
        ref VECTOR_3 rotated_x_axis_vector,
        ref VECTOR_3 rotated_y_axis_vector,
        ref VECTOR_3 rotated_z_axis_vector,
        ref VECTOR_3 scaling_vector
        )
    {
        Scale(
            scaling_vector.X,
            scaling_vector.Y,
            scaling_vector.Z
            );

        SetVector(
            X * rotated_x_axis_vector.X + Y * rotated_y_axis_vector.X + Z * rotated_z_axis_vector.X,
            X * rotated_x_axis_vector.Y + Y * rotated_y_axis_vector.Y + Z * rotated_z_axis_vector.Y,
            X * rotated_x_axis_vector.Z + Y * rotated_y_axis_vector.Z + Z * rotated_z_axis_vector.Z
            );

        Translate(
            translation_vector.X,
            translation_vector.Y,
            translation_vector.Z
            );
    }

    // ~~

    void ApplyTranslationRotationTransform(
        ref VECTOR_3 translation_vector,
        ref VECTOR_3 rotated_x_axis_vector,
        ref VECTOR_3 rotated_y_axis_vector,
        ref VECTOR_3 rotated_z_axis_vector
        )
    {
        SetVector(
            X * rotated_x_axis_vector.X + Y * rotated_y_axis_vector.X + Z * rotated_z_axis_vector.X,
            X * rotated_x_axis_vector.Y + Y * rotated_y_axis_vector.Y + Z * rotated_z_axis_vector.Y,
            X * rotated_x_axis_vector.Z + Y * rotated_y_axis_vector.Z + Z * rotated_z_axis_vector.Z
            );

        Translate(
            translation_vector.X,
            translation_vector.Y,
            translation_vector.Z
            );
    }

    // ~~

    void Read(
        STREAM stream
        )
    {
        stream.ReadReal64( X );
        stream.ReadReal64( Y );
        stream.ReadReal64( Z );
    }
}

// -- FUNCTIONS

string GetText(
    ref VECTOR_3 vector
    )
{
    return GetText( vector.X ) ~ " " ~ GetText( vector.Y ) ~ " " ~ GetText( vector.Z );
}
