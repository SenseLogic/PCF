#pragma once

// -- IMPORTS

#include "base.hpp"
#include "cell.hpp"
#include "component.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "image.hpp"
#include "map_.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "property.hpp"
#include "vector_.hpp"
#include "vector_3.hpp"

// -- TYPES

struct SCAN :
    public OBJECT
{
    // -- ATTRIBUTES

    string
        Name;
    uint64_t
        ColumnCount,
        RowCount,
        PointCount;
    VECTOR_3
        PositionVector,
        XAxisVector,
        YAxisVector,
        ZAxisVector;
    VECTOR_<LINK_<PROPERTY>>
        PropertyVector;
    VECTOR_<LINK_<IMAGE>>
        ImageVector;
    MAP_<VECTOR_3, LINK_<CELL>>
        CellMap;

    // -- INQUIRIES

    void Write(
        STREAM & stream
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
        stream.WriteObjectVector( PropertyVector );
        stream.WriteObjectVector( ImageVector );
        stream.WriteObjectByValueMap( CellMap );
    }

    // -- CONSTRUCTORS

    SCAN(
        )
    {
        PositionVector.SetVector( 0.0, 0.0, 0.0 );
        XAxisVector.SetVector( 1.0, 0.0, 0.0 );
        YAxisVector.SetVector( 0.0, 1.0, 0.0 );
        ZAxisVector.SetVector( 0.0, 0.0, 1.0 );
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
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
        stream.ReadObjectVector( PropertyVector );
        stream.ReadObjectVector( ImageVector );
        stream.ReadObjectByValueMap( CellMap );
    }

    // ~~

    LINK_<CELL> GetCell(
        const VECTOR_<LINK_<COMPONENT>> & component_vector,
        double position_x,
        double position_y,
        double position_z
        )
    {
        VECTOR_3
            cell_position_vector;
        LINK_<CELL>
            cell;

        if ( component_vector[ 0 ]->Compression == COMPRESSION_None )
        {
            assert(
                component_vector[ 1 ]->Compression == COMPRESSION_None
                && component_vector[ 2 ]->Compression == COMPRESSION_None
                );

            cell_position_vector.SetVector( 0.0, 0.0, 0.0 );
        }
        else if ( component_vector[ 0 ]->Compression == COMPRESSION_Discretization )
        {
            assert(
                component_vector[ 1 ]->Compression == COMPRESSION_Discretization
                && component_vector[ 2 ]->Compression == COMPRESSION_Discretization
                );

            cell_position_vector.SetVector(
                floor( position_x * component_vector[ 0 ]->OneOverPrecision ) * component_vector[ 0 ]->Precision,
                floor( position_y * component_vector[ 1 ]->OneOverPrecision ) * component_vector[ 1 ]->Precision,
                floor( position_z * component_vector[ 2 ]->OneOverPrecision ) * component_vector[ 2 ]->Precision
                );
        }

        auto found_cell = CellMap.find( cell_position_vector );

        if ( found_cell != CellMap.end() )
        {
            return found_cell->second;
        }
        else
        {
            cell = new CELL( component_vector );
            cell->PositionVector = cell_position_vector;

            CellMap[ cell_position_vector ] = cell;

            return cell;
        }
    }
};
