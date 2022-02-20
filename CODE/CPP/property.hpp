#pragma once

// -- IMPORTS

#include "base.hpp"
#include "stream.hpp"
#include "object.hpp"

using base::STREAM;
using base::OBJECT;

// -- TYPES

namespace pcf
{
    struct PROPERTY :
        public OBJECT
    {
        // -- ATTRIBUTES

        string
            Name,
            Value,
            Format;

        // -- CONSTRUCTORS

        PROPERTY(
            ) :
            OBJECT(),
            Name(),
            Value(),
            Format()
        {
        }

        // ~~

        PROPERTY(
            const PROPERTY & property
            ) :
            OBJECT( property ),
            Name( property.Name ),
            Value( property.Value ),
            Format( property.Format )
        {
        }

        // -- DESTRUCTORS

        virtual ~PROPERTY(
            )
        {
        }

        // -- OPERATORS

        PROPERTY & operator=(
            const PROPERTY & property
            )
        {
            Name = property.Name;
            Value = property.Value;
            Format = property.Format;

            return *this;
        }

        // -- INQUIRIES

        void Write(
            STREAM & stream
            ) const
        {
            stream.WriteText( Name );
            stream.WriteText( Value );
            stream.WriteText( Format );
        }

        // ~~

        void Dump(
            string indentation = ""
            ) const
        {
            cout << indentation << "Name : " << Name << "\n";
            cout << indentation << "Value : " << Value << "\n";
            cout << indentation << "Format : " << Format << "\n";
        }

        // -- OPERATIONS

        void Read(
            STREAM & stream
            )
        {
            stream.ReadText( Name );
            stream.ReadText( Value );
            stream.ReadText( Format );
        }
    };
}
