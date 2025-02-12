#include "loadlib.hpp"

#include <any>
#include <print>

#define LOG_OR_FAIL( var )                                                                         \
    if ( !var ) {                                                                                  \
        std::println( "[!] {} is null", #var );                                                    \
        return false;                                                                              \
    } else                                                                                         \
        std::println( "[+] {} = {}", #var, var )

auto map::loader< map::variant::LOADLIBRARY >::inject( const std::string_view dll ) const -> bool {
    LOG_OR_FAIL( m_proc_handle.get( ) );

    char          full_path[ MAX_PATH ];
    unsigned long _gfpn_res = GetFullPathNameA( dll.data( ), sizeof full_path, full_path, nullptr );
    LOG_OR_FAIL( _gfpn_res );

    void *k32 = GetModuleHandleA( "kernel32.dll" );
    LOG_OR_FAIL( k32 );

    void *lla = GetProcAddress( static_cast< HMODULE >( k32 ), "LoadLibraryA" );
    LOG_OR_FAIL( lla );

    void *str = VirtualAllocEx(
            m_proc_handle.get( ), nullptr, sizeof full_path, MEM_RESERVE | MEM_COMMIT,
            PAGE_EXECUTE_READWRITE );
    LOG_OR_FAIL( str );

    int _wpm_res = WriteProcessMemory(
            m_proc_handle.get( ), str, full_path, strlen( full_path ), nullptr );
    LOG_OR_FAIL( _wpm_res );

    void *_ct_res = CreateRemoteThread(
            m_proc_handle.get( ), nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( lla ),
            str, 0, nullptr );
    LOG_OR_FAIL( _ct_res );

    return true;
}

#undef LOG_OR_FAIL
