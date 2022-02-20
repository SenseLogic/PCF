module pcf.scan;

// -- IMPORTS

import std.stdio : writeln;
import base.stream;
import base.vector_3;
import base.vector_4;
import pcf.cell;
import pcf.cell_position_vector;
import pcf.component;
import pcf.compression;
import pcf.image;
import pcf.property;

// -- TYPES

class SCAN
{
    // -- ATTRIBUTES

    string
        Name;
    ulong
        ColumnCount,
        RowCount,
        PointCount;
    VECTOR_3
        PositionVector;
    VECTOR_4
        RotationVector;
    VECTOR_3
        XAxisVector,
        YAxisVector,
        ZAxisVector;
    COMPONENT[]
        ComponentArray;
    PROPERTY[]
        PropertyArray;
    IMAGE[]
        ImageArray;
    CELL[ CELL_POSITION_VECTOR ]
        CellMap;
    static void function( SCAN )
        PreWriteFunction,
        PostWriteFunction,
        PreReadFunction,
        PostReadFunction;
    static void delegate( SCAN )
        PreWriteDelegate,
        PostWriteDelegate,
        PreReadDelegate,
        PostReadDelegate;

    // -- CONSTRUCTORS

    this(
        )
    {
        PositionVector.SetVector( 0.0, 0.0, 0.0 );
        RotationVector.SetVector( 0.0, 0.0, 0.0, 1.0 );
        XAxisVector.SetVector( 1.0, 0.0, 0.0 );
        YAxisVector.SetVector( 0.0, 1.0, 0.0 );
        ZAxisVector.SetVector( 0.0, 0.0, 1.0 );
    }

    // -- INQUIRIES

    long GetComponentIndex(
        string component_name
        )
    {
        foreach ( component_index, component; ComponentArray )
        {
            if ( component.Name == component_name )
            {
                return component_index;
            }
        }

        return -1;
    }

    // ~~

    void TransformPositionVector(
        ref VECTOR_3 position_vector
        )
    {
        position_vector.ApplyTranslationRotationScalingTransform(
            PositionVector,
            XAxisVector,
            YAxisVector,
            ZAxisVector
            );
    }

    // ~~

    void Write(
        STREAM stream
        )
    {
        if ( PreWriteFunction !is null )
        {
            PreWriteFunction( this );
        }

        if ( PreWriteDelegate !is null )
        {
            PreWriteDelegate( this );
        }

        stream.WriteText( Name );
        stream.WriteNatural64( ColumnCount );
        stream.WriteNatural64( RowCount );
        stream.WriteNatural64( PointCount );
        stream.WriteValue( PositionVector );
        stream.WriteValue( RotationVector );
        stream.WriteValue( XAxisVector );
        stream.WriteValue( YAxisVector );
        stream.WriteValue( ZAxisVector );
        stream.WriteObjectArray( ComponentArray );
        stream.WriteObjectArray( PropertyArray );
        stream.WriteObjectArray( ImageArray );
        stream.WriteObjectByValueMap( CellMap );

        if ( PostWriteFunction !is null )
        {
            PostWriteFunction( this );
        }

        if ( PostWriteDelegate !is null )
        {
            PostWriteDelegate( this );
        }
    }

    // ~~

    void Dump(
        string indentation = ""
        )
    {
        writeln( indentation, "Name : ", Name );
        writeln( indentation, "ColumnCount : ", ColumnCount );
        writeln( indentation, "RowCount : ", RowCount );
        writeln( indentation, "PointCount : ", PointCount );
        writeln( indentation, "PositionVector : ", GetText( PositionVector ) );
        writeln( indentation, "RotationVector : ", GetText( RotationVector ) );
        writeln( indentation, "XAxisVector : ", GetText( XAxisVector ) );
        writeln( indentation, "YAxisVector : ", GetText( YAxisVector ) );
        writeln( indentation, "ZAxisVector : ", GetText( ZAxisVector ) );

        foreach ( component_index, component; ComponentArray )
        {
            writeln( indentation, "Component[", component_index, "] :" );

            component.Dump( indentation ~ "    " );
        }

        foreach ( property_index, property; PropertyArray )
        {
            writeln( indentation, "Property[", property_index, "] :" );

            property.Dump( indentation ~ "    " );
        }

        foreach ( image_index, image; ImageArray )
        {
            writeln( indentation, "Image[", image_index, "] :" );

            image.Dump( indentation ~ "    " );
        }

        foreach ( cell_position_vector, cell; CellMap )
        {
            writeln( indentation, "Cell[", GetText( cell_position_vector ), "] :" );

            cell.Dump( ComponentArray, indentation ~ "    " );
        }
    }

    // -- OPERATIONS

    void Clear(
        )
    {
        ComponentArray.destroy();
        PropertyArray.destroy();
        ImageArray.destroy();
        CellMap.destroy();
    }

    // ~~

    void SetRotationVector(
        )
    {
         RotationVector.SetFromAxisVectors( XAxisVector, YAxisVector, ZAxisVector );
    }

    // ~~

    void SetAxisVectors(
        )
    {
         RotationVector.GetAxisVectors( XAxisVector, YAxisVector, ZAxisVector );
    }

    // ~~

    CELL GetCell(
        double position_x,
        double position_y,
        double position_z
        )
    {
        CELL
            cell;
        CELL
            * found_cell;
        CELL_POSITION_VECTOR
            cell_position_vector;

        if ( ComponentArray[ 0 ].Compression == COMPRESSION.None )
        {
            assert(
                ComponentArray[ 1 ].Compression == COMPRESSION.None
                && ComponentArray[ 2 ].Compression == COMPRESSION.None
                );

            cell_position_vector.SetVector( 0, 0, 0 );
        }
        else
        {
            assert(
                ComponentArray[ 0 ].Compression == COMPRESSION.Discretization
                && ComponentArray[ 1 ].Compression == COMPRESSION.Discretization
                && ComponentArray[ 2 ].Compression == COMPRESSION.Discretization
                );

            cell_position_vector.SetVector(
                ComponentArray[ 0 ].GetIntegerValue( position_x ) >> ComponentArray[ 0 ].BitCount,
                ComponentArray[ 1 ].GetIntegerValue( position_y ) >> ComponentArray[ 1 ].BitCount,
                ComponentArray[ 2 ].GetIntegerValue( position_z ) >> ComponentArray[ 2 ].BitCount
                );
        }

        found_cell = cell_position_vector in CellMap;

        if ( found_cell !is null )
        {
            assert( found_cell.PositionVector == cell_position_vector );

            return *found_cell;
        }
        else
        {
            cell = new CELL( ComponentArray );
            cell.PositionVector = cell_position_vector;

            CellMap[ cell_position_vector ] = cell;

            return cell;
        }
    }

    // ~~

    void Read(
        STREAM stream
        )
    {
        if ( PreReadFunction !is null )
        {
            PreReadFunction( this );
        }

        if ( PreReadDelegate !is null )
        {
            PreReadDelegate( this );
        }

        stream.ReadText( Name );
        stream.ReadNatural64( ColumnCount );
        stream.ReadNatural64( RowCount );
        stream.ReadNatural64( PointCount );
        stream.ReadValue( PositionVector );
        stream.ReadValue( RotationVector );
        stream.ReadValue( XAxisVector );
        stream.ReadValue( YAxisVector );
        stream.ReadValue( ZAxisVector );
        stream.ReadObjectArray( ComponentArray );
        stream.ReadObjectArray( PropertyArray );
        stream.ReadObjectArray( ImageArray );
        stream.ReadObjectByValueMap( CellMap );

        if ( PostReadFunction !is null )
        {
            PostReadFunction( this );
        }

        if ( PostReadDelegate !is null )
        {
            PostReadDelegate( this );
        }
    }
}
