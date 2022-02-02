#pragma once

// -- IMPORTS

#include "base.hpp"
#include "component.hpp"
#include "stream.hpp"
#include "buffer.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "vector_.hpp"
#include "vector_3.hpp"

// -- TYPES

struct CELL :
    public OBJECT
{
    // -- TYPES

    typedef void ( *DELEGATE )( CELL & );

    // -- ATTRIBUTES

    uint64_t
        PointCount;
    VECTOR_3
        PositionVector;
    VECTOR_<LINK_<BUFFER>>
        BufferVector;
    static DELEGATE
        PreWriteDelegate,
        PostWriteDelegate,
        PreReadDelegate,
        PostReadDelegate;

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
        if ( PreWriteDelegate != nullptr )
        {
            ( *PreWriteDelegate )( *this );
        }

        stream.WriteNatural64( PointCount );
        stream.WriteValue( PositionVector );
        stream.WriteObjectVector( BufferVector );

        if ( PostWriteDelegate != nullptr )
        {
            ( *PostWriteDelegate )( *this );
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
        if ( PreReadDelegate != nullptr )
        {
            ( *PreReadDelegate )( *this );
        }

        stream.ReadNatural64( PointCount );
        stream.ReadValue( PositionVector );
        stream.ReadObjectVector( BufferVector );

        if ( PostReadDelegate != nullptr )
        {
            ( *PostReadDelegate )( *this );
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

    void AddComponentValue(
        const VECTOR_<LINK_<COMPONENT>> & component_vector,
        uint64_t component_index,
        double component_value
        )
    {
        if ( component_index == 0 )
        {
            component_value -= PositionVector.X;
        }
        else if ( component_index == 1 )
        {
            component_value -= PositionVector.Y;
        }
        else if ( component_index == 2 )
        {
            component_value -= PositionVector.Z;
        }

        BufferVector[ component_index ]->AddComponentValue( *component_vector[ component_index ], component_value );
    }

    // ~~

    double GetComponentValue(
        const VECTOR_<LINK_<COMPONENT>> & component_vector,
        uint64_t component_index
        )
    {
        double
            component_value;

        component_value = BufferVector[ component_index ]->GetComponentValue( *component_vector[ component_index ] );

        if ( component_index == 0 )
        {
            component_value += PositionVector.X;
        }
        else if ( component_index == 1 )
        {
            component_value += PositionVector.Y;
        }
        else if ( component_index == 2 )
        {
            component_value += PositionVector.Z;
        }

        return component_value;
    }
};
