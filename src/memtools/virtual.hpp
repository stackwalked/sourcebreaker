#pragma once

#include "address.hpp"

namespace mem {
    // returns T (address_t) pointer to function at index idx of vtable
    template < typename T = address_t >
    [[nodiscard]] auto vfunc(
            const address_t addr,
            std::size_t     idx
            ) -> T {
        return reinterpret_cast< T >( addr.to< T * >( )[ idx ] );
    }
}
