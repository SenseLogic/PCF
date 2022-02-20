#pragma once

// -- IMPORTS

#include <math.h>
#include <string.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "vector_.hpp"

using namespace std;

// -- FUNCTIONS

#ifndef assert
    #define assert( _condition_ ) \
        \
        if ( !( _condition_ ) ) \
        { \
            cerr << __FILE__ << "(" << __LINE__ << ") : " << #_condition_ << "\n"; \
            exit( -1 ); \
        }
#endif

// ~~

namespace base
{
    inline void PrintError(
        string message
        )
    {
        cerr << "*** ERROR : " << message << "\n";
    }

    // ~~

    inline void Abort(
        string message
        )
    {
        PrintError( message );

        exit( -1 );
    }

    // ~~

    inline void PrintProgress(
        uint64_t & progress,
        uint64_t index,
        uint64_t count
        )
    {
        uint64_t
            old_progress;

        if ( index + 1 == count )
        {
            cout << "      \r";
        }
        else
        {
            old_progress = progress;
            progress = ( uint64_t )floor( 1000.0 * ( double )( index + 1 ) / ( double )count );

            if ( progress < 0 )
            {
                progress = 0;
            }
            else if ( progress > 1000 )
            {
                progress = 1000;
            }

            if ( progress != old_progress )
            {
                cout << ( progress / 10 ) << "." << ( progress % 10 ) << "%\r";
            }
        }
    }

    // ~~

    inline bool HasPrefix(
        const char * text_character_array,
        const char * prefix_character_array
        )
    {
        uint64_t
            prefix_character_count,
            text_character_count;

        text_character_count = strlen( text_character_array );
        prefix_character_count = strlen( prefix_character_array );

        return
            text_character_count >= prefix_character_count
            && !strncmp( text_character_array, prefix_character_array, prefix_character_count );
    }

    // ~~

    inline bool HasPrefix(
        const string & text,
        const string & prefix
        )
    {
        return
            text.length() >= prefix.length()
            && !text.compare( 0, prefix.length(), prefix );
    }

    // ~~

    inline bool HasSuffix(
        const char * text_character_array,
        const char * suffix_character_array
        )
    {
        uint64_t
            suffix_character_count,
            text_character_count;

        text_character_count = strlen( text_character_array );
        suffix_character_count = strlen( suffix_character_array );

        return
            text_character_count >= suffix_character_count
            && !strcmp( text_character_array + text_character_count - suffix_character_count, suffix_character_array );
    }

    // ~~

    inline bool HasSuffix(
        const string & text,
        const string & suffix
        )
    {
        return
            text.length() >= suffix.length()
            && !text.compare( text.length() - suffix.length(), suffix.length(), suffix );
    }

    // ~~

    inline VECTOR_<string> Split(
        const string & text,
        const char separator_character
        )
    {
        uint64_t
            part_character_index,
            separator_character_index,
            text_character_count;
        VECTOR_<string>
            part_vector;

        text_character_count = text.length();
        part_character_index = 0;

        for ( separator_character_index = 0;
              separator_character_index < text_character_count;
              ++separator_character_index )
        {
            if ( text[ separator_character_index ] == separator_character )
            {
                part_vector.push_back(
                    text.substr( part_character_index, separator_character_index - part_character_index )
                    );

                part_character_index = separator_character_index + 1;
            }
        }

        part_vector.push_back(
            text.substr( part_character_index )
            );

        return part_vector;
    }

    // ~~

    inline string RemoveTrailingZeros(
        string text
        )
    {
        if ( text.find( '.' ) != string::npos )
        {
            while ( text.length() > 0
                    && text.back() == '0' )
            {
                text.resize( text.length() - 1 );
            }

            if ( text.length() > 0
                 && text.back() == '.' )
            {
                text.resize( text.length() - 1 );
            }
        }

        if ( text == "-0" )
        {
            return "0";
        }
        else
        {
            return text;
        }
    }

    // ~~

    inline bool IsBoolean(
        string text
        )
    {
        return
            text == "false"
            || text == "true";
    }

    // ~~

    inline bool IsInteger(
        string text
        )
    {
        uint64_t
            character_index;

        character_index = 0;

        if ( character_index < text.length()
             && text[ character_index ] == '-' )
        {
            ++character_index;
        }

        while ( character_index < text.length()
                && text[ character_index ] >= '0'
                && text[ character_index ] <= '9' )
        {
            ++character_index;
        }

        return
            character_index > 0
            && character_index == text.length();
    }

    // ~~

    inline bool IsReal(
        string text
        )
    {
        uint64_t
            character_index;

        character_index = 0;

        if ( character_index < text.length()
             && text[ character_index ] == '-' )
        {
            ++character_index;
        }

        while ( character_index < text.length()
                && text[ character_index ] >= '0'
                && text[ character_index ] <= '9' )
        {
            ++character_index;
        }

        if ( character_index < text.length()
             && text[ character_index ] == '.' )
        {
            ++character_index;
        }

        while ( character_index < text.length()
                && text[ character_index ] >= '0'
                && text[ character_index ] <= '9' )
        {
            ++character_index;
        }

        return
            character_index > 0
            && character_index == text.length();
    }

    // ~~

    inline bool GetBoolean(
        string text
        )
    {
        return text == "true";
    }

    // ~~

    inline uint64_t GetNatural64(
        string text
        )
    {
        if ( text == "" )
        {
            return 0;
        }
        else
        {
            return ( uint64_t )stoll( text.c_str() );
        }
    }

    // ~~

    inline int64_t GetInteger64(
        string text
        )
    {
        if ( text == "" )
        {
            return 0;
        }
        else
        {
            return ( int64_t )stoll( text.c_str() );
        }
    }

    // ~~

    inline double GetReal64(
        string text
        )
    {
        if ( text == "" )
        {
            return 0.0;
        }
        else
        {
            return stod( text );
        }
    }

    // ~~

    inline string GetText(
        bool boolean
        )
    {
        if ( boolean )
        {
            return "true";
        }
        else
        {
            return "false";
        }
    }

    // ~~

    inline string GetText(
        uint64_t natural
        )
    {
        return to_string( natural );
    }

    // ~~

    inline string GetText(
        int64_t integer
        )
    {
        return to_string( integer );
    }

    // ~~

    inline string GetText(
        float real
        )
    {
        return RemoveTrailingZeros( to_string( real ) );
    }

    // ~~

    inline string GetText(
        double real
        )
    {
        return RemoveTrailingZeros( to_string( real ) );
    }
}
