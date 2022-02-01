#pragma once

// -- IMPORTS

#include <assert.h>
#include <math.h>
#include <cstdint>
#include <cstdlib>
#include <string>

using namespace std;

#include "vector_.hpp"

// -- FUNCTIONS

bool IsInteger(
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

bool IsReal(
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

uint64_t GetNatural64(
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

int64_t GetInteger64(
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

double GetReal64(
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

string GetText(
    uint64_t natural
    )
{
    return to_string( natural );
}

// ~~

string GetText(
    int64_t integer
    )
{
    return to_string( integer );
}

// ~~

string GetText(
    float real
    )
{
    string
        text;

    text = to_string( real );
    /*
    if ( text.indexOf( '.' ) >= 0 )
    {
        while ( text.endsWith( '0') )
        {
            text = text[ 0 .. $ - 1 ];
        }

        if ( text.endsWith( '.' ) )
        {
            text = text[ 0 .. $ - 1 ];
        }
    }
    */
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

string GetText(
    double real
    )
{
    string
        text;

    text = to_string( real );
    /*
    if ( text.indexOf( '.' ) >= 0 )
    {
        while ( text.endsWith( '0') )
        {
            text = text[ 0 .. $ - 1 ];
        }

        if ( text.endsWith( '.' ) )
        {
            text = text[ 0 .. $ - 1 ];
        }
    }
    */
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

inline VECTOR_<string> Split(
    const string & text,
    const string & delimiter
    )
{
    VECTOR_<string>
        part_vector;
    /*
    TODO
    */
    return part_vector;
}
