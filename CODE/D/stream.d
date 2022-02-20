module base.stream;

// -- IMPORTS

import std.stdio : File;
import std.string : split, stripRight;
import base.base;
import base.scalar;

// -- TYPES

class STREAM
{
    // -- ATTRIBUTES

    File
        File_;
    SCALAR
        Scalar;

    // -- OPERATIONS

    void OpenOutputBinaryFile(
        string output_file_path
        )
    {
        File_ = File( output_file_path, "wb" );
    }

    // ~~

    void CloseOutputBinaryFile(
        )
    {
        File_.close();
    }

    // ~~

    void OpenInputBinaryFile(
        string input_file_path
        )
    {
        File_ = File( input_file_path, "rb" );
    }

    // ~~

    void CloseInputBinaryFile(
        )
    {
        File_.close();
    }

    // ~~

    void WriteBoolean(
        bool boolean
        )
    {
        Scalar.Boolean = boolean;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteCharacter(
        char character
        )
    {
        Scalar.Character = character;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteNatural8(
        ubyte natural
        )
    {
        Scalar.Natural8 = natural;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteNatural16(
        ushort natural
        )
    {
        WriteNatural64( ulong( natural ) );
    }

    // ~~

    void WriteNatural32(
        uint natural
        )
    {
        WriteNatural64( ulong( natural ) );
    }

    // ~~

    void WriteNatural64(
        ulong natural
        )
    {
        ulong
            remaining_natural;

        remaining_natural = natural;

        while ( remaining_natural > 127 )
        {
            WriteNatural8( ubyte( 128 | ( remaining_natural & 127 ) ) );

            remaining_natural >>= 7;
        }

        WriteNatural8( ubyte( remaining_natural & 127 ) );
    }

    // ~~

    void WriteInteger8(
        byte integer
        )
    {
        Scalar.Integer8 = integer;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteInteger16(
        short integer
        )
    {
        WriteInteger64( long( integer ) );
    }

    // ~~

    void WriteInteger32(
        int integer
        )
    {
        WriteInteger64( long( integer ) );
    }

    // ~~

    void WriteInteger64(
        long integer
        )
    {
        ulong
            natural;

        natural = ( ulong( integer ) & 0x7FFFFFFFFFFFFFFF ) << 1;

        if ( integer < 0 )
        {
            natural = ~natural | 1;
        }

        WriteNatural64( natural );
    }

    // ~~

    void WriteReal32(
        float real_
        )
    {
        Scalar.Real32 = real_;
        File_.rawWrite( Scalar.FourByteArray );
    }

    // ~~

    void WriteReal64(
        double real_
        )
    {
        Scalar.Real64 = real_;
        File_.rawWrite( Scalar.EightByteArray );
    }

    // ~~

    void WriteValue( _VALUE_ )(
        ref _VALUE_ value
        )
    {
        value.Write( this );
    }

    // ~~

    void WriteObject( _OBJECT_ )(
        _OBJECT_ object
        )
    {
        object.Write( this );
    }

    // ~~

    void WriteText(
        string text
        )
    {
        WriteNatural64( text.length );

        if ( text.length > 0 )
        {
            File_.rawWrite( text );
        }
    }

    // ~~

    void WriteScalarArray( _SCALAR_ )(
        _SCALAR_[] scalar_array
        )
    {
        WriteNatural64( scalar_array.length );

        if ( scalar_array.length > 0 )
        {
            File_.rawWrite( scalar_array );
        }
    }

    // ~~

    void WriteValueArray( _VALUE_ )(
        _VALUE_[] value_array
        )
    {
        WriteNatural64( value_array.length );

        foreach ( value_index; 0 .. value_array.length )
        {
            value_array[ value_index ].Write( this );
        }
    }

    // ~~

    void WriteObjectArray( _OBJECT_ )(
        _OBJECT_[] object_array
        )
    {
        WriteNatural64( object_array.length );

        foreach ( object_index; 0 .. object_array.length )
        {
            object_array[ object_index ].Write( this );
        }
    }

    // ~~

    void WriteObjectByValueMap( _OBJECT_, _KEY_ )(
        _OBJECT_[ _KEY_ ] object_map
        )
    {
        WriteNatural64( object_map.length );

        foreach ( entry; object_map.byKeyValue() )
        {
            entry.key.Write( this );
            entry.value.Write( this );
        }
    }

    // ~~

    void ReadBoolean(
        ref bool boolean
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        boolean = Scalar.Boolean;
    }

    // ~~

    void ReadCharacter(
        ref char character
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        character = Scalar.Character;
    }

    // ~~

    void ReadNatural8(
        ref ubyte natural
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        natural = Scalar.Natural8;
    }

    // ~~

    void ReadNatural16(
        ref ushort natural
        )
    {
        ulong
            read_natural;

        ReadNatural64( read_natural );
        natural = cast( ushort )( read_natural );
    }

    // ~~

    void ReadNatural32(
        ref uint natural
        )
    {
        ulong
            read_natural;

        ReadNatural64( read_natural );
        natural = cast( uint )( read_natural );
    }

    // ~~

    void ReadNatural64(
        ref ulong natural
        )
    {
        uint
            bit_count;
        ulong
            byte_;

        natural = 0;
        bit_count = 0;

        do
        {
            File_.rawRead( Scalar.OneByteArray );
            byte_ = ulong( Scalar.Natural8 );
            natural |= ( byte_ & 127 ) << bit_count;
            bit_count += 7;
        }
        while ( ( byte_ & 128 ) != 0 );
    }

    // ~~

    void ReadInteger8(
        ref byte integer
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        integer = Scalar.Integer8;
    }

    // ~~

    void ReadInteger16(
        ref short integer
        )
    {
        long
            read_integer;

        ReadInteger64( read_integer );
        integer = cast( short )( read_integer );
    }

    // ~~

    void ReadInteger32(
        ref int integer
        )
    {
        long
            read_integer;

        ReadInteger64( read_integer );
        integer = cast( int )( read_integer );
    }

    // ~~

    void ReadInteger64(
        ref long integer
        )
    {
        ulong
            natural;

        ReadNatural64( natural );

        if ( ( natural & 1 ) == 0 )
        {
            integer = long( natural >> 1 );
        }
        else
        {
            integer = long( ~( natural >> 1 ) | 0x8000000000000000 );
        }
    }

    // ~~

    void ReadReal32(
        ref float real_
        )
    {
        File_.rawRead( Scalar.FourByteArray );
        real_ = Scalar.Real32;
    }

    // ~~

    void ReadReal64(
        ref double real_
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        real_ = Scalar.Real64;
    }

    // ~~

    void ReadValue( _VALUE_ )(
        ref _VALUE_ value
        )
    {
        value.Read( this );
    }

    // ~~

    void ReadObjectValue( _OBJECT_ )(
        _OBJECT_ object
        )
    {
        object.Read( this );
    }

    // ~~

    void ReadObject( _OBJECT_ )(
        ref _OBJECT_ object
        )
    {
        object = new _OBJECT_();
        object.Read( this );
    }

    // ~~

    void ReadText(
        ref string text
        )
    {
        ulong
            character_count;

        ReadNatural64( character_count );
        text.length = character_count;

        if ( character_count > 0 )
        {
            File_.rawRead( cast( ubyte[] )text );
        }
    }

    // ~~

    void ReadScalarArray( _SCALAR_ )(
        ref _SCALAR_[] scalar_array
        )
    {
        ulong
            scalar_count;

        ReadNatural64( scalar_count );
        scalar_array.length = scalar_count;

        if ( scalar_count > 0 )
        {
            File_.rawRead( scalar_array );
        }
    }

    // ~~

    void ReadValueArray( _VALUE_ )(
        ref _VALUE_[] value_array
        )
    {
        ulong
            value_count;

        ReadNatural64( value_count );
        value_array.length = value_count;

        foreach ( value_index; 0 .. value_count )
        {
            value_array[ value_index ].Read( this );
        }
    }

    // ~~

    void ReadObjectArray( _OBJECT_ )(
        ref _OBJECT_[] object_array
        )
    {
        ulong
            object_count;

        ReadNatural64( object_count );
        object_array.length = object_count;

        foreach ( object_index; 0 .. object_count )
        {
            object_array[ object_index ] = new _OBJECT_();
            object_array[ object_index ].Read( this );
        }
    }

    // ~~

    void ReadObjectByValueMap( _OBJECT_, _KEY_ )(
        ref _OBJECT_[ _KEY_ ] object_map
        )
    {
        ulong
            object_count;
        _KEY_
            key;
        _OBJECT_
            object;

        ReadNatural64( object_count );
        object_map = null;

        foreach ( object_index; 0 .. object_count )
        {
            key.Read( this );
            object = new _OBJECT_();
            object.Read( this );
            object_map[ key ] = object;
        }
    }

    // ~~

    void OpenOutputTextFile(
        string output_file_path
        )
    {
        File_ = File( output_file_path, "wb" );
    }

    // ~~

    void CloseOutputTextFile(
        )
    {
        File_.close();
    }

    // ~~

    void OpenInputTextFile(
        string input_file_path
        )
    {
        File_ = File( input_file_path, "rb" );
    }

    // ~~

    void CloseInputTextFile(
        )
    {
        File_.close();
    }

    // ~~

    void WriteLine(
        string line
        )
    {
        File_.writeln( line );
    }

    // ~~

    void WriteNaturalLine(
        ulong natural
        )
    {
        WriteLine( natural.GetText() );
    }

    // ~~

    void WriteIntegerLine(
        long integer
        )
    {
        WriteLine( integer.GetText() );
    }

    // ~~

    void WriteRealLine(
        double real_
        )
    {
        WriteLine( real_.GetText() );
    }

    // ~~

    void WriteRealLine(
        double first_real,
        double second_real,
        double third_real
        )
    {
        WriteLine(
            first_real.GetText()
            ~ " "
            ~ second_real.GetText()
            ~ " "
            ~ third_real.GetText()
            );
    }

    // ~~

    void WriteRealLine(
        double first_real,
        double second_real,
        double third_real,
        double fourth_real
        )
    {
        WriteLine(
            first_real.GetText()
            ~ " "
            ~ second_real.GetText()
            ~ " "
            ~ third_real.GetText()
            ~ " "
            ~ fourth_real.GetText()
            );
    }

    // ~~

    void WriteRealLine(
        double first_real,
        double second_real,
        double third_real,
        double fourth_real,
        double fifth_real,
        double sixth_real,
        double seventh_real
        )
    {
        WriteLine(
            first_real.GetText()
            ~ " "
            ~ second_real.GetText()
            ~ " "
            ~ third_real.GetText()
            ~ " "
            ~ fourth_real.GetText()
            ~ " "
            ~ fifth_real.GetText()
            ~ " "
            ~ sixth_real.GetText()
            ~ " "
            ~ seventh_real.GetText()
            );
    }

    // ~~

    bool ReadLine(
        ref string line
        )
    {
        line = File_.readln();

        if ( line !is null )
        {
            line = line.stripRight();
        }

        return
            line !is null
            && line != "";
    }

    // ~~

    bool ReadNaturalLine(
        ref ulong natural
        )
    {
        string
            line;

        if ( ReadLine( line ) )
        {
            natural = line.GetNatural64();

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    bool ReadIntegerLine(
        ref long integer
        )
    {
        string
            line;

        if ( ReadLine( line ) )
        {
            integer = line.GetInteger64();

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    bool ReadRealLine(
        ref double real_
        )
    {
        string
            line;

        if ( ReadLine( line ) )
        {
            real_ = line.GetReal64();

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    bool ReadRealLine(
        ref double first_real,
        ref double second_real,
        ref double third_real
        )
    {
        string
            line;
        string[]
            part_array;

        if ( ReadLine( line ) )
        {
            part_array = line.split( " " );

            first_real = part_array[ 0 ].GetReal64();
            second_real = part_array[ 1 ].GetReal64();
            third_real = part_array[ 2 ].GetReal64();

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    bool ReadRealLine(
        ref double first_real,
        ref double second_real,
        ref double third_real,
        ref double fourth_real
        )
    {
        string
            line;
        string[]
            part_array;

        if ( ReadLine( line ) )
        {
            part_array = line.split( " " );

            first_real = part_array[ 0 ].GetReal64();
            second_real = part_array[ 1 ].GetReal64();
            third_real = part_array[ 2 ].GetReal64();
            fourth_real = part_array[ 3 ].GetReal64();

            return true;
        }
        else
        {
            return false;
        }
    }

    // ~~

    bool ReadRealLine(
        ref double first_real,
        ref double second_real,
        ref double third_real,
        ref double fourth_real,
        ref double fifth_real,
        ref double sixth_real,
        ref double seventh_real
        )
    {
        string
            line;
        string[]
            part_array;

        if ( ReadLine( line ) )
        {
            part_array = line.split( " " );

            first_real = part_array[ 0 ].GetReal64();
            second_real = part_array[ 1 ].GetReal64();
            third_real = part_array[ 2 ].GetReal64();
            fourth_real = part_array[ 3 ].GetReal64();
            fifth_real = part_array[ 4 ].GetReal64();
            sixth_real = part_array[ 5 ].GetReal64();
            seventh_real = part_array[ 6 ].GetReal64();

            return true;
        }
        else
        {
            return false;
        }
    }
}
