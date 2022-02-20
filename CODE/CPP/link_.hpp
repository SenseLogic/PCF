#pragma once

// -- TYPES

namespace base
{
    template <typename _TYPE_>
    struct LINK_
    {
        // -- ATTRIBUTES

        _TYPE_
            * Address;

        // -- CONSTRUCTORS

        LINK_(
            ) :
            Address( nullptr )
        {
        }

        // ~~

        LINK_(
            const LINK_ & link
            ) :
            Address( nullptr )
        {
            SetAddress( link.Address );
        }

        // ~~

        LINK_(
            _TYPE_ * address
            ) :
            Address( nullptr )
        {
            SetAddress( address );
        }

        // ~~

        ~LINK_(
            )
        {
            SetNull();
        }

        // -- OPERATORS

        LINK_ & operator=(
            const LINK_ & link
            )
        {
            SetAddress( link.Address );

            return *this;
        }

        // ~~

        LINK_ & operator=(
            const _TYPE_ * address
            )
        {
            SetAddress( address );

            return *this;
        }

        // ~~

        operator _TYPE_ *(
            void
            ) const
        {
            return Address;
        }

        // ~~

        _TYPE_ & operator*(
            void
            ) const
        {
            assert( Address != nullptr );

            return *Address;
        }

        // ~~

        _TYPE_ * operator->(
            void
            ) const
        {
            assert( Address != nullptr );

            return Address;
        }

        // -- INQUIRIES

        bool IsNull(
            ) const
        {
            return Address == nullptr;
        }

        // -- OPERATIONS

        void SetNull(
            )
        {
            if ( Address != nullptr )
            {
                Address->RemoveLink();
                Address = nullptr;
            }
        }

        // ~~

        void SetAddress(
            const _TYPE_ * address
            )
        {
            _TYPE_
                * non_const_address;

            if ( Address != address )
            {
                if ( address == nullptr )
                {
                    SetNull();
                }
                else
                {
                    non_const_address = ( _TYPE_ * )address;
                    non_const_address->AddLink();
                    SetNull();
                    Address = non_const_address;
                }
            }
        }
    };
}
