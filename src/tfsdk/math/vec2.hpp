#pragma once

#include <cfloat>
#include <cmath>

namespace sdk {
    class vec2_t {
    public:
        float x, y;

        vec2_t( ) { x = y = 0.0f; }

        vec2_t( const float X, const float Y ) {
            x = X;
            y = Y;
        }

        explicit vec2_t( const float *v ) {
            x = v[ 0 ];
            y = v[ 1 ];
        }

        vec2_t( const vec2_t &v ) {
            x = v.x;
            y = v.y;
        }

        vec2_t &operator=( const vec2_t &v ) = default;

        float &operator[]( int i ) { return ( ( float * ) this )[ i ]; }

        float operator[]( int i ) const { return ( ( float * ) this )[ i ]; }

        vec2_t &operator+=( const vec2_t &v ) {
            x += v.x;
            y += v.y;
            return *this;
        }

        vec2_t &operator-=( const vec2_t &v ) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2_t &operator*=( const vec2_t &v ) {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        vec2_t &operator/=( const vec2_t &v ) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        vec2_t &operator+=( const float v ) {
            x += v;
            y += v;
            return *this;
        }

        vec2_t &operator-=( const float v ) {
            x -= v;
            y -= v;
            return *this;
        }

        vec2_t &operator*=( const float v ) {
            x *= v;
            y *= v;
            return *this;
        }

        vec2_t &operator/=( const float v ) {
            x /= v;
            y /= v;
            return *this;
        }

        vec2_t operator+( const vec2_t &v ) const { return { x + v.x, y + v.y }; }

        vec2_t operator-( const vec2_t &v ) const { return { x - v.x, y - v.y }; }

        vec2_t operator*( const vec2_t &v ) const { return { x * v.x, y * v.y }; }

        vec2_t operator/( const vec2_t &v ) const { return { x / v.x, y / v.y }; }

        vec2_t operator+( const float v ) const { return { x + v, y + v }; }

        vec2_t operator-( const float v ) const { return { x - v, y - v }; }

        vec2_t operator*( const float v ) const { return { x * v, y * v }; }

        vec2_t operator/( const float v ) const { return { x / v, y / v }; }

        void set( const float X = 0.0f, const float Y = 0.0f ) {
            x = X;
            y = Y;
        }

        [[nodiscard]] float length( ) const { return sqrtf( x * x + y * y ); }

        [[nodiscard]] float length_sqr( ) const { return ( x * x + y * y ); }

        [[nodiscard]] float dist_to( const vec2_t &v ) const { return ( *this - v ).length( ); }

        [[nodiscard]] float dist_to_sqr( const vec2_t &v ) const {
            return ( *this - v ).length_sqr( );
        }

        [[nodiscard]] float dot( const vec2_t &v ) const { return ( x * v.x + y * v.y ); }

        [[nodiscard]] bool is_zero( ) const {
            return ( x > -FLT_EPSILON && x < FLT_EPSILON && y > -FLT_EPSILON && y < FLT_EPSILON );
        }

        explicit operator bool( ) const noexcept { return !is_zero( ); }
    };
} // namespace sdk
