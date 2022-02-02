#pragma once

// -- IMPORTS

#include <math.h>
#include <string.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

#include "vector_.hpp"

// -- FUNCTIONS

#define assert( _condition_ ) \
    \
    if ( !( _condition_ ) ) \
    { \
        printf( \
            "%s(%d) : %s\n", \
            __FILE__, \
            __LINE__, \
            #_condition_ \
            ); \
        exit( -1 ); \
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

inline bool IsInteger(
    string text
    )
{
    int64_t
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
    int64_t
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
