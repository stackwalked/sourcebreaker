#pragma once

#include <Windows.h>
#include <string_view>
#include <vector>

#include "address.hpp"

namespace mem {
    namespace detail {
        // converts IDA-style signature to byte array
        auto pattern_to_bytes( std::string_view ) -> std::vector< int >;
    }

    // neat wrapper around HMODULE, pointer-to-module
    class module_t {
        const char *m_name;
        address_t   m_address;

    public:
        // construction
        module_t( ) : m_name( "" ) {}

        explicit module_t( const char *name )
            : m_name( name ), m_address( GetModuleHandleA( name ) ) {}

        // destruction
        ~module_t( ) = default;

        [[nodiscard]] constexpr auto base( ) const -> address_t { return m_address; }
        [[nodiscard]] constexpr auto name( ) const -> const char * { return m_name; }

        auto header_dos( ) -> IMAGE_DOS_HEADER * {
            return m_address.cast< IMAGE_DOS_HEADER * >( );
        }

        auto header_nt( ) -> IMAGE_NT_HEADERS * {
            return m_address.offset( header_dos( )->e_lfanew ).ptr<
                IMAGE_NT_HEADERS >( );
        }
    };

    // dll_t functional-style operators

    // WinAPI GetProcAddress
    auto find_export( const module_t &, const char *name ) -> address_t;

    // accepts IDA sig
    auto find_pattern( module_t &, const char *sig ) -> address_t;
}
