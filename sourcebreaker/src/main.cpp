#include "thirdparty.hpp"

auto __stdcall DllMain( HINSTANCE dllinst, unsigned long reason, void* reserved )
  -> unsigned long {
  if ( reason == DLL_PROCESS_ATTACH ) {
    MessageBoxA( 0, "sourcebreaker", "sourcebreaker DllMain", 0 );
  }

  return 1;
}

