#pragma once

// -- IMPORTS

#include "base.hpp"
#include "cell.hpp"
#include "cell_position_vector.hpp"
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

namespace pcf
{
    struct SCAN :
        public OBJECT
    {
        // -- TYPES

        typedef void ( *DELEGATE )( SCAN & );

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
        MAP_<CELL_POSITION_VECTOR, LINK_<CELL>>
            CellMap;
        static DELEGATE
            PreWriteDelegate,
            PostWriteDelegate,
            PreReadDelegate,
            PostReadDelegate;

        // -- CONSTRUCTORS

        SCAN(
            ) :
            OBJECT(),
            Name(),
            ColumnCount(),
            RowCount(),
            PointCount(),
            PositionVector( 0.0, 0.0, 0.0 ),
            XAxisVector( 1.0, 0.0, 0.0 ),
            YAxisVector( 0.0, 1.0, 0.0 ),
            ZAxisVector( 0.0, 0.0, 1.0 ),
            PropertyVector(),
            ImageVector(),
            CellMap()
        {
        }

        // ~~

        SCAN(
            const SCAN & scan
            ) :
            OBJECT( scan ),
            Name( scan.Name ),
            ColumnCount( scan.ColumnCount ),
            RowCount( scan.RowCount ),
            PointCount( scan.PointCount ),
            PositionVector( scan.PositionVector ),
            XAxisVector( scan.XAxisVector ),
            YAxisVector( scan.YAxisVector ),
            ZAxisVector( scan.ZAxisVector ),
            PropertyVector( scan.PropertyVector ),
            ImageVector( scan.ImageVector ),
            CellMap( scan.CellMap )
        {
        }

        // -- DESTRUCTORS

        virtual ~SCAN(
            )
        {
        }

        // -- OPERATORS

        SCAN & operator=(
            const SCAN & scan
            )
        {
            Name = scan.Name;
            ColumnCount = scan.ColumnCount;
            RowCount = scan.RowCount;
            PointCount = scan.PointCount;
            PositionVector = scan.PositionVector;
            XAxisVector = scan.XAxisVector;
            YAxisVector = scan.YAxisVector;
            ZAxisVector = scan.ZAxisVector;
            PropertyVector = scan.PropertyVector;
            ImageVector = scan.ImageVector;
            CellMap = scan.CellMap;

            return *this;
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            )
        {
            if ( PreWriteDelegate != nullptr )
            {
                ( *PreWriteDelegate )( *this );
            }

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

            if ( PostWriteDelegate != nullptr )
            {
                ( *PostWriteDelegate )( *this );
            }
        }

        // -- OPERATIONS

        void Clear(
            )
        {
            PropertyVector.clear();
            ImageVector.clear();
            CellMap.clear();
        }

        // ~~

        void Read(
            STREAM & stream
            )
        {
            if ( PreReadDelegate != nullptr )
            {
                ( *PreReadDelegate )( *this );
            }

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

            if ( PostReadDelegate != nullptr )
            {
                ( *PostReadDelegate )( *this );
            }
        }

        // ~~

        CELL * GetCell(
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            double position_x,
            double position_y,
            double position_z
            )
        {
            CELL_POSITION_VECTOR
                cell_position_vector;
            LINK_<CELL>
                cell;

            if ( component_vector[ 0 ]->Compression == COMPRESSION::None )
            {
                assert(
                    component_vector[ 1 ]->Compression == COMPRESSION::None
                    && component_vector[ 2 ]->Compression == COMPRESSION::None
                    );

                cell_position_vector.SetVector( 0, 0, 0 );
            }
            else
            {
                assert(
                    component_vector[ 0 ]->Compression == COMPRESSION::Discretization
                    && component_vector[ 1 ]->Compression == COMPRESSION::Discretization
                    && component_vector[ 2 ]->Compression == COMPRESSION::Discretization
                    );

                cell_position_vector.SetVector(
                    ( int64_t )floor( position_x * component_vector[ 0 ]->OneOverPrecision ) >> component_vector[ 0 ]->BitCount,
                    ( int64_t )floor( position_y * component_vector[ 1 ]->OneOverPrecision ) >> component_vector[ 1 ]->BitCount,
                    ( int64_t )floor( position_z * component_vector[ 2 ]->OneOverPrecision ) >> component_vector[ 2 ]->BitCount
                    );
            }

            auto found_cell = CellMap.find( cell_position_vector );

            if ( found_cell != CellMap.end() )
            {
                return found_cell->second.Address;
            }
            else
            {
                cell = new CELL( component_vector );
                cell->PositionVector = cell_position_vector;

                CellMap[ cell_position_vector ] = cell;

                return cell.Address;
            }
        }
    };
}
