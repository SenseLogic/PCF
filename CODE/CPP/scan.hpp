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
#include "vector_4.hpp"

// -- TYPES

namespace pcf
{
    struct SCAN :
        public OBJECT
    {
        // -- TYPES

        typedef void ( *FUNCTION )( SCAN & );

        // -- ATTRIBUTES

        string
            Name;
        uint64_t
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
        VECTOR_<LINK_<COMPONENT>>
            ComponentVector;
        VECTOR_<LINK_<PROPERTY>>
            PropertyVector;
        VECTOR_<LINK_<IMAGE>>
            ImageVector;
        MAP_<CELL_POSITION_VECTOR, LINK_<CELL>>
            CellMap;
        static FUNCTION
            PreWriteFunction,
            PostWriteFunction,
            PreReadFunction,
            PostReadFunction;

        // -- CONSTRUCTORS

        SCAN(
            ) :
            OBJECT(),
            Name(),
            ColumnCount(),
            RowCount(),
            PointCount(),
            PositionVector( 0.0, 0.0, 0.0 ),
            RotationVector( 0.0, 0.0, 0.0, 1.0 ),
            XAxisVector( 1.0, 0.0, 0.0 ),
            YAxisVector( 0.0, 1.0, 0.0 ),
            ZAxisVector( 0.0, 0.0, 1.0 ),
            ComponentVector(),
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
            ComponentVector( scan.ComponentVector ),
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
            ComponentVector = scan.ComponentVector;
            PropertyVector = scan.PropertyVector;
            ImageVector = scan.ImageVector;
            CellMap = scan.CellMap;

            return *this;
        }

        // -- INQUIRIES

        int64_t GetComponentIndex(
            string component_name
            )
        {
            uint64_t
                component_index;

            for ( component_index = 0;
                  component_index < ComponentVector.size();
                  ++component_index )
            {
                if ( ComponentVector[ component_index ]->Name == component_name )
                {
                    return ( int64_t )component_index;
                }
            }

            return -1;
        }

        // ~~

        void TransformPositionVector(
            VECTOR_3 & position_vector
            )
        {
            position_vector.ApplyTranslationRotationTransform(
                PositionVector,
                XAxisVector,
                YAxisVector,
                ZAxisVector
                );
        }

        // ~~

        void Write(
            STREAM & stream
            )
        {
            if ( PreWriteFunction != nullptr )
            {
                ( *PreWriteFunction )( *this );
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
            stream.WriteObjectVector( ComponentVector );
            stream.WriteObjectVector( PropertyVector );
            stream.WriteObjectVector( ImageVector );
            stream.WriteObjectByValueMap( CellMap );

            if ( PostWriteFunction != nullptr )
            {
                ( *PostWriteFunction )( *this );
            }
        }

        // ~~

        void Dump(
            string indentation = ""
            ) const
        {
            uint64_t
                component_index,
                image_index,
                property_index;

            cout << indentation << "Name : " << Name << "\n";
            cout << indentation << "ColumnCount : " << ColumnCount << "\n";
            cout << indentation << "RowCount : " << RowCount << "\n";
            cout << indentation << "PointCount : " << PointCount << "\n";
            cout << indentation << "PositionVector : " << GetText( PositionVector ) << "\n";
            cout << indentation << "RotationVector : " << GetText( RotationVector ) << "\n";
            cout << indentation << "XAxisVector : " << GetText( XAxisVector ) << "\n";
            cout << indentation << "YAxisVector : " << GetText( YAxisVector ) << "\n";
            cout << indentation << "ZAxisVector : " << GetText( ZAxisVector ) << "\n";

            for ( component_index = 0;
                  component_index < ComponentVector.size();
                  ++component_index )
            {
                cout << indentation << "Component[" << component_index << "] :" << "\n";

                ComponentVector[ component_index ]->Dump( indentation + "    " );
            }

            for ( property_index = 0;
                  property_index < PropertyVector.size();
                  ++property_index )
            {
                cout << indentation << "Property[" << property_index << "] :" << "\n";

                PropertyVector[ property_index ]->Dump( indentation + "    " );
            }

            for ( image_index = 0;
                  image_index < ImageVector.size();
                  ++image_index )
            {
                cout << indentation << "Image[" << image_index << "] :" << "\n";

                ImageVector[ image_index ]->Dump( indentation + "    " );
            }

            for ( auto & cell_entry : CellMap )
            {
                cout << indentation << "Cell[" << GetText( cell_entry.first ) << "] :" << "\n";

                cell_entry.second->Dump( ComponentVector, indentation + "    " );
            }
        }

        // -- OPERATIONS

        void Clear(
            )
        {
            ComponentVector.clear();
            PropertyVector.clear();
            ImageVector.clear();
            CellMap.clear();
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

        CELL * GetCell(
            double position_x,
            double position_y,
            double position_z
            )
        {
            CELL_POSITION_VECTOR
                cell_position_vector;
            LINK_<CELL>
                cell;

            if ( ComponentVector[ 0 ]->Compression == COMPRESSION::None )
            {
                assert(
                    ComponentVector[ 1 ]->Compression == COMPRESSION::None
                    && ComponentVector[ 2 ]->Compression == COMPRESSION::None
                    );

                cell_position_vector.SetVector( 0, 0, 0 );
            }
            else
            {
                assert(
                    ComponentVector[ 0 ]->Compression == COMPRESSION::Discretization
                    && ComponentVector[ 1 ]->Compression == COMPRESSION::Discretization
                    && ComponentVector[ 2 ]->Compression == COMPRESSION::Discretization
                    );

                cell_position_vector.SetVector(
                    ComponentVector[ 0 ]->GetIntegerValue( position_x ) >> ComponentVector[ 0 ]->BitCount,
                    ComponentVector[ 1 ]->GetIntegerValue( position_y ) >> ComponentVector[ 1 ]->BitCount,
                    ComponentVector[ 2 ]->GetIntegerValue( position_z ) >> ComponentVector[ 2 ]->BitCount
                    );
            }

            auto found_cell = CellMap.find( cell_position_vector );

            if ( found_cell != CellMap.end() )
            {
                assert( found_cell->second.Address->PositionVector == cell_position_vector );

                return found_cell->second.Address;
            }
            else
            {
                cell = new CELL( ComponentVector );
                cell->PositionVector = cell_position_vector;

                CellMap[ cell_position_vector ] = cell;

                return cell.Address;
            }
        }

        // ~~

        void Read(
            STREAM & stream
            )
        {
            if ( PreReadFunction != nullptr )
            {
                ( *PreReadFunction )( *this );
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
            stream.ReadObjectVector( ComponentVector );
            stream.ReadObjectVector( PropertyVector );
            stream.ReadObjectVector( ImageVector );
            stream.ReadObjectByValueMap( CellMap );

            if ( PostReadFunction != nullptr )
            {
                ( *PostReadFunction )( *this );
            }
        }
    };
}
