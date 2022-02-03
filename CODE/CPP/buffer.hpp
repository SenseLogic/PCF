#pragma once

// -- IMPORTS

#include "base.hpp"
#include "component.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "object.hpp"
#include "scalar.hpp"
#include "vector_.hpp"

// -- TYPES

namespace pcf
{
    struct BUFFER :
        public OBJECT
    {
        // -- ATTIBUTES

        uint64_t
            MinimumNaturalValue;
        uint16_t
            ComponentBitCount;
        uint64_t
            BitCount;
        VECTOR_<uint8_t>
            ByteVector;
        uint64_t
            ReadBitIndex;

        // -- CONSTRUCTORS

        BUFFER(
            ) :
            OBJECT(),
            MinimumNaturalValue( 0 ),
            ComponentBitCount( 0 ),
            BitCount( 0 ),
            ByteVector(),
            ReadBitIndex( 0 )
        {
        }

        // ~~

        BUFFER(
            const BUFFER & buffer
            ) :
            OBJECT( buffer ),
            MinimumNaturalValue( buffer.MinimumNaturalValue ),
            ComponentBitCount( buffer.ComponentBitCount ),
            BitCount( buffer.BitCount ),
            ByteVector( buffer.ByteVector ),
            ReadBitIndex( buffer.ReadBitIndex )
        {
        }

        // ~~

        BUFFER(
            const COMPONENT & component
            ) :
            OBJECT(),
            MinimumNaturalValue( 0 ),
            ComponentBitCount( component.BitCount ),
            BitCount( 0 ),
            ByteVector(),
            ReadBitIndex( 0 )
        {
        }

        // -- DESTRUCTORS

        virtual ~BUFFER(
            )
        {
        }

        // -- OPERATORS

        BUFFER & operator=(
            const BUFFER & buffer
            )
        {
            MinimumNaturalValue = buffer.MinimumNaturalValue;
            ComponentBitCount = buffer.ComponentBitCount;
            BitCount = buffer.BitCount;
            ByteVector = buffer.ByteVector;
            ReadBitIndex = buffer.ReadBitIndex;

            return *this;
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            )
        {
            stream.WriteNatural64( MinimumNaturalValue );
            stream.WriteNatural16( ComponentBitCount );
            stream.WriteNatural64( BitCount );
            stream.WriteScalarVector( ByteVector );
        }

        // -- OPERATIONS

        void Read(
            STREAM & stream
            )
        {
            stream.ReadNatural64( MinimumNaturalValue );
            stream.ReadNatural16( ComponentBitCount );
            stream.ReadNatural64( BitCount );
            stream.ReadScalarVector( ByteVector );

            ReadBitIndex = 0;
        }

        // ~~

        void AddComponentValue(
            COMPONENT & component,
            double component_value
            )
        {
            double
                real_value;
            uint16_t
                byte_bit_index,
                component_bit_index;
            uint64_t
                bit_index,
                byte_index,
                component_byte_index,
                natural_value;
            SCALAR
                scalar;

            if ( component.Compression == COMPRESSION::None )
            {
                if ( ComponentBitCount == 32 )
                {
                    scalar.Real32 = ( float )component_value;

                    for ( component_byte_index = 0;
                          component_byte_index < 4;
                          ++component_byte_index )
                    {
                        ByteVector.push_back( scalar.FourByteVector[ component_byte_index ] );
                    }
                }
                else
                {
                    assert( ComponentBitCount == 64 );

                    scalar.Real64 = component_value;

                    for ( component_byte_index = 0;
                          component_byte_index < 8;
                          ++component_byte_index )
                    {
                        ByteVector.push_back( scalar.EightByteVector[ component_byte_index ] );
                    }
                }
            }
            else
            {
                assert( component.Compression == COMPRESSION::Discretization );

                real_value = ( component_value - component.MinimumValue ) * component.OneOverPrecision;
                assert( real_value >= -0.5 );

                natural_value = ( uint64_t )( real_value + 0.5 ) - MinimumNaturalValue;
                assert( ComponentBitCount == 64 || natural_value < ( 1ULL << ComponentBitCount ) );

                for ( component_bit_index = 0;
                      component_bit_index < ComponentBitCount;
                      ++component_bit_index )
                {
                    bit_index = BitCount + component_bit_index;
                    byte_index = bit_index >> 3;
                    byte_bit_index = bit_index & 7;

                    if ( byte_index == ByteVector.size() )
                    {
                        ByteVector.push_back( 0 );
                    }

                    if ( natural_value & ( 1ULL << component_bit_index ) )
                    {
                        ByteVector[ byte_index ] |= 1 << byte_bit_index;
                    }
                }
            }

            BitCount += ComponentBitCount;
        }

        // ~~

        double GetComponentValue(
            COMPONENT & component
            )
        {
            double
                component_value,
                real_value;
            uint16_t
                byte_bit_index,
                component_bit_index;
            uint64_t
                bit_index,
                byte_index,
                component_byte_index,
                natural_value;
            SCALAR
                scalar;

            if ( component.Compression == COMPRESSION::None )
            {
                byte_index = ReadBitIndex >> 3;

                if ( ComponentBitCount == 32 )
                {
                    for ( component_byte_index = 0;
                          component_byte_index < 4;
                          ++component_byte_index )
                    {
                        scalar.FourByteVector[ component_byte_index ] = ByteVector[ byte_index + component_byte_index ];
                    }

                    component_value = scalar.Real32;
                }
                else
                {
                    assert( ComponentBitCount == 64 );

                    for ( component_byte_index = 0;
                          component_byte_index < 8;
                          ++component_byte_index )
                    {
                        scalar.EightByteVector[ component_byte_index ] = ByteVector[ byte_index + component_byte_index ];
                    }

                    component_value = scalar.Real64;
                }
            }
            else
            {
                assert( component.Compression == COMPRESSION::Discretization );

                natural_value = 0;

                for ( component_bit_index = 0;
                      component_bit_index < ComponentBitCount;
                      ++component_bit_index )
                {
                    bit_index = ReadBitIndex + component_bit_index;
                    byte_index = bit_index >> 3;
                    byte_bit_index = bit_index & 7;

                    if ( ByteVector[ byte_index ] & ( 1 << byte_bit_index ) )
                    {
                        natural_value |= 1ULL << component_bit_index;
                    }
                }

                real_value = ( double )natural_value;
                component_value = ( real_value * component.Precision ) + component.MinimumValue;
            }

            ReadBitIndex += ComponentBitCount;

            return component_value;
        }
    };
}
