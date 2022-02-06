// -- IMPORTS

#include "base.hpp"
#include "cloud.hpp"
#include "compression.hpp"
using namespace pcf;

// -- VARIABLES

LINK_<CLOUD>
    Cloud;

// -- FUNCTIONS

void PrintError(
    string message
    )
{
    cerr << "*** ERROR : " << message << "\n";
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

bool HasPrefix(
    const char * text_character_array,
    const char * prefix_character_array
    )
{
    int
        prefix_character_count,
        text_character_count;

    text_character_count = strlen( text_character_array );
    prefix_character_count = strlen( prefix_character_array );

    return
        text_character_count >= prefix_character_count
        && !strncmp( text_character_array, prefix_character_array, prefix_character_count );
}

// ~~

bool HasSuffix(
    const char * text_character_array,
    const char * suffix_character_array
    )
{
    int
        suffix_character_count,
        text_character_count;

    text_character_count = strlen( text_character_array );
    suffix_character_count = strlen( suffix_character_array );

    return
        text_character_count >= suffix_character_count
        && !strcmp( text_character_array + text_character_count - suffix_character_count, suffix_character_array );
}

// ~~

int main(
    int argument_count,
    char ** argument_array
    )
{
    int
        option_argument_count;
    string
        option;

    --argument_count;
    ++argument_array;

    while ( argument_count >= 1
            && HasPrefix( argument_array[ 0 ], "--" ) )
    {
        option = argument_array[ 0 ];

        --argument_count;
        ++argument_array;

        option_argument_count = 0;

        while ( option_argument_count < argument_count
                && !HasPrefix( argument_array[ option_argument_count ], "--" ) )
        {
            ++option_argument_count;
        }

        try
        {
            if ( option == "--read-pts"
                 && option_argument_count == 3
                 && HasSuffix( argument_array[ 0 ], ".pts" ) )
            {
                Cloud = new CLOUD();
                Cloud->ReadPtsFile(
                    argument_array[ 0 ],
                    ( atoi( argument_array[ 1 ] ) < 32 ) ? COMPRESSION::Discretization : COMPRESSION::None,
                    atoi( argument_array[ 1 ] ),
                    atof( argument_array[ 2 ] )
                    );
            }
            else if ( option == "--read-ptx"
                      && option_argument_count == 3
                      && HasSuffix( argument_array[ 0 ], ".ptx" ) )
            {
                Cloud = new CLOUD();
                Cloud->ReadPtxFile(
                    argument_array[ 0 ],
                    ( atoi( argument_array[ 1 ] ) < 32 ) ? COMPRESSION::Discretization : COMPRESSION::None,
                    atoi( argument_array[ 1 ] ),
                    atof( argument_array[ 2 ] )
                    );
            }
            else if ( option == "--read-pcf"
                      && option_argument_count == 1
                      && HasSuffix( argument_array[ 0 ], ".pcf" ) )
            {
                Cloud = new CLOUD();
                Cloud->ReadPcfFile( argument_array[ 0 ] );
            }
            else if ( option == "--dump"
                      && option_argument_count == 0
                      && !Cloud.IsNull() )
            {
                Cloud->Dump();
            }
            else if ( option == "--write-pts"
                      && option_argument_count == 1
                      && HasSuffix( argument_array[ 0 ], ".pts" )
                      && !Cloud.IsNull() )
            {
                Cloud->WritePtsFile( argument_array[ 0 ] );
            }
            else if ( option == "--write-ptx"
                      && option_argument_count == 1
                      && HasSuffix( argument_array[ 0 ], ".ptx" )
                      && !Cloud.IsNull() )
            {
                Cloud->WritePtxFile( argument_array[ 0 ] );
            }
            else if ( option == "--write-pcf"
                      && option_argument_count == 1
                      && HasSuffix( argument_array[ 0 ], ".pcf" )
                      && !Cloud.IsNull() )
            {
                Cloud->WritePcfFile( argument_array[ 0 ] );
            }
            else
            {
                Abort( "Invalid option : " + option );
            }
        }
        catch ( const exception & exception_ )
        {
            cerr << exception_.what() << "\n";
        }

        argument_count -= option_argument_count;
        argument_array += option_argument_count;
    }

    if ( argument_count > 0 )
    {
        cout
            << "Usage :\n"
            << "    pcf [ options ]\n"
            << "Options :\n"
            << "    --read-pts <file path> <position bit count> <position precision>\n"
            << "    --read-ptx <file path> <position bit count> <position precision>\n"
            << "    --read-pcf <file path>\n"
            << "    --write-pts <file path>\n"
            << "    --write-ptx <file path>\n"
            << "    --write-pcf <file path>\n"
            << "Examples :\n"
            << "    pcf --read-pts cloud.ptx 8 0.001 --write-pcf cloud.pcf\n"
            << "    pcf --read-pcf cloud.pcf --write-ptx cloud.ptx\n";

        Abort( "Invalid arguments" );
    }

    return 0;
}
