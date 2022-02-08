// -- IMPORTS

#include "base.hpp"
#include "cell.hpp"
#include "cloud.hpp"
#include "compression.hpp"
#include "scan.hpp"
using namespace pcf;

// -- VARIABLES

SCAN
    * Scan;
LINK_<CLOUD>
    Cloud;

// -- FUNCTIONS

void SetScan(
    SCAN & scan
    )
{
    Scan = &scan;
}

// ~~

void PrintCell(
    CELL & cell
    )
{
    uint64_t
        buffer_index,
        point_index;

    cout << "Cell : " << GetText( cell.PositionVector ) << " (" << cell.PointCount << ")\n";

    cell.SetComponentIndex( 0 );

    for ( point_index = 0;
          point_index < cell.PointCount;
          ++point_index )
    {
        cout << "    [" << point_index << "]";

        for ( buffer_index = 0;
              buffer_index < cell.BufferVector.size();
              ++buffer_index )
        {
            cout << " " << GetText( cell.GetComponentValue( Scan->ComponentVector, buffer_index ) );
        }

        cout << "\n";
    }
}

// ~~

int main(
    int argument_count,
    char ** argument_array
    )
{
    try
    {
        SCAN::PreWriteFunction = &SetScan;
        SCAN::PreReadFunction = &SetScan;
        CELL::PostWriteFunction = &PrintCell;
        CELL::PostReadFunction = &PrintCell;

        Cloud = new CLOUD();

        puts( "Reading test.ptx" );
        Cloud->ReadPtxFile( "IN/test.ptx", COMPRESSION::None );

        puts( "Writing test_1.pts" );
        Cloud->WritePtsFile( "OUT/test_1.pts" );

        puts( "Writing test_1.ptx" );
        Cloud->WritePtxFile( "OUT/test_1.ptx" );

        puts( "Writing test_1.pcf" );
        Cloud->WritePcfFile( "OUT/test_1.pcf" );

        Cloud = new CLOUD();

        puts( "Reading test_1.pcf" );
        Cloud->ReadPcfFile( "OUT/test_1.pcf" );

        puts( "Writing test_2.pts" );
        Cloud->WritePtsFile( "OUT/test_2.pts" );

        puts( "Writing test_2.ptx" );
        Cloud->WritePtxFile( "OUT/test_2.ptx" );

        puts( "Writing test_2.pcf" );
        Cloud->WritePcfFile( "OUT/test_2.pcf" );

        Cloud = new CLOUD();

        puts( "Reading test.ptx" );
        Cloud->ReadPtxFile( "IN/test.ptx", COMPRESSION::Discretization, 8, 0.1 );

        puts( "Writing test_3.pts" );
        Cloud->WritePtsFile( "OUT/test_3.pts" );

        puts( "Writing test_3.ptx" );
        Cloud->WritePtxFile( "OUT/test_3.ptx" );

        puts( "Writing test_3.pcf" );
        Cloud->WritePcfFile( "OUT/test_3.pcf" );

        Cloud = new CLOUD();

        puts( "Reading test_3.pcf" );
        Cloud->ReadPcfFile( "OUT/test_3.pcf" );

        puts( "Writing test_4.pts" );
        Cloud->WritePtsFile( "OUT/test_4.pts" );

        puts( "Writing test_4.ptx" );
        Cloud->WritePtxFile( "OUT/test_4.ptx" );

        puts( "Writing test_4.pcf" );
        Cloud->WritePcfFile( "OUT/test_4.pcf" );

        Cloud = new CLOUD();

        puts( "Reading test_4.pcf" );
        Cloud->ReadPcfFile( "OUT/test_4.pcf" );

        puts( "Writing test_5.pts" );
        Cloud->WritePtsFile( "OUT/test_5.pts" );

        puts( "Writing test_5.ptx" );
        Cloud->WritePtxFile( "OUT/test_5.ptx" );

        puts( "Writing test_5.pcf" );
        Cloud->WritePcfFile( "OUT/test_5.pcf" );

        Cloud = new CLOUD();

        puts( "Reading OUT/test_1.pts" );
        Cloud->ReadPtsFile( "OUT/test_1.pts", COMPRESSION::Discretization, 8, 0.1 );

        puts( "Writing test_6.pts" );
        Cloud->WritePtsFile( "OUT/test_6.pts" );

        puts( "Writing test_6.ptx" );
        Cloud->WritePtxFile( "OUT/test_6.ptx" );

        puts( "Writing test_6.pcf" );
        Cloud->WritePcfFile( "OUT/test_6.pcf" );
    }
    catch ( const exception & exception_ )
    {
        cerr << exception_.what() << "\n";
    }

    return 0;
}
