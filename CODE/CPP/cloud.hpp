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

namespace pcf
{
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
        VECTOR_<LINK_<PROPERTY>>
            PropertyVector;
        VECTOR_<LINK_<SCAN>>
            ScanVector;

        // -- CONSTRUCTORS

        CLOUD(
            ) :
            OBJECT(),
            Version( 0 ),
            Name(),
            IsLeftHanded( false ),
            IsZUp( false ),
            PropertyVector(),
            ScanVector()
        {
        }

        // ~~

        CLOUD(
            const CLOUD & cloud
            ) :
            OBJECT( cloud ),
            Version( cloud.Version ),
            Name( cloud.Name ),
            IsLeftHanded( cloud.IsLeftHanded ),
            IsZUp( cloud.IsZUp ),
            PropertyVector( cloud.PropertyVector ),
            ScanVector( cloud.ScanVector )
        {
        }

        // -- DESTRUCTORS

        virtual ~CLOUD(
            )
        {
        }

        // -- OPERATORS

        CLOUD & operator=(
            const CLOUD & cloud
            )
        {
            Version = cloud.Version;
            Name = cloud.Name;
            IsLeftHanded = cloud.IsLeftHanded;
            IsZUp = cloud.IsZUp;
            PropertyVector = cloud.PropertyVector;
            ScanVector = cloud.ScanVector;

            return *this;
        }

        // -- INQUIRIES

        uint64_t GetPointCount(
            ) const
        {
            uint64_t
                point_count;

            point_count = 0;

            for ( auto & scan : ScanVector )
            {
                point_count += scan->PointCount;
            }

            return point_count;
        }

        // ~~

        void Dump(
            string indentation = ""
            ) const
        {
            uint64_t
                property_index,
                scan_index;

            cout << indentation << "Version : " << Version << "\n";
            cout << indentation << "Name : " << Name << "\n";
            cout << indentation << "IsLeftHanded : " << GetText( IsLeftHanded ) << "\n";
            cout << indentation << "IsZUp : " << GetText( IsZUp ) << "\n";

            for ( property_index = 0;
                  property_index < PropertyVector.size();
                  ++property_index )
            {
                cout << indentation << "Property[" << property_index << "] :" << "\n";

                PropertyVector[ property_index ]->Dump( indentation + "    " );
            }

            for ( scan_index = 0;
                  scan_index < ScanVector.size();
                  ++scan_index )
            {
                cout << indentation << "Scan[" << scan_index << "] :" << "\n";

                ScanVector[ scan_index ]->Dump( indentation + "    " );
            }
        }

        // ~~

        void Write(
            STREAM & stream
            )
        {
            stream.WriteNatural32( Version );
            stream.WriteText( Name );
            stream.WriteBoolean( IsLeftHanded );
            stream.WriteBoolean( IsZUp );
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
            stream.CloseOutputBinaryFile();
        }

        // ~~

        void WritePtsFile(
            const string & output_file_path
            )
        {
            uint64_t
                point_index;
            STREAM
                stream;

            stream.OpenOutputTextFile( output_file_path );
            stream.WriteNaturalLine( GetPointCount() );

            for ( auto & scan : ScanVector )
            {
                for ( auto & cell_entry : scan->CellMap )
                {
                    LINK_<CELL>
                        & cell = cell_entry.second;

                    cell->SetComponentIndex( 0 );

                    for ( point_index = 0;
                          point_index < cell->PointCount;
                          ++point_index )
                    {
                        stream.WriteRealLine(
                            cell->GetComponentValue( scan->ComponentVector, 0 ),
                            cell->GetComponentValue( scan->ComponentVector, 1 ),
                            cell->GetComponentValue( scan->ComponentVector, 2 ),
                            cell->GetComponentValue( scan->ComponentVector, 3 ),
                            cell->GetComponentValue( scan->ComponentVector, 4 ),
                            cell->GetComponentValue( scan->ComponentVector, 5 ),
                            cell->GetComponentValue( scan->ComponentVector, 6 )
                            );
                    }
                }
            }

            stream.CloseOutputTextFile();
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

                    cell->SetComponentIndex( 0 );

                    for ( point_index = 0;
                          point_index < cell->PointCount;
                          ++point_index )
                    {
                        stream.WriteRealLine(
                            cell->GetComponentValue( scan->ComponentVector, 0 ),
                            cell->GetComponentValue( scan->ComponentVector, 1 ),
                            cell->GetComponentValue( scan->ComponentVector, 2 ),
                            cell->GetComponentValue( scan->ComponentVector, 3 ),
                            cell->GetComponentValue( scan->ComponentVector, 4 ),
                            cell->GetComponentValue( scan->ComponentVector, 5 ),
                            cell->GetComponentValue( scan->ComponentVector, 6 )
                            );
                    }
                }
            }

            stream.CloseOutputTextFile();
        }

        // -- OPERATIONS

        void Clear(
            )
        {
            PropertyVector.clear();
            ScanVector.clear();
        }

        // ~~

        void Read(
            STREAM & stream
            )
        {
            stream.ReadNatural32( Version );
            stream.ReadText( Name );
            stream.ReadBoolean( IsLeftHanded );
            stream.ReadBoolean( IsZUp );
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
            stream.CloseInputBinaryFile();
        }

        // ~~

        void ReadPtsFile(
            const string & input_file_path,
            const COMPRESSION compression,
            uint16_t position_bit_count = 8,
            double position_precision = 0.001,
            double position_minimum = 0.0,
            double position_maximum = 0.0,
            uint16_t intensity_bit_count = 12,
            double intensity_precision = 1.0,
            double intensity_minimum = -2048.0,
            double intensity_maximum = 2047.0,
            uint16_t color_bit_count = 8,
            double color_precision = 1.0,
            double color_minimum = 0.0,
            double color_maximum = 0.0
            )
        {
            double
                color_blue,
                color_green,
                intensity,
                color_red,
                position_x,
                position_y,
                position_z;
            uint64_t
                point_index;
            STREAM
                stream;
            CELL
                * cell;
            LINK_<SCAN>
                scan;

            stream.OpenInputTextFile( input_file_path );

            scan = new SCAN();

            if ( compression == COMPRESSION::None )
            {
                scan->ComponentVector.push_back( new COMPONENT( "X", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "Y", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "Z", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "I", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "R", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "G", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                scan->ComponentVector.push_back( new COMPONENT( "B", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
            }
            else
            {
                assert( compression == COMPRESSION::Discretization );

                scan->ComponentVector.push_back( new COMPONENT( "X", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "Y", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "Z", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "I", COMPRESSION::Discretization, intensity_bit_count, intensity_precision, intensity_minimum, intensity_minimum, intensity_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "R", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "G", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
                scan->ComponentVector.push_back( new COMPONENT( "B", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
            }

            if ( stream.ReadNaturalLine( scan->PointCount ) )
            {
                scan->ColumnCount = scan->PointCount;
                scan->RowCount = 1;

                for ( point_index = 0;
                      point_index < scan->PointCount;
                      ++point_index )
                {
                    stream.ReadRealLine( position_x, position_y, position_z, intensity, color_red, color_green, color_blue );

                    cell = scan->GetCell( position_x, position_y, position_z );
                    cell->AddComponentValue( scan->ComponentVector, 0, position_x );
                    cell->AddComponentValue( scan->ComponentVector, 1, position_y );
                    cell->AddComponentValue( scan->ComponentVector, 2, position_z );
                    cell->AddComponentValue( scan->ComponentVector, 3, intensity );
                    cell->AddComponentValue( scan->ComponentVector, 4, color_red );
                    cell->AddComponentValue( scan->ComponentVector, 5, color_green );
                    cell->AddComponentValue( scan->ComponentVector, 6, color_blue );
                    ++cell->PointCount;
                }

                ScanVector.push_back( scan );
            }

            stream.CloseInputTextFile();
        }

        // ~~

        void ReadPtxFile(
            const string & input_file_path,
            const COMPRESSION compression,
            uint16_t position_bit_count = 8,
            double position_precision = 0.001,
            double position_minimum = 0.0,
            double position_maximum = 0.0,
            uint16_t intensity_bit_count = 8,
            double intensity_precision = 1.0 / 255.0,
            double intensity_minimum = 0.0,
            double intensity_maximum = 1.0,
            uint16_t color_bit_count = 8,
            double color_precision = 1.0,
            double color_minimum = 0.0,
            double color_maximum = 255.0
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
            uint64_t
                point_index;
            STREAM
                stream;
            CELL
                * cell;
            LINK_<SCAN>
                scan;

            stream.OpenInputTextFile( input_file_path );

            for ( ; ; )
            {
                scan = new SCAN();

                if ( compression == COMPRESSION::None )
                {
                    scan->ComponentVector.push_back( new COMPONENT( "X", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "Y", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "Z", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "I", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "R", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "G", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                    scan->ComponentVector.push_back( new COMPONENT( "B", COMPRESSION::None, 32, 0.0, 0.0, 0.0, 0.0 ) );
                }
                else
                {
                    assert( compression == COMPRESSION::Discretization );

                    scan->ComponentVector.push_back( new COMPONENT( "X", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "Y", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "Z", COMPRESSION::Discretization, position_bit_count, position_precision, position_minimum, position_minimum, position_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "I", COMPRESSION::Discretization, intensity_bit_count, intensity_precision, intensity_minimum, intensity_minimum, intensity_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "R", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "G", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
                    scan->ComponentVector.push_back( new COMPONENT( "B", COMPRESSION::Discretization, color_bit_count, color_precision, color_minimum, color_minimum, color_maximum ) );
                }

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

                        cell = scan->GetCell( position_x, position_y, position_z );
                        cell->AddComponentValue( scan->ComponentVector, 0, position_x );
                        cell->AddComponentValue( scan->ComponentVector, 1, position_y );
                        cell->AddComponentValue( scan->ComponentVector, 2, position_z );
                        cell->AddComponentValue( scan->ComponentVector, 3, intensity );
                        cell->AddComponentValue( scan->ComponentVector, 4, color_red );
                        cell->AddComponentValue( scan->ComponentVector, 5, color_green );
                        cell->AddComponentValue( scan->ComponentVector, 6, color_blue );
                        ++cell->PointCount;
                    }

                    ScanVector.push_back( scan );
                }
                else
                {
                    break;
                }
            }

            stream.CloseInputTextFile();
        }
    };
}
