#include "thirdparty.hpp"

auto __stdcall DllMain(
        HINSTANCE           dllinst,
        const unsigned long reason,
        void *              reserved
        ) -> unsigned long {
    if ( reason == DLL_PROCESS_ATTACH ) {
        MessageBoxA( nullptr, "sourcebreaker", "sourcebreaker DllMain", 0 );
    }

    return 1;
}
