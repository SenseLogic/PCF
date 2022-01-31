module pcf.cloud;

// -- IMPORTS

import pcf.cell;
import pcf.component;
import pcf.compression;
import pcf.file;
import pcf.property;
import pcf.scalar;
import pcf.scan;
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
        IsZUp,
        IsCompressed;
    COMPONENT[]
        ComponentArray;
    PROPERTY[]
        PropertyArray;
    SCAN[]
        ScanArray;

    // -- INQUIRIES

    void Write(
        FILE file
        )
    {
        file.WriteNatural32( Version );
        file.WriteText( Name );
        file.WriteBoolean( IsLeftHanded );
        file.WriteBoolean( IsZUp );
        file.WriteObjectArray( ComponentArray );
        file.WriteObjectArray( PropertyArray );
        file.WriteObjectArray( ScanArray );
    }

    // ~~

    void WritePcfFile(
        string output_file_path
        )
    {
        FILE
            file;

        file = new FILE();
        file.OpenOutputBinaryFile( output_file_path );
        file.WriteObject( this );
        file.Close();
    }

    // ~~

    void WritePtxFile(
        string output_file_path
        )
    {
        FILE
            file;

        file = new FILE();
        file.OpenOutputTextFile( output_file_path );

        foreach ( scan; ScanArray )
        {
            file.WriteNaturalLine( scan.ColumnCount );
            file.WriteNaturalLine( scan.RowCount );
            file.WriteRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z );
            file.WriteRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z );
            file.WriteRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z );
            file.WriteRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z );
            file.WriteRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z, 0.0 );
            file.WriteRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z, 0.0 );
            file.WriteRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z, 0.0 );
            file.WriteRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z, 1.0 );

            foreach ( cell; scan.CellMap.byValue )
            {
                cell.SeekComponent( 0 );

                foreach ( point_index; 0 .. cell.PointCount )
                {
                    file.WriteRealLine(
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

        file.Close();
    }

    // -- OPERATIONS

    void Read(
        FILE file
        )
    {
        file.ReadNatural32( Version );
        file.ReadText( Name );
        file.ReadBoolean( IsLeftHanded );
        file.ReadBoolean( IsZUp );
        file.ReadObjectArray( ComponentArray );
        file.ReadObjectArray( PropertyArray );
        file.ReadObjectArray( ScanArray );
    }

    // ~~

    void Compress(
        )
    {
        if ( !IsCompressed )
        {
            foreach ( scan; ScanArray )
            {
                scan.Compress( ComponentArray );
            }

            IsCompressed = true;
        }
    }

    // ~~

    void ReadPcfFile(
        string input_file_path
        )
    {
        FILE
            file;

        file = new FILE();
        file.OpenInputBinaryFile( input_file_path );
        file.ReadObjectValue( this );
        file.Close();
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
        FILE
            file;
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

        file = new FILE();
        file.OpenInputTextFile( input_file_path );

        for ( ; ; )
        {
            scan = new SCAN();

            if ( file.ReadNaturalLine( scan.ColumnCount ) )
            {
                file.ReadNaturalLine( scan.RowCount );
                file.ReadRealLine( scan.PositionVector.X, scan.PositionVector.Y, scan.PositionVector.Z );
                file.ReadRealLine( scan.XAxisVector.X, scan.XAxisVector.Y, scan.XAxisVector.Z );
                file.ReadRealLine( scan.YAxisVector.X, scan.YAxisVector.Y, scan.YAxisVector.Z );
                file.ReadRealLine( scan.ZAxisVector.X, scan.ZAxisVector.Y, scan.ZAxisVector.Z );
                file.ReadRealLine( position_x, position_y, position_z, position_w );
                file.ReadRealLine( position_x, position_y, position_z, position_w );
                file.ReadRealLine( position_x, position_y, position_z, position_w );
                file.ReadRealLine( position_x, position_y, position_z, position_w );

                scan.PointCount = scan.ColumnCount * scan.RowCount;

                foreach ( point_index; 0 .. scan.PointCount )
                {
                    file.ReadRealLine( position_x, position_y, position_z, intensity, color_red, color_green, color_blue );

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

        file.Close();

        Compress();
    }
}
