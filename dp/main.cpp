
#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"
#include "Database.h"
#include "Observer.h"

int main() {
    Database::get().open("library.db");
    
    {
        LibrarySystem system;
        
        EmailNotifier emailNotifier(&system.getNotifier());
        SMSNotifier smsNotifier(&system.getNotifier());
        
        CLI cli(system);
        cli.run();
    }
    
    Database::get().close();
    std::cout << "program shut." << std::endl;
    return 0;
}