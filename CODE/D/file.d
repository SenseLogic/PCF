module pcf.file;

// -- IMPORTS

import pcf.scalar;
import std.stdio : File;
import std.string: split, stripRight;

// -- TYPES

class FILE
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

    void OpenInputBinaryFile(
        string input_file_path
        )
    {
        File_ = File( input_file_path, "rb" );
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

    void WriteNatural(
        ubyte natural
        )
    {
        Scalar.Natural8 = natural;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteNatural(
        ushort natural
        )
    {
        Scalar.Natural16 = natural;
        File_.rawWrite( Scalar.TwoByteArray );
    }

    // ~~

    void WriteNatural(
        uint natural
        )
    {
        Scalar.Natural32 = natural;
        File_.rawWrite( Scalar.FourByteArray );
    }

    // ~~

    void WriteNatural(
        ulong natural
        )
    {
        Scalar.Natural64 = natural;
        File_.rawWrite( Scalar.EightByteArray );
    }

    // ~~

    void WriteInteger(
        byte integer
        )
    {
        Scalar.Integer8 = integer;
        File_.rawWrite( Scalar.OneByteArray );
    }

    // ~~

    void WriteInteger(
        short integer
        )
    {
        Scalar.Integer16 = integer;
        File_.rawWrite( Scalar.TwoByteArray );
    }

    // ~~

    void WriteInteger(
        int integer
        )
    {
        Scalar.Integer32 = integer;
        File_.rawWrite( Scalar.FourByteArray );
    }

    // ~~

    void WriteInteger(
        long integer
        )
    {
        Scalar.Integer64 = integer;
        File_.rawWrite( Scalar.EightByteArray );
    }

    // ~~

    void WriteReal(
        float real_
        )
    {
        Scalar.Real32 = real_;
        File_.rawWrite( Scalar.FourByteArray );
    }

    // ~~

    void WriteReal(
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
        WriteNatural( text.length );

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
        WriteNatural( scalar_array.length );

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
        WriteNatural( value_array.length );

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
        WriteNatural( object_array.length );

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
        WriteNatural( object_map.length );

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

    void ReadNatural(
        ref ubyte natural
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        natural = Scalar.Natural8;
    }

    // ~~

    void ReadNatural(
        ref ushort natural
        )
    {
        File_.rawRead( Scalar.TwoByteArray );
        natural = Scalar.Natural16;
    }

    // ~~

    void ReadNatural(
        ref uint natural
        )
    {
        File_.rawRead( Scalar.FourByteArray );
        natural = Scalar.Natural32;
    }

    // ~~

    void ReadNatural(
        ref ulong natural
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        natural = Scalar.Natural64;
    }

    // ~~

    void ReadInteger(
        ref byte integer
        )
    {
        File_.rawRead( Scalar.OneByteArray );
        integer = Scalar.Integer8;
    }

    // ~~

    void ReadInteger(
        ref short integer
        )
    {
        File_.rawRead( Scalar.TwoByteArray );
        integer = Scalar.Integer16;
    }

    // ~~

    void ReadInteger(
        ref int integer
        )
    {
        File_.rawRead( Scalar.FourByteArray );
        integer = Scalar.Integer32;
    }

    // ~~

    void ReadInteger(
        ref long integer
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        integer = Scalar.Integer64;
    }

    // ~~

    void ReadReal(
        ref float real_
        )
    {
        File_.rawRead( Scalar.FourByteArray );
        real_ = Scalar.Real32;
    }

    // ~~

    void ReadReal(
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
        File_.rawRead( Scalar.EightByteArray );
        text.length = Scalar.Natural64;

        if ( text.length > 0 )
        {
            File_.rawRead( cast( ubyte[] )text );
        }
    }

    // ~~

    void ReadScalarArray( _SCALAR_ )(
        ref _SCALAR_[] scalar_array
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        scalar_array.length = Scalar.Natural64;

        if ( scalar_array.length > 0 )
        {
            File_.rawRead( scalar_array );
        }
    }

    // ~~

    void ReadValueArray( _VALUE_ )(
        ref _VALUE_[] value_array
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        value_array.length = Scalar.Natural64;

        foreach ( value_index; 0 .. value_array.length )
        {
            value_array[ value_index ].Read( this );
        }
    }

    // ~~

    void ReadObjectArray( _OBJECT_ )(
        ref _OBJECT_[] object_array
        )
    {
        File_.rawRead( Scalar.EightByteArray );
        object_array.length = Scalar.Natural64;

        foreach ( object_index; 0 .. object_array.length )
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

        File_.rawRead( Scalar.EightByteArray );
        object_count = Scalar.Natural64;
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
        File_ = File( output_file_path, "wt" );
    }

    // ~~

    void OpenInputTextFile(
        string input_file_path
        )
    {
        File_ = File( input_file_path, "rt" );
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

    // ~~

    void Close(
        )
    {
        File_.close();
    }
}
