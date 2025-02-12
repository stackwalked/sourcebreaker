#pragma once
#include <string_view>

namespace map {
    enum class variant { NONE, LOADLIBRARY, MANUALMAP, KERNELMAP };

    // abstract "opaque" loader API
    template < variant S > class loader final {
    protected:
        variant m_variant = S;

    public:
        loader( ) = default;

        virtual ~loader( ) = default;

        virtual void inject( std::string_view ) = delete;

        auto variant( ) const -> const variant & { return m_variant; }
    };
} // namespace map
