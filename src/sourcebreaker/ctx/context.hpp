#pragma once
#include <sourcebreaker/thirdparty.hpp>

namespace sbr {
    struct ctx_t {
        HMODULE m_dll;

        ctx_t( ) = default;

        // the perfect ctor. is an empty-body one :)
        explicit ctx_t( const HMODULE inst ) : m_dll( inst ) {}

        // main loop.
        auto install( ) const -> void;
    };
}
