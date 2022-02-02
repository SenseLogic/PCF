// -- IMPORTS

import pcf.base;
import pcf.cell;
import pcf.cloud;
import pcf.compression;
import std.conv : to;
import std.stdio: writeln;

// -- FUNCTIONS

class TEST
{
    // -- ATTRIBUTES

    CLOUD
        Cloud;

    // -- OPERATIONS

    void PrintCell(
        CELL cell
        )
    {
        string
            line;

        writeln(
            "Cell : ",
            cell.PositionVector.X.GetText(),
            " ",
            cell.PositionVector.Y.GetText(),
            " ",
            cell.PositionVector.Z.GetText(),
            " (",
            cell.PointCount,
            ")"
            );

        foreach ( point_index; 0 .. cell.PointCount )
        {
            line = "    [" ~ point_index.to!string() ~ "]";

            cell.SeekComponent( 0 );

            foreach ( buffer_index, buffer; cell.BufferArray )
            {
                line ~= " " ~ cell.GetComponentValue( Cloud.ComponentArray, buffer_index ).GetText();
            }

            writeln( line );
        }
    }

    // ~~

    void Run(
        )
    {
        CELL.PostWriteDelegate = &PrintCell;
        CELL.PostReadDelegate = &PrintCell;

        Cloud = new CLOUD();
        Cloud.ReadPtxFile( "IN/test.ptx", COMPRESSION.None );
        Cloud.WritePtxFile( "OUT/test_1.ptx" );
        Cloud.WritePcfFile( "OUT/test_1.pcf" );

        Cloud = new CLOUD();
        Cloud.ReadPcfFile( "OUT/test_1.pcf" );
        Cloud.WritePtxFile( "OUT/test_2.ptx" );
        Cloud.WritePcfFile( "OUT/test_2.pcf" );

        Cloud = new CLOUD();
        Cloud.ReadPtxFile( "IN/test.ptx", COMPRESSION.Discretization );
        Cloud.WritePtxFile( "OUT/test_3.ptx" );
        Cloud.WritePcfFile( "OUT/test_3.pcf" );

        Cloud = new CLOUD();
        Cloud.ReadPcfFile( "OUT/test_3.pcf" );
        Cloud.WritePtxFile( "OUT/test_4.ptx" );
        Cloud.WritePcfFile( "OUT/test_4.pcf" );
    }
}



void main(
    string[] argument_array
    )
{
    TEST
        test;

    test = new TEST();
    test.Run();
}
