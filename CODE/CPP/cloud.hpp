#pragma once

// -- IMPORTS

#include "base.hpp"
#include "cell.hpp"
#include "component.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "link_.hpp"
#include "object.hpp"
#include "property.hpp"
#include "scan.hpp"
#include "vector_.hpp"
#include "vector_3.hpp"

// -- TYPES

struct CLOUD :
    public OBJECT
{
    // -- ATTRIBUTES

    uint32_t
        Version;
    string
        Name;
    bool
        IsLeftHanded,
        IsZUp;
    VECTOR_<LINK_<COMPONENT>>
        ComponentVector;
    VECTOR_<LINK_<PROPERTY>>
        PropertyVector;
    VECTOR_<LINK_<SCAN>>
        ScanVector;

    // -- INQUIRIES

    void Write(
        STREAM & stream
        )
    {
        stream.WriteNatural32( Version );
        stream.WriteText( Name );
        stream.WriteBoolean( IsLeftHanded );
        stream.WriteBoolean( IsZUp );
        stream.WriteObjectVector( ComponentVector );
        stream.WriteObjectVector( PropertyVector );
        stream.WriteObjectVector( ScanVector );
    }

    // ~~

    void WritePcfFile(
        const string & output_file_path
        )
    {
        STREAM
            stream;

        stream.OpenOutputBinaryFile( output_file_path );
        stream.WriteObject( *this );
        stream.Close();
    }

    // ~~

    void WritePtxFile(
        const string & output_file_path
        )
    {
        uint64_t
            point_index;
        STREAM
            stream;

        stream.OpenOutputTextFile( output_file_path );

        for ( auto & scan : ScanVector )
        {
            stream.WriteNaturalLine( scan->ColumnCount );
            stream.WriteNaturalLine( scan->RowCount );
            stream.WriteRealLine( scan->PositionVector.X, scan->PositionVector.Y, scan->PositionVector.Z );
            stream.WriteRealLine( scan->XAxisVector.X, scan->XAxisVector.Y, scan->XAxisVector.Z );
            stream.WriteRealLine( scan->YAxisVector.X, scan->YAxisVector.Y, scan->YAxisVector.Z );
            stream.WriteRealLine( scan->ZAxisVector.X, scan->ZAxisVector.Y, scan->ZAxisVector.Z );
            stream.WriteRealLine( scan->XAxisVector.X, scan->XAxisVector.Y, scan->XAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan->YAxisVector.X, scan->YAxisVector.Y, scan->YAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan->ZAxisVector.X, scan->ZAxisVector.Y, scan->ZAxisVector.Z, 0.0 );
            stream.WriteRealLine( scan->PositionVector.X, scan->PositionVector.Y, scan->PositionVector.Z, 1.0 );

            for ( auto & cell_entry : scan->CellMap )
            {
                LINK_<CELL>
                    & cell = cell_entry.second;

                cell->SeekComponent( 0 );

                for ( point_index = 0;
                      point_index < cell->PointCount;
                      ++point_index )
                {
                    stream.WriteRealLine(
                        cell->GetComponentValue( ComponentVector, 0 ),
                        cell->GetComponentValue( ComponentVector, 1 ),
                        cell->GetComponentValue( ComponentVector, 2 ),
                        cell->GetComponentValue( ComponentVector, 3 ),
                        cell->GetComponentValue( ComponentVector, 4 ),
                        cell->GetComponentValue( ComponentVector, 5 ),
                        cell->GetComponentValue( ComponentVector, 6 )
                        );
                }
            }
        }

        stream.Close();
    }

    // -- OPERATIONS

    void Read(
        STREAM & stream
        )
    {
        stream.ReadNatural32( Version );
        stream.ReadText( Name );
        stream.ReadBoolean( IsLeftHanded );
        stream.ReadBoolean( IsZUp );
        stream.ReadObjectVector( ComponentVector );
        stream.ReadObjectVector( PropertyVector );
        stream.ReadObjectVector( ScanVector );
    }

    // ~~

    void ReadPcfFile(
        const string & input_file_path
        )
    {
        STREAM
            stream;

        stream.OpenInputBinaryFile( input_file_path );
        stream.ReadObjectValue( *this );
        stream.Close();
    }

    // ~~

    void ReadPtxFile(
        const string & input_file_path,
        const COMPRESSION compression
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
        uint64_t
            point_index;
        STREAM
            stream;
        LINK_<CELL>
            cell;
        LINK_<SCAN>
            scan;

        ComponentVector.clear();

        if ( compression == COMPRESSION_None )
        {
            ComponentVector.push_back( new COMPONENT( "X", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "Y", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "Z", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "I", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "R", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "G", 0.0, 32, COMPRESSION_None ) );
            ComponentVector.push_back( new COMPONENT( "B", 0.0, 32, COMPRESSION_None ) );
        }
        else if ( compression == COMPRESSION_Discretization )
        {
            ComponentVector.push_back( new COMPONENT( "X", 0.001 ) );
            ComponentVector.push_back( new COMPONENT( "Y", 0.001 ) );
            ComponentVector.push_back( new COMPONENT( "Z", 0.001 ) );
            ComponentVector.push_back( new COMPONENT( "I", 1.0 / 255.0 ) );
            ComponentVector.push_back( new COMPONENT( "R", 1.0 ) );
            ComponentVector.push_back( new COMPONENT( "G", 1.0 ) );
            ComponentVector.push_back( new COMPONENT( "B", 1.0 ) );
        }

        stream.OpenInputTextFile( input_file_path );

        for ( ; ; )
        {
            scan = new SCAN();

            if ( stream.ReadNaturalLine( scan->ColumnCount ) )
            {
                stream.ReadNaturalLine( scan->RowCount );
                stream.ReadRealLine( scan->PositionVector.X, scan->PositionVector.Y, scan->PositionVector.Z );
                stream.ReadRealLine( scan->XAxisVector.X, scan->XAxisVector.Y, scan->XAxisVector.Z );
                stream.ReadRealLine( scan->YAxisVector.X, scan->YAxisVector.Y, scan->YAxisVector.Z );
                stream.ReadRealLine( scan->ZAxisVector.X, scan->ZAxisVector.Y, scan->ZAxisVector.Z );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );
                stream.ReadRealLine( position_x, position_y, position_z, position_w );

                scan->PointCount = scan->ColumnCount * scan->RowCount;

                for ( point_index = 0;
                      point_index < scan->PointCount;
                      ++point_index )
                {
                    stream.ReadRealLine( position_x, position_y, position_z, intensity, color_red, color_green, color_blue );

                    cell = scan->GetCell( ComponentVector, position_x, position_y, position_z );
                    cell->AddComponentValue( ComponentVector, 0, position_x );
                    cell->AddComponentValue( ComponentVector, 1, position_y );
                    cell->AddComponentValue( ComponentVector, 2, position_z );
                    cell->AddComponentValue( ComponentVector, 3, intensity );
                    cell->AddComponentValue( ComponentVector, 4, color_red );
                    cell->AddComponentValue( ComponentVector, 5, color_green );
                    cell->AddComponentValue( ComponentVector, 6, color_blue );

                    ++cell->PointCount;
                }

                ScanVector.push_back( scan );
            }
            else
            {
                break;
            }
        }

        stream.Close();
    }
};
