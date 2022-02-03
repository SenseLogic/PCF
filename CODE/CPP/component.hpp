#pragma once

// -- IMPORTS

#include "base.hpp"
#include "compression.hpp"
#include "stream.hpp"
#include "object.hpp"

// -- TYPES

namespace pcf
{
    struct COMPONENT :
        public OBJECT
    {
        // -- ATTRIBUTES

        string
            Name;
        COMPRESSION
            Compression;
        uint16_t
            BitCount;
        double
            Precision,
            MinimumValue,
            MaximumValue,
            OneOverPrecision;

        // -- CONSTRUCTORS

        COMPONENT(
            ) :
            OBJECT(),
            Name(),
            Compression( COMPRESSION::None ),
            BitCount( 0 ),
            Precision( 0.0 ),
            MinimumValue( 0.0 ),
            MaximumValue( 0.0 ),
            OneOverPrecision( 0.0 )
        {
        }

        // ~~

        COMPONENT(
            const COMPONENT & component
            ) :
            OBJECT( component ),
            Name( component.Name ),
            Compression( component.Compression ),
            BitCount( component.BitCount ),
            Precision( component.Precision ),
            MinimumValue( component.MinimumValue ),
            MaximumValue( component.MaximumValue ),
            OneOverPrecision( component.OneOverPrecision )
        {
        }

        // ~~

        COMPONENT(
            string name,
            COMPRESSION compression = COMPRESSION::Discretization,
            uint16_t bit_count = 8,
            double precision = 1.0,
            double minimum_value = 0.0,
            double maximum_value = 0.0
            ) :
            OBJECT(),
            Name( name ),
            Compression( compression ),
            BitCount( bit_count ),
            Precision( precision ),
            MinimumValue( minimum_value ),
            MaximumValue( maximum_value ),
            OneOverPrecision( 1.0 / precision )
        {
        }

        // -- DESTRUCTORS

        virtual ~COMPONENT(
            )
        {
        }

        // -- OPERATORS

        COMPONENT & operator=(
            const COMPONENT & component
            )
        {
            Name = component.Name;
            Compression = component.Compression;
            BitCount = component.BitCount;
            Precision = component.Precision;
            MinimumValue = component.MinimumValue;
            MaximumValue = component.MaximumValue;
            OneOverPrecision = component.OneOverPrecision;

            return *this;
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            )
        {
            stream.WriteText( Name );
            stream.WriteNatural16( ( uint16_t )Compression );
            stream.WriteNatural16( BitCount );
            stream.WriteReal64( Precision );
            stream.WriteReal64( MinimumValue );
            stream.WriteReal64( MaximumValue );
            stream.WriteReal64( OneOverPrecision );
        }

        // -- OPERATIONS

        void Read(
            STREAM & stream
            )
        {
            stream.ReadText( Name );
            stream.ReadNatural16( ( uint16_t & )Compression );
            stream.ReadNatural16( BitCount );
            stream.ReadReal64( Precision );
            stream.ReadReal64( MinimumValue );
            stream.ReadReal64( MaximumValue );
            stream.ReadReal64( OneOverPrecision );
        }
    };
}
