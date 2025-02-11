#include "module.hpp"

auto mem::detail::pattern_to_bytes( std::string_view pat ) -> std::vector< int > {
    auto bytes = std::vector< int >{ };

    const auto start = const_cast< char * >( pat.data( ) );
    const auto end   = start + pat.length( );

    for ( auto current = start; current < end; ++current ) {
        if ( *current == '?' ) {
            ++current;

            if ( *current == '?' )
                ++current;

            bytes.emplace_back( -1 );
        } else
            bytes.emplace_back( strtoul( current, &current, 16 ) );
    }
    return bytes;
}

auto mem::find_export( const module_t &dll, const char *name ) -> mem::address_t {
    return static_cast< address_t >( GetProcAddress( dll.base( ).cast< HMODULE >( ), name ) );
}

auto mem::find_pattern( module_t &dll, const char *sig ) -> address_t {
    const std::vector< int > bytes = detail::pattern_to_bytes( sig );

    const unsigned long image_size = dll.header_nt( )->OptionalHeader.SizeOfImage;
    for ( unsigned long i = 0ul; i < image_size - bytes.size( ); i++ ) {
        bool found = true;

        for ( unsigned long j = 0ul; j < bytes.size( ); j++ ) {
            if ( bytes[ j ] == -1 ) // = "?" placeholder byte
                continue;
            if ( dll.base( ).offset( i + j ).read< std::uint8_t >( ) == bytes[ j ] )
                continue;

            found = false;
            break;
        }

        if ( !found )
            continue;

        return dll.base( ).offset( i );
    }

    // nothing found
    return { };
}
