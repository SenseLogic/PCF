module pcf.scalar;

// -- IMPORTS

import std.conv : to;
import std.string : endsWith, format, indexOf;

// -- TYPES

union SCALAR
{
    bool
        Boolean;
    char
        Character;
    ubyte
        Natural8;
    ushort
        Natural16;
    uint
        Natural32;
    ulong
        Natural64;
    byte
        Integer8;
    short
        Integer16;
    int
        Integer32;
    long
        Integer64;
    float
        Real32;
    double
        Real64;
    ubyte[ 1 ]
        OneByteArray;
    ubyte[ 2 ]
        TwoByteArray;
    ubyte[ 4 ]
        FourByteArray;
    ubyte[ 8 ]
        EightByteArray;
}

// -- FUNCTIONS

bool IsInteger(
    string text
    )
{
    long
        character_index;

    character_index = 0;

    if ( character_index < text.length
         && text[ character_index ] == '-' )
    {
        ++character_index;
    }

    while ( character_index < text.length
            && text[ character_index ] >= '0'
            && text[ character_index ] <= '9' )
    {
        ++character_index;
    }

    return
        character_index > 0
        && character_index == text.length;
}

// ~~

bool IsReal(
    string text
    )
{
    long
        character_index;

    character_index = 0;

    if ( character_index < text.length
         && text[ character_index ] == '-' )
    {
        ++character_index;
    }

    while ( character_index < text.length
            && text[ character_index ] >= '0'
            && text[ character_index ] <= '9' )
    {
        ++character_index;
    }

    if ( character_index < text.length
         && text[ character_index ] == '.' )
    {
        ++character_index;
    }

    while ( character_index < text.length
            && text[ character_index ] >= '0'
            && text[ character_index ] <= '9' )
    {
        ++character_index;
    }

    return
        character_index > 0
        && character_index == text.length;
}

// ~~

ulong GetNatural64(
    string text
    )
{
    if ( text == "" )
    {
        return 0;
    }
    else
    {
        return text.to!ulong();
    }
}

// ~~

long GetInteger64(
    string text
    )
{
    if ( text == "" )
    {
        return 0;
    }
    else
    {
        return text.to!long();
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
        return text.to!double();
    }
}

// ~~

string GetText(
    long integer
    )
{
    return integer.to!string();
}

// ~~

string GetText(
    float real_
    )
{
    string
        text;

    text = format( "%f", real_ );

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
    double real_
    )
{
    string
        text;

    text = format( "%f", real_ );

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

    if ( text == "-0" )
    {
        return "0";
    }
    else
    {
        return text;
    }
}
