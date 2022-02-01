module pcf.scan;

// -- IMPORTS

import pcf.cell;
import pcf.component;
import pcf.compression;
import pcf.image;
import pcf.property;
import pcf.stream;
import pcf.vector_3;
import std.math: floor;

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
        PositionVector,
        XAxisVector,
        YAxisVector,
        ZAxisVector;
    PROPERTY[]
        PropertyArray;
    IMAGE[]
        ImageArray;
    CELL[ VECTOR_3 ]
        CellMap;

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteText( Name );
        stream.WriteNatural64( ColumnCount );
        stream.WriteNatural64( RowCount );
        stream.WriteNatural64( PointCount );
        stream.WriteValue( PositionVector );
        stream.WriteValue( XAxisVector );
        stream.WriteValue( YAxisVector );
        stream.WriteValue( ZAxisVector );
        stream.WriteObjectArray( PropertyArray );
        stream.WriteObjectArray( ImageArray );
        stream.WriteObjectByValueMap!( CELL, VECTOR_3 )( CellMap );
    }

    // -- CONSTRUCTORS

    this(
        )
    {
        PositionVector.SetVector( 0.0, 0.0, 0.0 );
        XAxisVector.SetVector( 1.0, 0.0, 0.0 );
        YAxisVector.SetVector( 0.0, 1.0, 0.0 );
        ZAxisVector.SetVector( 0.0, 0.0, 1.0 );
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadText( Name );
        stream.ReadNatural64( ColumnCount );
        stream.ReadNatural64( RowCount );
        stream.ReadNatural64( PointCount );
        stream.ReadValue( PositionVector );
        stream.ReadValue( XAxisVector );
        stream.ReadValue( YAxisVector );
        stream.ReadValue( ZAxisVector );
        stream.ReadObjectArray( PropertyArray );
        stream.ReadObjectArray( ImageArray );
        stream.ReadObjectByValueMap!( CELL, VECTOR_3 )( CellMap );
    }

    // ~~

    CELL GetCell(
        COMPONENT[] component_array,
        double position_x,
        double position_y,
        double position_z
        )
    {
        VECTOR_3
            cell_position_vector;
        CELL
            cell;
        CELL
            * found_cell;

        if ( component_array[ 0 ].Compression == COMPRESSION.None )
        {
            assert(
                component_array[ 1 ].Compression == COMPRESSION.None
                && component_array[ 2 ].Compression == COMPRESSION.None
                );

            cell_position_vector.SetVector( 0.0, 0.0, 0.0 );
        }
        else if ( component_array[ 0 ].Compression == COMPRESSION.Discretization )
        {
            assert(
                component_array[ 1 ].Compression == COMPRESSION.Discretization
                && component_array[ 2 ].Compression == COMPRESSION.Discretization
                );

            cell_position_vector.SetVector(
                ( position_x * component_array[ 0 ].OneOverPrecision ).floor() * component_array[ 0 ].Precision,
                ( position_y * component_array[ 1 ].OneOverPrecision ).floor() * component_array[ 1 ].Precision,
                ( position_z * component_array[ 2 ].OneOverPrecision ).floor() * component_array[ 2 ].Precision
                );
        }

        found_cell = cell_position_vector in CellMap;

        if ( found_cell !is null )
        {
            return *found_cell;
        }
        else
        {
            cell = new CELL( component_array );
            cell.PositionVector = cell_position_vector;

            CellMap[ cell_position_vector ] = cell;

            return cell;
        }
    }
}
