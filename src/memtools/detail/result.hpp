#pragma once
#include <expected>

namespace mem {
    enum class status_t {
        OK          = 0,
        ERR_UNKNOWN = 1,
    };

    template < typename Ret > using res_t = std::expected< Ret, status_t >;
} // namespace mem
