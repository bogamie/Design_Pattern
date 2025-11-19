
#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"
#include "Database.h"

int main() {
    Database::get().open("library.db");
    LibrarySystem system;
    system.seed();
    CLI cli(system);
    cli.run();
    std::cout << "program shut." << std::endl;
    return 0;
}