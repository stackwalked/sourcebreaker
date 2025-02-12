#pragma once

#include <cmath>

namespace sdk {
    using matrix3x4 = float[ 3 ][ 4 ];

    constexpr double PI  = 3.1415926535897932384;
    constexpr double TAU = PI * 2;

    __forceinline constexpr float deg_to_rad( const float value ) {
        return value * static_cast< float >( static_cast< double >( PI ) / 180 );
    }

    __forceinline constexpr float rad_to_deg( const float value ) {
        return value * static_cast< float >( 180. / static_cast< double >( PI ) );
    }

    inline void sine_cosine( const float &radians, float &sine, float &cosine ) {
        sine   = sin( radians );
        cosine = cos( radians );
    }
} // namespace sdk

#include "vec2.hpp"
#include "vec3.hpp"

namespace sdk {
    using QAngle = vec3_t;
    using Vector = vec3_t;
} // namespace sdk
