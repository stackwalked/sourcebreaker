#include "loadlib.hpp"

#define FAIL_IF_ZERO( t, var, ex )                                                                 \
    t var;                                                                                         \
    if ( var = ex; !var )                                                                          \
    return false

bool map::loader< map::variant::LOADLIBRARY >::inject( const std::string_view dll ) const {
    char full_path[ MAX_PATH ];

    FAIL_IF_ZERO(
            unsigned long, _gfpn_res,
            GetFullPathNameA( dll.data( ), sizeof full_path, full_path, nullptr ) );

    FAIL_IF_ZERO( HMODULE, k32, GetModuleHandleA( "kernel32.dll" ) );

    FAIL_IF_ZERO( void *, lla, GetProcAddress( k32, "LoadLibraryA" ) );

    FAIL_IF_ZERO(
            void *, str,
            VirtualAllocEx(
                    m_proc_handle.get( ), nullptr, sizeof full_path, MEM_RESERVE | MEM_COMMIT,
                    PAGE_EXECUTE_READWRITE ) );

    FAIL_IF_ZERO(
            int, _wpm_res,
            WriteProcessMemory(
                    m_proc_handle.get( ), str, full_path, strlen( full_path ), nullptr ) );

    CreateRemoteThread(
            m_proc_handle.get( ), nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( lla ),
            str, 0, nullptr );

    return true;
}
