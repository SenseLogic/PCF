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

        void SeekComponent(
            uint64_t component_index
            )
        {
            assert( component_index == 0 );

            for ( auto & buffer : BufferVector )
            {
                buffer->ReadBitIndex = 0;
            }
        }

        // ~~

        int64_t GetComponentOffset(
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            uint64_t component_index
            )
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
            const VECTOR_<LINK_<COMPONENT>> & component_vector,
            uint64_t component_index
            )
        {
            return
                BufferVector[ component_index ]->GetComponentValue(
                    *component_vector[ component_index ],
                    GetComponentOffset( component_vector, component_index )
                    );
        }
    };
}
