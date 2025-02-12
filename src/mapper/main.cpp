#include <iostream>

#include "api/loader.hpp"
#include "ldrs/loadlib.hpp"

int main( int argc, char *argv[] ) {
    const map::loader< map::variant::LOADLIBRARY > loader{ L"tf_win64.exe" };

    loader.inject( "" );

    return 0;
}
