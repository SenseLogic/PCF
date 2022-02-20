#pragma once

// -- IMPORTS

#include "base.hpp"
#include "component.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "object.hpp"
#include "scalar.hpp"
#include "vector_.hpp"

using base::OBJECT;
using base::SCALAR;
using base::STREAM;
using base::VECTOR_;

// -- TYPES

namespace pcf
{
    struct BUFFER :
        public OBJECT
    {
        // -- ATTIBUTES

        uint64_t
            BaseValue;
        uint16_t
            ComponentBitCount;
        uint64_t
            BitCount;
        VECTOR_<uint8_t>
            ByteVector;

        // -- CONSTRUCTORS

        BUFFER(
            ) :
            OBJECT(),
            BaseValue( 0 ),
            ComponentBitCount( 0 ),
            BitCount( 0 ),
            ByteVector()
        {
        }

        // ~~

        BUFFER(
            const BUFFER & buffer
            ) :
            OBJECT( buffer ),
            BaseValue( buffer.BaseValue ),
            ComponentBitCount( buffer.ComponentBitCount ),
            BitCount( buffer.BitCount ),
            ByteVector( buffer.ByteVector )
        {
        }

        // ~~

        BUFFER(
            const COMPONENT & component
            ) :
            OBJECT(),
            BaseValue( 0 ),
            ComponentBitCount( component.BitCount ),
            BitCount( 0 ),
            ByteVector()
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
            BaseValue = buffer.BaseValue;
            ComponentBitCount = buffer.ComponentBitCount;
            BitCount = buffer.BitCount;
            ByteVector = buffer.ByteVector;

            return *this;
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            )
        {
            stream.WriteNatural64( BaseValue );
            stream.WriteNatural16( ComponentBitCount );
            stream.WriteNatural64( BitCount );
            stream.WriteScalarVector( ByteVector );
        }

        // ~~

        void Dump(
            string indentation = ""
            ) const
        {
            cout << indentation << "BaseValue : " << BaseValue << "\n";
            cout << indentation << "ComponentBitCount : " << ComponentBitCount << "\n";
            cout << indentation << "BitCount : " << BitCount << "\n";
        }

        // -- OPERATIONS

        void AddComponentValue(
            COMPONENT & component,
            double component_value,
            int64_t component_offset
            )
        {
            int64_t
                integer_value;
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

                integer_value = component.GetIntegerValue( component_value ) - ( component_offset << component.BitCount );
                assert( integer_value >= ( int64_t )BaseValue );

                natural_value = ( uint64_t )integer_value - BaseValue;
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
            uint64_t point_index,
            COMPONENT & component,
            int64_t component_offset
            )
        {
            double
                component_value;
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
                byte_index = ( point_index * ComponentBitCount ) >> 3;

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
                    bit_index = ( point_index * ComponentBitCount ) + component_bit_index;
                    byte_index = bit_index >> 3;
                    byte_bit_index = bit_index & 7;

                    if ( ByteVector[ byte_index ] & ( 1 << byte_bit_index ) )
                    {
                        natural_value |= 1ULL << component_bit_index;
                    }
                }

                natural_value += BaseValue;
                component_value = component.GetRealValue( ( int64_t )natural_value + ( component_offset << component.BitCount ) );
            }

            return component_value;
        }

        // ~~

        void Read(
            STREAM & stream
            )
        {
            stream.ReadNatural64( BaseValue );
            stream.ReadNatural16( ComponentBitCount );
            stream.ReadNatural64( BitCount );
            stream.ReadScalarVector( ByteVector );
        }
    };
}
