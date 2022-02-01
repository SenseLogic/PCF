module pcf.cloud;

// -- IMPORTS

import pcf.cell;
import pcf.component;
import pcf.compression;
import pcf.property;
import pcf.scan;
import pcf.stream;
import pcf.vector_3;
import std.conv : to;
import std.string : strip;

// -- TYPES

class CLOUD
{
    // -- ATTRIBUTES

    uint
        Version;
    string
        Name;
    bool
        IsLeftHanded,
        IsZUp;
    COMPONENT[]
        ComponentArray;
    PROPERTY[]
        PropertyArray;
    SCAN[]
        ScanArray;

    // -- INQUIRIES

    void Write(
        STREAM stream
        )
    {
        stream.WriteNatural32( Version );
        stream.WriteText( Name );
        stream.WriteBoolean( IsLeftHanded );
        stream.WriteBoolean( IsZUp );
        stream.WriteObjectArray( ComponentArray );
        stream.WriteObjectArray( PropertyArray );
        stream.WriteObjectArray( ScanArray );
    }

    // ~~

    void WritePcfFile(
        string output_file_path
        )
    {
        STREAM
            stream;

        stream = new STREAM();
        stream.OpenOutputBinaryFile( output_file_path );
        stream.WriteObject( this );
        stream.Close();
    }

    // ~~

    void WritePtxFile(
        string output_file_path
        )
    {
        STREAM
            stream;

        stream = new STREAM();
        stream.OpenOutputTextFile( output_file_path );

        foreach ( scan; ScanArray )
        {
            stream.WriteNaturalLine( scan.ColumnCount );
            stream.WriteNaturalLine( scan.RowCount );
            stream.WriteRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z );
            stream.WriteRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z );
            stream.WriteRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z );
            stream.WriteRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z );
            stream.WriteRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z, 1.0 );

            foreach ( cell; scan.CellMap.byValue )
            {
                cell.SeekComponent( 0 );

                foreach ( point_index; 0 .. cell.PointCount )
                {
                    stream.WriteRealLine(
                        cell.GetComponentValue( ComponentArray, 0 ),
                        cell.GetComponentValue( ComponentArray, 1 ),
                        cell.GetComponentValue( ComponentArray, 2 ),
                        cell.GetComponentValue( ComponentArray, 3 ),
                        cell.GetComponentValue( ComponentArray, 4 ),
                        cell.GetComponentValue( ComponentArray, 5 ),
                        cell.GetComponentValue( ComponentArray, 6 )
                        );
                }
            }
        }

        stream.Close();
    }

    // -- OPERATIONS

    void Read(
        STREAM stream
        )
    {
        stream.ReadNatural32( Version );
        stream.ReadText( Name );
        stream.ReadBoolean( IsLeftHanded );
        stream.ReadBoolean( IsZUp );
        stream.ReadObjectArray( ComponentArray );
        stream.ReadObjectArray( PropertyArray );
        stream.ReadObjectArray( ScanArray );
    }

    // ~~

    void ReadPcfFile(
        string input_file_path
        )
    {
        STREAM
            stream;

        stream = new STREAM();
        stream.OpenInputBinaryFile( input_file_path );
        stream.ReadObjectValue( this );
        stream.Close();
    }

    // ~~

    void ReadPtxFile(
        string input_file_path,
        COMPRESSION compression
        )
    {
        double
            color_blue,
            color_green,
            intensity,
            color_red,
            position_w,
            position_x,
            position_y,
            position_z;
        string
            line;
        CELL
            cell;
        STREAM
            stream;
        SCAN
            scan;

        ComponentArray = null;

        if ( compression == COMPRESSION.None )
        {
            ComponentArray ~= new COMPONENT( "X", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "Y", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "Z", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "I", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "R", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "G", 0.0, 32, COMPRESSION.None );
            ComponentArray ~= new COMPONENT( "B", 0.0, 32, COMPRESSION.None );
        }
        else if ( compression == COMPRESSION.Discretization )
        {
            ComponentArray ~= new COMPONENT( "X", 0.001 );
            ComponentArray ~= new COMPONENT( "Y", 0.001 );
            ComponentArray ~= new COMPONENT( "Z", 0.001 );
            ComponentArray ~= new COMPONENT( "I", 1.0 / 255.0 );
            ComponentArray ~= new COMPONENT( "R", 1.0 );
            ComponentArray ~= new COMPONENT( "G", 1.0 );
            ComponentArray ~= new COMPONENT( "B", 1.0 );
        }

        stream = new STREAM();
        stream.OpenInputTextFile( input_file_path );

        for ( ; ; )
        {
            scan = new SCAN();

            if ( stream.ReadNaturalLine( scan.ColumnCount ) )
            {
                stream.ReadNaturalLine( scan.RowCount );
                stream.ReadRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z );
                stream.ReadRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z );
                stream.ReadRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z );
                stream.ReadRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );

                scan.PointCount = scan.ColumnCount * scan.RowCount;

                foreach ( point_index; 0 .. scan.PointCount )
                {
                    stream.ReadRealLine( position_x, position_y, position_z, intensity, color_red, color_green, color_blue );

                    cell = scan.GetCell( ComponentArray, position_x, position_y, position_z );
                    cell.AddComponentValue( ComponentArray, 0, position_x );
                    cell.AddComponentValue( ComponentArray, 1, position_y );
                    cell.AddComponentValue( ComponentArray, 2, position_z );
                    cell.AddComponentValue( ComponentArray, 3, intensity );
                    cell.AddComponentValue( ComponentArray, 4, color_red );
                    cell.AddComponentValue( ComponentArray, 5, color_green );
                    cell.AddComponentValue( ComponentArray, 6, color_blue );

                    ++cell.PointCount;
                }

                ScanArray ~= scan;
            }
            else
            {
                break;
            }
        }

        stream.Close();
    }
}
