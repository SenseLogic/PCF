module pcf.scan;

// -- IMPORTS

import pcf.cell;
import pcf.component;
import pcf.compression;
import pcf.file;
import pcf.image;
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
    string
        Data;
    IMAGE[]
        ImageArray;
    CELL[ VECTOR_3 ]
        CellMap;

    // -- INQUIRIES

    void Write(
        FILE file
        )
    {
        file.WriteText( Name );
        file.WriteNatural( ColumnCount );
        file.WriteNatural( RowCount );
        file.WriteNatural( PointCount );
        file.WriteValue( PositionVector );
        file.WriteValue( XAxisVector );
        file.WriteValue( YAxisVector );
        file.WriteValue( ZAxisVector );
        file.WriteText( Data );
        file.WriteObjectArray( ImageArray );
        file.WriteObjectByValueMap!( CELL, VECTOR_3 )( CellMap );
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
        FILE file
        )
    {
        file.ReadText( Name );
        file.ReadNatural( ColumnCount );
        file.ReadNatural( RowCount );
        file.ReadNatural( PointCount );
        file.ReadValue( PositionVector );
        file.ReadValue( XAxisVector );
        file.ReadValue( YAxisVector );
        file.ReadValue( ZAxisVector );
        file.ReadText( Data );
        file.ReadObjectArray( ImageArray );
        file.ReadObjectByValueMap!( CELL, VECTOR_3 )( CellMap );
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

    // ~~

    void Compress(
        COMPONENT[] component_array
        )
    {
        foreach ( cell; CellMap.byValue )
        {
            cell.Compress( component_array );
        }
    }
}
