#pragma once

#include <Windows.h>
// ReSharper disable once CppWrongIncludesOrder
#include <TlHelp32.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>

#include <mapper/api/loader.hpp>

template <> class map::loader< map::variant::LOADLIBRARY > final {
    struct detail {
        // HANDLE = void*, => std::unique_ptr<void> ~ HANDLE.
        // custom winapi dtor. applied
        using handle = std::unique_ptr< void, decltype( []( void *ptr ) {
                                            ptr &&ptr != INVALID_HANDLE_VALUE &&CloseHandle( ptr );
                                        } ) >;

        // enumerates processes with TlHelp32
        // has to be inline, otherwise linker error. weird
        static auto get_proc( const std::wstring_view name ) -> handle {
            void *snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
            if ( snapshot == INVALID_HANDLE_VALUE )
                return nullptr;

            PROCESSENTRY32W pe;
            pe.dwSize = sizeof( PROCESSENTRY32W );

            unsigned long ret = 0;
            for ( bool proc = Process32FirstW( snapshot, &pe ); proc;
                  proc      = Process32NextW( snapshot, &pe ) ) {
                if ( wcscmp( pe.szExeFile, name.data( ) ) )
                    continue;

                ret = pe.th32ProcessID;
                break;
            }

            CloseHandle( snapshot );

            return ret == 0 ? handle{ OpenProcess( PROCESS_ALL_ACCESS, FALSE, ret ) } : nullptr;
        }

        static auto simple_assert( std::invocable auto &&fx ) {
            if ( auto r = fx( ); r )
                return r;

            return false;
        }
    };

    detail::handle m_proc_handle;

public:
    loader( ) = default;

    explicit loader( const std::wstring_view target )
        : m_proc_handle{ detail::get_proc( target ) } {}

    virtual ~loader( ) = default;

    bool inject( std::string_view ) const;

    // loadlib-related functionality
};
