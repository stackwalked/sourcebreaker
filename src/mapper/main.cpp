#include <iostream>

#include "api/loader.hpp"
#include "ldrs/loadlib.hpp"

int main( const int argc, char *argv[] ) {
    if ( argc != 2 ) {
        std::cerr << "Usage: " << argv[ 0 ] << " <path/to/module>\n";
        return EXIT_FAILURE;
    }

    const map::loader< map::variant::LOADLIBRARY > loader{ L"tf_win64.exe" };

    if ( loader.inject( argv[ 1 ] ) )
        std::cout << "[+] injected successfully\n";

    return 0;
}
