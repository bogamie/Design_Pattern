
#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"

int main() {
    LibrarySystem system;
    system.seed();
    CLI cli(system);
    cli.run();
    std::cout << "program shut." << std::endl;
    return 0;
}