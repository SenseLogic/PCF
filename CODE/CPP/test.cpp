// -- IMPORTS

#include "cloud.hpp"
#include "compression.hpp"

// -- FUNCTIONS

int main(
    int argument_count,
    char ** argument_array
    )
{
    LINK_<CLOUD>
        cloud;

    cloud = new CLOUD();
    cloud->ReadPtxFile( "IN/test.ptx", COMPRESSION_None );
    cloud->WritePtxFile( "OUT/test_1.ptx" );
    cloud->WritePcfFile( "OUT/test_1.pcf" );

    cloud = new CLOUD();
    cloud->ReadPcfFile( "OUT/test_1.pcf" );
    cloud->WritePtxFile( "OUT/test_2.ptx" );
    cloud->WritePcfFile( "OUT/test_2.pcf" );

    cloud = new CLOUD();
    cloud->ReadPtxFile( "IN/test.ptx", COMPRESSION_Discretization );
    cloud->WritePtxFile( "OUT/test_3.ptx" );
    cloud->WritePcfFile( "OUT/test_3.pcf" );

    cloud = new CLOUD();
    cloud->ReadPcfFile( "OUT/test_3.pcf" );
    cloud->WritePtxFile( "OUT/test_4.ptx" );
    cloud->WritePcfFile( "OUT/test_4.pcf" );

    return 0;
}
