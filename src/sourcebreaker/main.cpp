#include "thirdparty.hpp"
#include "ctx/context.hpp"

auto __stdcall DllMain(
        // ReSharper disable once CppParameterMayBeConst
        HINSTANCE           instance,
        const unsigned long reason,
        void *              reserved
        ) -> unsigned long {

    if ( instance ) // null w/ some manual mappers
        DisableThreadLibraryCalls( instance );

    std::thread(
            [&] {
                const sbr::ctx_t ctx{ instance };
                ctx.install( );
            }
            ).detach( );

    return 1;
}
