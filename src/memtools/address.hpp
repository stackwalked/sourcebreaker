#pragma once

#include <cstddef>
#include <cstdint>

namespace mem {
    // wrapper class around std::uintptr_t
    // @credit: https://github.com/W1lliam1337/digital-sdk/blob/master/digital-sdk/core/utils/memory/address.hh
    class address_t {
    public:
        address_t( ) = default;

        explicit address_t( const std::uintptr_t address ) : m_address{ address } {}

        explicit address_t( void *address )
            : m_address{ reinterpret_cast< std::uintptr_t >( address ) } {}

        explicit operator std::uintptr_t( ) const { return m_address; }
        explicit operator void *( ) const { return reinterpret_cast< void * >( m_address ); }

        auto operator==( const address_t address ) const -> bool {
            return as< std::uintptr_t >( ) == address.as< std::uintptr_t >( );
        }

        auto operator!=( const address_t address ) const -> bool {
            return as< std::uintptr_t >( ) != address.as< std::uintptr_t >( );
        }

        [[nodiscard]] auto is_valid( ) const -> bool { return m_address && this; }
        // NOLINT(clang-diagnostic-undefined-bool-conversion)

        template < typename T = address_t >
        [[nodiscard]] auto to( ) const -> T { return *reinterpret_cast< T * >( m_address ); }

        template < typename T = address_t >
        [[nodiscard]] auto as( ) const -> T { return m_address ? T( m_address ) : T( ); }

        template < typename T = address_t >
        [[nodiscard]] auto at( const std::ptrdiff_t offset ) const -> T {
            return m_address ? *reinterpret_cast< T * >( m_address + offset ) : T( );
        }

        template < typename T >
        auto read( ) -> T {
            return *ptr< T >( );
        }

        template < typename T >
        auto ptr( ) -> T * {
            return reinterpret_cast< T * >( m_address );
        }

        template < typename T >
        auto cast( ) -> T {
            return reinterpret_cast< T >( m_address );
        }

        template < typename T = address_t >
        [[nodiscard]] auto offset( const std::ptrdiff_t offset ) const -> T {
            return m_address ? T( m_address + offset ) : T( );
        }

        template < typename T = address_t >
        [[nodiscard]] auto get( std::ptrdiff_t dereferences = 1 ) const -> T {
            std::ptrdiff_t object = m_address;

            while ( dereferences-- ) {
                if ( !object )
                    break;

                object = *reinterpret_cast< std::ptrdiff_t * >( object );
            }

            return reinterpret_cast< T >( object );
        }

        template < typename T = address_t >
        [[nodiscard]] auto relative( const std::ptrdiff_t offset = 0x1 ) const -> T {
            const std::ptrdiff_t new_address = m_address + offset;
            const std::int32_t relative_offset = *reinterpret_cast< std::int32_t * >( new_address );

            if ( !relative_offset )
                return T( );

            return reinterpret_cast< T >( new_address + 4 + relative_offset );
        }

        template < typename T = std::ptrdiff_t >
        auto set( const T &value ) const -> void {
            *reinterpret_cast< T * >( m_address ) = value;
        }

    private:
        std::uintptr_t m_address{ };
    };
}
