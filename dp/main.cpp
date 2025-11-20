#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"
using namespace std;

int main() {
    LibrarySystem system;
    system.seed();
    CLI cli(system);
    cli.run();
    cout << "프로그램을 종료합니다." << endl;
    return 0;
}