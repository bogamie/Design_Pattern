// 새 CLI 진입점
#include <iostream>
#include "CLI.h"
#include "LibrarySystem.h"

int main() {
    LibrarySystem system;
    system.seed();
    CLI cli(system);
    cli.run();
    std::cout << "프로그램을 종료합니다." << std::endl;
    return 0;
}