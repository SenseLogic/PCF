module pcf.cell;

// -- IMPORTS

import std.container.array;
import std.container.util;
import std.stdio : write, writeln;
import pcf.buffer;
import pcf.cell_position_vector;
import pcf.component;
import pcf.compression;
import pcf.stream;

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

    void Dump(
        COMPONENT[] component_array,
        string indentation = ""
        )
    {
        double
            component_value;

        writeln( indentation, "PointCount : ", PointCount );
        writeln( indentation, "PositionVector : ", GetText( PositionVector ) );

        foreach ( buffer_index, buffer; BufferArray )
        {
            writeln( indentation, "Buffer[", buffer_index, "] :" );

            buffer.Dump( indentation ~ "    " );
        }

        foreach ( point_index; 0 .. PointCount )
        {
            write( indentation, "Point[", point_index, "] :" );

            foreach ( component_index, buffer; BufferArray )
            {
                component_value
                    = buffer.GetComponentValue(
                          point_index,
                          component_array[ component_index ],
                          GetComponentOffset( component_array, component_index )
                          );

                write( " ", component_value );
            }

            writeln();
        }
    }

    // ~~

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
        ulong point_index,
        COMPONENT[] component_array,
        ulong component_index
        )
    {
        return
            BufferArray[ component_index ].GetComponentValue(
                point_index,
                component_array[ component_index ],
                GetComponentOffset( component_array, component_index )
                );
    }
}
