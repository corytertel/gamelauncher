#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "steam_library.h"

int main(int argc, char** argv) {
    SteamLibrary steam{ "/home/cory/.local/share/Steam/steamapps/" };
    std::cout << steam.library_to_string() << std::endl;
    size_t index{};
    std::cin >> index;
    try {
        steam.launch_app(index);
    } catch (std::out_of_range& e) {
        std::cout << "Index is out of range" << std::endl;
    }
    return 0;
}
