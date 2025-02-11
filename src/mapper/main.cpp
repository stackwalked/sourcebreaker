#include <iostream>

#include "api/loader.hpp"
#include "ldrs/loadlib.hpp"

int main( int argc, char *argv[ ] ) {
    map::loader< map::variant::LOADLIBRARY > loader{ };

    loader.inject( "" );

    return 0;
}
