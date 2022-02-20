#pragma once

// -- IMPORTS

#include "base.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "map_.hpp"
#include "scalar.hpp"
#include "vector_.hpp"

// -- TYPES

namespace base
{
    struct STREAM
    {
        // -- ATTRIBUTES

        ofstream
            OutputFileStream;
        ifstream
            InputFileStream;
        SCALAR
            Scalar;

        // -- CONSTRUCTORS

        STREAM(
            ) :
            OutputFileStream(),
            InputFileStream()
        {
        }

        // -- DESTRUCTORS

        ~STREAM(
            )
        {
        }

        // -- OPERATIONS

        void OpenOutputBinaryFile(
            string output_file_path
            )
        {
            OutputFileStream.open( output_file_path, ofstream::out | ofstream::binary );
        }

        // ~~

        void CloseOutputBinaryFile(
            )
        {
            OutputFileStream.close();
        }

        // ~~

        void OpenInputBinaryFile(
            string input_file_path
            )
        {
            InputFileStream.open( input_file_path, ofstream::in | ofstream::binary );
        }

        // ~~

        void CloseInputBinaryFile(
            )
        {
            InputFileStream.close();
        }

        // ~~

        void WriteBoolean(
            bool boolean
            )
        {
            Scalar.Boolean = boolean;
            OutputFileStream.write( ( const char * )Scalar.OneByteVector, 1 );
        }

        // ~~

        void WriteCharacter(
            char character
            )
        {
            Scalar.Character = character;
            OutputFileStream.write( ( const char * )Scalar.OneByteVector, 1 );
        }

        // ~~

        void WriteNatural8(
            uint8_t natural
            )
        {
            Scalar.Natural8 = natural;
            OutputFileStream.write( ( const char * )Scalar.OneByteVector, 1 );
        }

        // ~~

        void WriteNatural16(
            uint16_t natural
            )
        {
            WriteNatural64( uint64_t( natural ) );
        }

        // ~~

        void WriteNatural32(
            uint32_t natural
            )
        {
            WriteNatural64( uint64_t( natural ) );
        }

        // ~~

        void WriteNatural64(
            uint64_t natural
            )
        {
            uint64_t
                remaining_natural;

            remaining_natural = natural;

            while ( remaining_natural > 127 )
            {
                WriteNatural8( uint8_t( 128 | ( remaining_natural & 127 ) ) );

                remaining_natural >>= 7;
            }

            WriteNatural8( uint8_t( remaining_natural & 127 ) );
        }

        // ~~

        void WriteInteger8(
            int8_t integer
            )
        {
            Scalar.Integer8 = integer;
            OutputFileStream.write( ( const char * )Scalar.OneByteVector, 1 );
        }

        // ~~

        void WriteInteger16(
            int16_t integer
            )
        {
            WriteInteger64( int64_t( integer ) );
        }

        // ~~

        void WriteInteger32(
            int32_t integer
            )
        {
            WriteInteger64( int64_t( integer ) );
        }

        // ~~

        void WriteInteger64(
            int64_t integer
            )
        {
            uint64_t
                natural;

            natural = ( uint64_t( integer ) & 0x7FFFFFFFFFFFFFFF ) << 1;

            if ( integer < 0 )
            {
                natural = ~natural | 1;
            }

            WriteNatural64( natural );
        }

        // ~~

        void WriteReal32(
            float real
            )
        {
            Scalar.Real32 = real;
            OutputFileStream.write( ( const char * )Scalar.FourByteVector, 4 );
        }

        // ~~

        void WriteReal64(
            double real
            )
        {
            Scalar.Real64 = real;
            OutputFileStream.write( ( const char * )Scalar.EightByteVector, 8 );
        }

        // ~~

        template <typename _VALUE_>
        void WriteValue(
            _VALUE_ & value
            )
        {
            value.Write( *this );
        }

        // ~~

        template <typename _OBJECT_>
        void WriteObject(
            _OBJECT_ & object
            )
        {
            object.Write( *this );
        }

        // ~~

        void WriteText(
            const string & text
            )
        {
            uint64_t
                character_count;

            character_count = text.length();
            WriteNatural64( character_count );

            if ( character_count > 0 )
            {
                OutputFileStream.write( text.data(), character_count );
            }
        }

        // ~~

        template <typename _SCALAR_>
        void WriteScalarVector(
            VECTOR_<_SCALAR_> & scalar_vector
            )
        {
            uint64_t
                scalar_count;

            scalar_count =  scalar_vector.size();
            WriteNatural64( scalar_count );

            if ( scalar_count > 0 )
            {
                OutputFileStream.write( ( const char * )scalar_vector.data(), scalar_count * sizeof( _SCALAR_ ) );
            }
        }

        // ~~

        template <typename _VALUE_>
        void WriteValueVector(
            VECTOR_<_VALUE_> & value_vector
            )
        {
            uint64_t
                value_count,
                value_index;

            value_count = value_vector.size();

            WriteNatural64( value_count );

            for ( value_index = 0;
                  value_index < value_count;
                  ++value_index )
            {
                value_vector[ value_index ].Write( *this );
            }
        }

        // ~~

        template <typename _OBJECT_>
        void WriteObjectVector(
            VECTOR_<LINK_<_OBJECT_>> & object_vector
            )
        {
            uint64_t
                object_count,
                object_index;

            object_count = object_vector.size();
            WriteNatural64( object_count );

            for ( object_index = 0;
                  object_index < object_count;
                  ++object_index )
            {
                object_vector[ object_index ]->Write( *this );
            }
        }

        // ~~

        template <typename _OBJECT_, typename _KEY_>
        void WriteObjectByValueMap(
            MAP_<_KEY_, LINK_<_OBJECT_>> & object_map
            )
        {
            WriteNatural64( object_map.size() );

            for ( auto & entry : object_map )
            {
                entry.first.Write( *this );
                entry.second->Write( *this );
            }
        }

        // ~~

        void ReadBoolean(
            bool & boolean
            )
        {
            InputFileStream.read( ( char * )Scalar.OneByteVector, 1 );
            boolean = Scalar.Boolean;
        }

        // ~~

        void ReadCharacter(
            char & character
            )
        {
            InputFileStream.read( ( char * )Scalar.OneByteVector, 1 );
            character = Scalar.Character;
        }

        // ~~

        void ReadNatural8(
            uint8_t & natural
            )
        {
            InputFileStream.read( ( char * )Scalar.OneByteVector, 1 );
            natural = Scalar.Natural8;
        }

        // ~~

        void ReadNatural16(
            uint16_t & natural
            )
        {
            uint64_t
                read_natural;

            ReadNatural64( read_natural );
            natural = ( uint16_t )( read_natural );
        }

        // ~~

        void ReadNatural32(
            uint32_t & natural
            )
        {
            uint64_t
                read_natural;

            ReadNatural64( read_natural );
            natural = ( uint32_t )( read_natural );
        }

        // ~~

        void ReadNatural64(
            uint64_t & natural
            )
        {
            uint32_t
                bit_count;
            uint64_t
                byte_;

            natural = 0;
            bit_count = 0;

            do
            {
                InputFileStream.read( ( char * )Scalar.OneByteVector, 1 );
                byte_ = uint64_t( Scalar.Natural8 );
                natural |= ( byte_ & 127 ) << bit_count;
                bit_count += 7;
            }
            while ( ( byte_ & 128 ) != 0 );
        }

        // ~~

        void ReadInteger8(
            int8_t & integer
            )
        {
            InputFileStream.read( ( char * )Scalar.OneByteVector, 1 );
            integer = Scalar.Integer8;
        }

        // ~~

        void ReadInteger16(
            int16_t & integer
            )
        {
            int64_t
                read_integer;

            ReadInteger64( read_integer );
            integer = ( int16_t )( read_integer );
        }

        // ~~

        void ReadInteger32(
            int32_t & integer
            )
        {
            int64_t
                read_integer;

            ReadInteger64( read_integer );
            integer = ( int32_t )( read_integer );
        }

        // ~~

        void ReadInteger64(
            int64_t & integer
            )
        {
            uint64_t
                natural;

            ReadNatural64( natural );

            if ( ( natural & 1 ) == 0 )
            {
                integer = int64_t( natural >> 1 );
            }
            else
            {
                integer = int64_t( ~( natural >> 1 ) | 0x8000000000000000 );
            }
        }

        // ~~

        void ReadReal32(
            float & real
            )
        {
            InputFileStream.read( ( char * )Scalar.FourByteVector, 4 );
            real = Scalar.Real32;
        }

        // ~~

        void ReadReal64(
            double & real
            )
        {
            InputFileStream.read( ( char * )Scalar.EightByteVector, 8 );
            real = Scalar.Real64;
        }

        // ~~

        template <typename _VALUE_>
        void ReadValue(
            _VALUE_ & value
            )
        {
            value.Read( *this );
        }

        // ~~

        template <typename _OBJECT_>
        void ReadObjectValue(
            _OBJECT_ & object
            )
        {
            object.Read( *this );
        }

        // ~~

        template <typename _OBJECT_>
        void ReadObject(
            _OBJECT_ & object
            )
        {
            object = new _OBJECT_();
            object.Read( *this );
        }

        // ~~

        void ReadText(
            string & text
            )
        {
            uint64_t
                character_count;

            ReadNatural64( character_count );
            text.resize( character_count );

            if ( character_count > 0 )
            {
                InputFileStream.read( ( char * )text.data(), character_count );
            }
        }

        // ~~

        template <typename _SCALAR_>
        void ReadScalarVector(
            VECTOR_<_SCALAR_> & scalar_vector
            )
        {
            uint64_t
                scalar_count;

            ReadNatural64( scalar_count );
            scalar_vector.resize( scalar_count );

            if ( scalar_count > 0 )
            {
                InputFileStream.read( ( char * )scalar_vector.data(), scalar_count * sizeof( _SCALAR_ ) );
            }
        }

        // ~~

        template <typename _VALUE_>
        void ReadValueVector(
            VECTOR_<_VALUE_> & value_vector
            )
        {
            uint64_t
                value_count,
                value_index;

            ReadNatural64( value_count );
            value_vector.resize( value_count );

            for ( value_index = 0;
                  value_index < value_count;
                  ++value_index )
            {
                value_vector[ value_index ].Read( *this );
            }
        }

        // ~~

        template <typename _OBJECT_>
        void ReadObjectVector(
            VECTOR_<LINK_<_OBJECT_>> & object_vector
            )
        {
            uint64_t
                object_count,
                object_index;

            ReadNatural64( object_count );
            object_vector.resize( object_count );

            for ( object_index = 0;
                  object_index < object_count;
                  ++object_index )
            {
                object_vector[ object_index ] = new _OBJECT_();
                object_vector[ object_index ]->Read( *this );
            }
        }

        // ~~

        template <typename _OBJECT_, typename _KEY_>
        void ReadObjectByValueMap(
            MAP_<_KEY_, LINK_<_OBJECT_>> & object_map
            )
        {
            uint64_t
                object_count,
                object_index;
            _KEY_
                key;
            LINK_<_OBJECT_>
                object;

            ReadNatural64( object_count );
            object_map.clear();

            for ( object_index = 0;
                  object_index < object_count;
                  ++object_index )
            {
                key.Read( *this );
                object = new _OBJECT_();
                object->Read( *this );
                object_map[ key ] = object;
            }
        }

        // ~~

        void OpenOutputTextFile(
            const string & output_file_path
            )
        {
            OutputFileStream.open( output_file_path, ofstream::out | ofstream::binary );
        }

        // ~~

        void CloseOutputTextFile(
            )
        {
            OutputFileStream.close();
        }

        // ~~

        void OpenInputTextFile(
            const string & input_file_path
            )
        {
            InputFileStream.open( input_file_path, ofstream::in | ofstream::binary );
        }

        // ~~

        void CloseInputTextFile(
            )
        {
            InputFileStream.close();
        }

        // ~~

        void WriteLine(
            const string & line
            )
        {
            OutputFileStream.write( line.c_str(), line.length() );
            OutputFileStream.write( "\n", 1 );
        }

        // ~~

        void WriteNaturalLine(
            uint64_t natural
            )
        {
            WriteLine( GetText( natural ) );
        }

        // ~~

        void WriteIntegerLine(
            int64_t integer
            )
        {
            WriteLine( GetText( integer ) );
        }

        // ~~

        void WriteRealLine(
            double real
            )
        {
            WriteLine( GetText( real ) );
        }

        // ~~

        void WriteRealLine(
            double first_real,
            double second_real,
            double third_real
            )
        {
            WriteLine(
                GetText( first_real )
                + " "
                + GetText( second_real )
                + " "
                + GetText( third_real )
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
                GetText( first_real )
                + " "
                + GetText( second_real )
                + " "
                + GetText( third_real )
                + " "
                + GetText( fourth_real )
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
                GetText( first_real )
                + " "
                + GetText( second_real )
                + " "
                + GetText( third_real )
                + " "
                + GetText( fourth_real )
                + " "
                + GetText( fifth_real )
                + " "
                + GetText( sixth_real )
                + " "
                + GetText( seventh_real )
                );
        }

        // ~~

        bool ReadLine(
            string & line
            )
        {
            uint64_t
                character_count;

            if ( getline( InputFileStream, line ) )
            {
                character_count = line.length();

                while ( character_count > 0
                        && line[ character_count - 1 ] >= 0
                        && line[ character_count - 1 ] <= 32 )
                {
                    --character_count;
                }

                line.resize( character_count );
            }
            else
            {
                line = "";
            }

            return line != "";
        }

        // ~~

        bool ReadNaturalLine(
            uint64_t & natural
            )
        {
            string
                line;

            if ( ReadLine( line ) )
            {
                natural = GetNatural64( line );

                return true;
            }
            else
            {
                return false;
            }
        }

        // ~~

        bool ReadIntegerLine(
            int64_t & integer
            )
        {
            string
                line;

            if ( ReadLine( line ) )
            {
                integer = GetInteger64( line );

                return true;
            }
            else
            {
                return false;
            }
        }

        // ~~

        bool ReadRealLine(
            double & real
            )
        {
            string
                line;

            if ( ReadLine( line ) )
            {
                real = GetReal64( line );

                return true;
            }
            else
            {
                return false;
            }
        }

        // ~~

        bool ReadRealLine(
            double & first_real,
            double & second_real,
            double & third_real
            )
        {
            string
                line;
            VECTOR_<string>
                part_vector;

            if ( ReadLine( line ) )
            {
                part_vector = Split( line, ' ' );

                first_real = GetReal64( part_vector[ 0 ] );
                second_real = GetReal64( part_vector[ 1 ] );
                third_real = GetReal64( part_vector[ 2 ] );

                return true;
            }
            else
            {
                return false;
            }
        }

        // ~~

        bool ReadRealLine(
            double & first_real,
            double & second_real,
            double & third_real,
            double & fourth_real
            )
        {
            string
                line;
            VECTOR_<string>
                part_vector;

            if ( ReadLine( line ) )
            {
                part_vector = Split( line, ' ' );

                first_real = GetReal64( part_vector[ 0 ] );
                second_real = GetReal64( part_vector[ 1 ] );
                third_real = GetReal64( part_vector[ 2 ] );
                fourth_real = GetReal64( part_vector[ 3 ] );

                return true;
            }
            else
            {
                return false;
            }
        }

        // ~~

        bool ReadRealLine(
            double & first_real,
            double & second_real,
            double & third_real,
            double & fourth_real,
            double & fifth_real,
            double & sixth_real,
            double & seventh_real
            )
        {
            string
                line;
            VECTOR_<string>
                part_vector;

            if ( ReadLine( line ) )
            {
                part_vector = Split( line, ' ' );

                first_real = GetReal64( part_vector[ 0 ] );
                second_real = GetReal64( part_vector[ 1 ] );
                third_real = GetReal64( part_vector[ 2 ] );
                fourth_real = GetReal64( part_vector[ 3 ] );
                fifth_real = GetReal64( part_vector[ 4 ] );
                sixth_real = GetReal64( part_vector[ 5 ] );
                seventh_real = GetReal64( part_vector[ 6 ] );

                return true;
            }
            else
            {
                return false;
            }
        }
    };
}
