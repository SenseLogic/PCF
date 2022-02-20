module pcf.buffer;

// -- IMPORTS

import std.conv : to;
import std.stdio : writeln;
import base.scalar;
import base.stream;
import pcf.component;
import pcf.compression;

// -- TYPES

class BUFFER
{
    // -- ATTIBUTES

    ulong
        BaseValue;
    ushort
        ComponentBitCount;
    ulong
        BitCount;
    ubyte[]
        ByteArray;

    // -- CONSTRUCTORS

    this(
        )
    {
    }

    // ~~

    this(
        COMPONENT component
        )
    {
        ComponentBitCount = component.BitCount;
    }

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteNatural64( BaseValue );
        stream.WriteNatural16( ComponentBitCount );
        stream.WriteNatural64( BitCount );
        stream.WriteScalarArray( ByteArray );
    }

    // ~~

    void Dump(
        string indentation = ""
        )
    {
        writeln( indentation, "BaseValue : ", BaseValue );
        writeln( indentation, "ComponentBitCount : ", ComponentBitCount );
        writeln( indentation, "BitCount : ", BitCount );
    }

    // -- OPERATIONS

    void AddComponentValue(
        COMPONENT component,
        double component_value,
        long component_offset
        )
    {
        long
            integer_value;
        ulong
            bit_index,
            byte_index,
            natural_value;
        ushort
            byte_bit_index;
        SCALAR
            scalar;

        if ( component.Compression == COMPRESSION.None )
        {
            if ( ComponentBitCount == 32 )
            {
                scalar.Real32 = component_value.to!float();

                foreach ( component_byte_index; 0 .. 4 )
                {
                    ByteArray ~= scalar.FourByteArray[ component_byte_index ];
                }
            }
            else
            {
                assert( ComponentBitCount == 64 );

                scalar.Real64 = component_value;

                foreach ( component_byte_index; 0 .. 8 )
                {
                    ByteArray ~= scalar.EightByteArray[ component_byte_index ];
                }
            }
        }
        else
        {
            assert( component.Compression == COMPRESSION.Discretization );

            integer_value = component.GetIntegerValue( component_value ) - ( component_offset << component.BitCount );
            assert( integer_value >= BaseValue.to!long() );

            natural_value = integer_value.to!ulong() - BaseValue;
            assert( ComponentBitCount == 64 || natural_value < ( 1UL << ComponentBitCount ) );

            foreach ( component_bit_index; 0 .. ComponentBitCount )
            {
                bit_index = BitCount + component_bit_index;
                byte_index = bit_index >> 3;
                byte_bit_index = bit_index & 7;

                if ( byte_index == ByteArray.length )
                {
                    ByteArray ~= 0;
                }

                if ( natural_value & ( 1UL << component_bit_index ) )
                {
                    ByteArray[ byte_index ] |= 1 << byte_bit_index;
                }
            }
        }

        BitCount += ComponentBitCount;
    }

    // ~~

    double GetComponentValue(
        ulong point_index,
        COMPONENT component,
        long component_offset
        )
    {
        double
            component_value;
        ulong
            bit_index,
            byte_index,
            natural_value;
        ushort
            byte_bit_index;
        SCALAR
            scalar;

        if ( component.Compression == COMPRESSION.None )
        {
            byte_index = ( point_index * ComponentBitCount ) >> 3;

            if ( ComponentBitCount == 32 )
            {
                foreach ( component_byte_index; 0 .. 4 )
                {
                    scalar.FourByteArray[ component_byte_index ] = ByteArray[ byte_index + component_byte_index ];
                }

                component_value = scalar.Real32;
            }
            else
            {
                assert( ComponentBitCount == 64 );

                foreach ( component_byte_index; 0 .. 8 )
                {
                    scalar.EightByteArray[ component_byte_index ] = ByteArray[ byte_index + component_byte_index ];
                }

                component_value = scalar.Real64;
            }
        }
        else
        {
            assert( component.Compression == COMPRESSION.Discretization );

            natural_value = 0;

            foreach ( component_bit_index; 0 .. ComponentBitCount )
            {
                bit_index = point_index * ComponentBitCount + component_bit_index;
                byte_index = bit_index >> 3;
                byte_bit_index = bit_index & 7;

                if ( ByteArray[ byte_index ] & ( 1 << byte_bit_index ) )
                {
                    natural_value |= 1UL << component_bit_index;
                }
            }

            natural_value += BaseValue;
            component_value = component.GetRealValue( natural_value.to!long() + ( component_offset << component.BitCount ) );
        }

        return component_value;
    }

    // ~~

    void Read(
        STREAM stream
        )
    {
        stream.ReadNatural64( BaseValue );
        stream.ReadNatural16( ComponentBitCount );
        stream.ReadNatural64( BitCount );
        stream.ReadScalarArray( ByteArray );
    }
}
