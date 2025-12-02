
#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"
#include "Database.h"
#include "Observer.h"

int main() {
    Database::get().open("library.db");
    
    {
        LibrarySystem system;
        
        // 구체 Observer가 구체 Subject 참조
        EmailNotifier emailNotifier(&system.getNotifier());
        SMSNotifier smsNotifier(&system.getNotifier());
        
        system.seed();
        CLI cli(system);
        cli.run();
    }
    
    Database::get().close();
    std::cout << "program shut." << std::endl;
    return 0;
}