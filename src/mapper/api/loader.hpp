#pragma once
#include <string_view>

namespace map {
    enum class variant {
        NONE,
        LOADLIBRARY
    };;

    // abstract "opaque" loader API
    template < variant S >
    class loader< S > final {
    protected:
        variant m_variant = S;

    public:
        loader( ) = default;

        virtual ~loader( ) = default;

        virtual void inject( std::string_view ) = delete;
    };
}
