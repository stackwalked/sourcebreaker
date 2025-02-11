#pragma once

#include <mapper/api/loader.hpp>

template <>
class map::loader< map::variant::LOADLIBRARY >final {
public:
    virtual ~loader( ) = default;

    void inject( std::string_view ) {}
};
