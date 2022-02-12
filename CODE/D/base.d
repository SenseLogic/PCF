module pcf.base;

// -- IMPORTS

import core.stdc.stdlib : exit;
import std.conv : to;
import std.stdio : writeln;
import std.string : endsWith, format, indexOf;

// -- FUNCTIONS

void PrintError(
    string message
    )
{
    writeln( "*** ERROR : ", message );
}

// ~~

void Abort(
    string message
    )
{
    PrintError( message );

    exit( -1 );
}

// ~~

void Abort(
    string message,
    Exception exception
    )
{
    PrintError( message );
    PrintError( exception.msg );

    exit( -1 );
}

// ~~

string RemoveTrailingZeros(
    string text
    )
{
    if ( text.indexOf( '.' ) >= 0 )
    {
        while ( text.endsWith( '0' ) )
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

bool IsInteger(
    string text
    )
{
    ulong
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
    ulong
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
    ulong natural
    )
{
    return natural.to!string();
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
    return RemoveTrailingZeros( format( "%f", real_ ) );
}

// ~~

string GetText(
    double real_
    )
{
    return RemoveTrailingZeros( format( "%f", real_ ) );
}
