// -- IMPORTS

import pcf.cloud;
import pcf.compression;

// -- FUNCTIONS

void main(
    string[] argument_array
    )
{
    CLOUD
        cloud;

    cloud = new CLOUD();
    cloud.ReadPtxFile( "IN/test.ptx", COMPRESSION.None );
    cloud.WritePtxFile( "OUT/test_1.ptx" );
    cloud.WritePcfFile( "OUT/test_1.pcf" );

    cloud = new CLOUD();
    cloud.ReadPcfFile( "OUT/test_1.pcf" );
    cloud.WritePtxFile( "OUT/test_2.ptx" );
    cloud.WritePcfFile( "OUT/test_2.pcf" );

    cloud = new CLOUD();
    cloud.ReadPtxFile( "IN/test.ptx", COMPRESSION.Discretization );
    cloud.WritePtxFile( "OUT/test_3.ptx" );
    cloud.WritePcfFile( "OUT/test_3.pcf" );

    cloud = new CLOUD();
    cloud.ReadPcfFile( "OUT/test_3.pcf" );
    cloud.WritePtxFile( "OUT/test_4.ptx" );
    cloud.WritePcfFile( "OUT/test_4.pcf" );
}
