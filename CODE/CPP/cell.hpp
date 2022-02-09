#pragma once

// -- IMPORTS

#include "base.hpp"
#include "buffer.hpp"
#include "cell_position_vector.hpp"
#include "component.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "stream.hpp"
#include "vector_.hpp"

// -- TYPES

namespace pcf
{
    struct CELL :
        public OBJECT
    {
        // -- TYPES

        typedef void ( *FUNCTION )( CELL & );

        // -- ATTRIBUTES

        uint64_t
            PointCount;
        CELL_POSITION_VECTOR
            PositionVector;
        VECTOR_<LINK_<BUFFER>>
            BufferVector;
        static FUNCTION
            PreWriteFunction,
            PostWriteFunction,
            PreReadFunction,
            PostReadFunction;

        // -- CONSTRUCTORS

        CELL(
            ) :
            OBJECT(),
            PointCount( 0 ),
            PositionVector(),
            BufferVector()
        {
        }

        // ~~

        CELL(
            const CELL & cell
            ) :
            OBJECT( cell ),
            PointCount( cell.PointCount ),
            PositionVector( cell.PositionVector ),
            BufferVector( cell.BufferVector )
        {
        }

        // ~~

        CELL(
            const VECTOR_<LINK_<COMPONENT>> & component_vector
            ) :
            OBJECT(),
            PointCount( 0 ),
            PositionVector(),
            BufferVector()
        {
            for ( auto & component : component_vector )
            {
                BufferVector.push_back( new BUFFER( *component ) );
            }
        }

        // -- DESTRUCTORS

        virtual ~CELL(
            )
        {
        }

        // -- OPERATORS

        CELL & operator=(
            const CELL & cell
            )
        {
            PointCount = cell.PointCount;
            PositionVector = cell.PositionVector;
            BufferVector = cell.BufferVector;

            return *this;
        }

        // -- INQUIRIES

        int64_t GetComponentOffset(
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            uint64_t component_index
            ) const
        {
            if ( component_index <= 2
                 && component_vector[ component_index ]->Compression == COMPRESSION::Discretization )
            {
                if ( component_index == 0 )
                {
                    return PositionVector.X;
                }
                else if ( component_index == 1 )
                {
                    return PositionVector.Y;
                }
                else if ( component_index == 2 )
                {
                    return PositionVector.Z;
                }
            }

            return 0;
        }

        // ~~

        void Dump(
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            string indentation = ""
            )
        {
            double
                component_value;
            uint64_t
                buffer_index,
                component_index,
                point_index;

            cout << indentation << "PointCount : " << PointCount << "\n";
            cout << indentation << "PositionVector : " << GetText( PositionVector ) << "\n";

            for ( buffer_index = 0;
                  buffer_index < BufferVector.size();
                  ++buffer_index )
            {
                cout << indentation << "Buffer[" << buffer_index << "] :" << "\n";

                BufferVector[ buffer_index ]->Dump( indentation + "    " );
            }

            for ( point_index = 0;
                  point_index < PointCount;
                  ++point_index )
            {
                cout << indentation << "Point[" << point_index << "] :";

                for ( component_index = 0;
                      component_index < BufferVector.size();
                      ++component_index )
                {
                    component_value
                        = BufferVector[ component_index ]->GetComponentValue(
                              point_index,
                              *component_vector[ component_index ],
                              GetComponentOffset( component_vector, component_index )
                              );

                    cout << " " << component_value;
                }

                cout << "\n";
            }
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

            stream.WriteNatural64( PointCount );
            stream.WriteValue( PositionVector );
            stream.WriteObjectVector( BufferVector );

            if ( PostWriteFunction != nullptr )
            {
                ( *PostWriteFunction )( *this );
            }
        }

        // -- OPERATIONS

        void Clear(
            )
        {
            BufferVector.clear();
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

            stream.ReadNatural64( PointCount );
            stream.ReadValue( PositionVector );
            stream.ReadObjectVector( BufferVector );

            if ( PostReadFunction != nullptr )
            {
                ( *PostReadFunction )( *this );
            }
        }

        // ~~

        void AddComponentValue(
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            uint64_t component_index,
            double component_value
            )
        {
            BufferVector[ component_index ]->AddComponentValue(
                *component_vector[ component_index ],
                component_value,
                GetComponentOffset( component_vector, component_index )
                );
        }

        // ~~

        double GetComponentValue(
            uint64_t point_index,
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            uint64_t component_index
            )
        {
            return
                BufferVector[ component_index ]->GetComponentValue(
                    point_index,
                    *component_vector[ component_index ],
                    GetComponentOffset( component_vector, component_index )
                    );
        }
    };
}
