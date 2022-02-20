module pcf.pcf;

// -- IMPORTS

import std.conv : to;
import std.stdio : writeln;
import std.string : endsWith, startsWith;
import base.base;
import pcf.cloud;
import pcf.compression;

// -- VARIABLES

CLOUD
    Cloud;

// -- FUNCTIONS

void main(
    string[] argument_array
    )
{
    long
        argument_count;
    string
        option;

    argument_array = argument_array[ 1 .. $ ];

    while ( argument_array.length >= 1
            && argument_array[ 0 ].startsWith( "--" ) )
    {
        option = argument_array[ 0 ];

        argument_array = argument_array[ 1 .. $ ];
        argument_count = 0;

        while ( argument_count < argument_array.length
                && !argument_array[ argument_count ].startsWith( "--" ) )
        {
            ++argument_count;
        }

        if ( option == "--read-pts"
             && argument_count == 3
             && argument_array[ 0 ].endsWith( ".pts" ) )
        {
            writeln( "Reading PTS file : ", argument_array[ 0 ] );

            Cloud = new CLOUD();
            Cloud.ReadPtsFile(
                argument_array[ 0 ],
                ( argument_array[ 1 ].to!ushort() < 32 ) ? COMPRESSION.Discretization : COMPRESSION.None,
                argument_array[ 1 ].to!ushort(),
                argument_array[ 2 ].to!double()
                );
        }
        else if ( option == "--read-ptx"
                  && argument_count == 3
                  && argument_array[ 0 ].endsWith( ".ptx" ) )
        {
            writeln( "Reading PTX file : ", argument_array[ 0 ] );

            Cloud = new CLOUD();
            Cloud.ReadPtxFile(
                argument_array[ 0 ],
                ( argument_array[ 1 ].to!ushort() < 32 ) ? COMPRESSION.Discretization : COMPRESSION.None,
                argument_array[ 1 ].to!ushort(),
                argument_array[ 2 ].to!double()
                );
        }
        else if ( option == "--read-pcf"
                  && argument_count == 1
                  && argument_array[ 0 ].endsWith( ".pcf" ) )
        {
            writeln( "Reading PCF file : ", argument_array[ 0 ] );

            Cloud = new CLOUD();
            Cloud.ReadPcfFile( argument_array[ 0 ] );
        }
        else if ( option == "--dump"
                  && argument_count == 0
                  && Cloud !is null )
        {
            Cloud.Dump();
        }
        else if ( option == "--write-pts"
                  && argument_count == 1
                  && argument_array[ 0 ].endsWith( ".pts" )
                  && Cloud !is null )
        {
            writeln( "Writing PTS file : ", argument_array[ 0 ] );

            Cloud.WritePtsFile( argument_array[ 0 ] );
        }
        else if ( option == "--write-ptx"
                  && argument_count == 1
                  && argument_array[ 0 ].endsWith( ".ptx" )
                  && Cloud !is null )
        {
            writeln( "Writing PTX file : ", argument_array[ 0 ] );

            Cloud.WritePtxFile( argument_array[ 0 ] );
        }
        else if ( option == "--write-pcf"
                  && argument_count == 1
                  && argument_array[ 0 ].endsWith( ".pcf" )
                  && Cloud !is null )
        {
            writeln( "Writing PCF file : ", argument_array[ 0 ] );

            Cloud.WritePcfFile( argument_array[ 0 ] );
        }
        else
        {
            Abort( "Invalid option : " ~ option );
        }

        argument_array = argument_array[ argument_count .. $ ];
    }

    if ( argument_array.length > 0 )
    {
        writeln( "Usage :" );
        writeln( "    pcf [options]" );
        writeln( "Options :" );
        writeln( "    --read-pts <file path> <position bit count> <position precision>" );
        writeln( "    --read-ptx <file path> <position bit count> <position precision>" );
        writeln( "    --read-pcf <file path>" );
        writeln( "    --dump" );
        writeln( "    --write-pts <file path>" );
        writeln( "    --write-ptx <file path>" );
        writeln( "    --write-pcf <file path>" );
        writeln( "Examples :" );
        writeln( "    pcf --read-pts cloud.ptx 8 0.001 --write-pcf cloud.pcf" );
        writeln( "    pcf --read-pcf cloud.pcf --write-ptx cloud.ptx" );

        Abort( "Invalid arguments : " ~ argument_array.to!string( ) );
    }
}
