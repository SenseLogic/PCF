module pcf.cell;

// -- IMPORTS

import pcf.buffer;
import pcf.cell_position_vector;
import pcf.component;
import pcf.compression;
import pcf.stream;
import std.container.array;
import std.container.util;

// -- TYPES

class CELL
{
    // -- ATTRIBUTES

    ulong
        PointCount;
    CELL_POSITION_VECTOR
        PositionVector;
    BUFFER[]
        BufferArray;
    static void function( CELL )
        PreWriteFunction,
        PostWriteFunction,
        PreReadFunction,
        PostReadFunction;
    static void delegate( CELL )
        PreWriteDelegate,
        PostWriteDelegate,
        PreReadDelegate,
        PostReadDelegate;

    // -- CONSTRUCTORS

    this(
        )
    {
    }

    // ~~

    this(
        COMPONENT[] component_array
        )
    {
        foreach ( component; component_array )
        {
            BufferArray ~= new BUFFER( component );
        }
    }

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        if ( PreWriteFunction !is null )
        {
            PreWriteFunction( this );
        }

        if ( PreWriteDelegate !is null )
        {
            PreWriteDelegate( this );
        }

        stream.WriteNatural64( PointCount );
        stream.WriteValue( PositionVector );
        stream.WriteObjectArray( BufferArray );

        if ( PostWriteFunction !is null )
        {
            PostWriteFunction( this );
        }

        if ( PostWriteDelegate !is null )
        {
            PostWriteDelegate( this );
        }
    }

    // -- OPERATIONS

    void Clear(
        )
    {
        BufferArray.destroy();
    }

    // ~~

    void Read(
        STREAM stream
        )
    {
        if ( PreReadFunction !is null )
        {
            PreReadFunction( this );
        }

        if ( PreReadDelegate !is null )
        {
            PreReadDelegate( this );
        }

        stream.ReadNatural64( PointCount );
        stream.ReadValue( PositionVector );
        stream.ReadObjectArray( BufferArray );

        if ( PostReadFunction !is null )
        {
            PostReadFunction( this );
        }

        if ( PostReadDelegate !is null )
        {
            PostReadDelegate( this );
        }
    }

    // ~~

    void SeekComponent(
        ulong component_index
        )
    {
        assert( component_index == 0 );

        foreach ( buffer; BufferArray )
        {
            buffer.ReadBitIndex = 0;
        }
    }

    // ~~

    long GetComponentOffset(
        COMPONENT[] component_array,
        ulong component_index
        )
    {
        if ( component_index <= 2
             && component_array[ component_index ].Compression == COMPRESSION.Discretization )
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
        COMPONENT[] component_array,
        ulong component_index,
        double component_value
        )
    {
        BufferArray[ component_index ].AddComponentValue(
            component_array[ component_index ],
            component_value,
            GetComponentOffset( component_array, component_index )
            );
    }

    // ~~

    double GetComponentValue(
        COMPONENT[] component_array,
        ulong component_index
        )
    {
        return
            BufferArray[ component_index ].GetComponentValue(
                component_array[ component_index ],
                GetComponentOffset( component_array, component_index )
                );
    }
}
