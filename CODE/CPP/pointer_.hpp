#pragma once

// -- TYPES

namespace base
{
    template <typename _TYPE_>
    struct POINTER_
    {
        // -- ATTRIBUTES

        _TYPE_
            * Address;

        // -- CONSTRUCTORS

        POINTER_(
            ) :
            Address( nullptr )
        {
        }

        // ~~

        POINTER_(
            const POINTER_ & link
            ) :
            Address( nullptr )
        {
            SetAddress( link.Address );
        }

        // ~~

        POINTER_(
            _TYPE_ * address
            ) :
            Address( nullptr )
        {
            SetAddress( address );
        }

        // ~~

        ~POINTER_(
            )
        {
            SetNull();
        }

        // -- OPERATORS

        POINTER_ & operator=(
            const POINTER_ & link
            )
        {
            SetAddress( link.Address );

            return *this;
        }

        // ~~

        POINTER_ & operator=(
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
            assert(
                Address == nullptr
                || Address->ReferenceCount > 0
                );

            return Address;
        }

        // ~~

        _TYPE_ & operator*(
            void
            ) const
        {
            assert(
                Address != nullptr
                && Address->ReferenceCount > 0
                );

            return *Address;
        }

        // ~~

        _TYPE_ * operator->(
            void
            ) const
        {
            assert(
                Address != nullptr
                && Address->ReferenceCount > 0
                );

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
                Address->RemovePointer();
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
                    non_const_address->AddPointer();
                    SetNull();
                    Address = non_const_address;
                }
            }
        }
    };
}
