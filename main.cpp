#include "steam_library.h"
#include "log.h"

int main(int argc, char** argv) {
    //Get $USER
    char name_buffer[256]{};
    FILE *file{ popen("whoami", "r") };
    if (!file) { Log::error("Could not read 'whoami' for $USER"); return 1; }
    fgets(name_buffer, sizeof(name_buffer), file);
    pclose(file);
    std::string user_name{ name_buffer };
    user_name.pop_back();

    //Create default path
    std::string path{ "/home/" };
    path += user_name;
    path += "/.local/share/Steam/steamapps/";

    //Get user's Steam library
    try {
        SteamLibrary steam{ path };
        Log::standard("Steam Library at " + path);
        Log::standard(steam.library_to_string());

        //Asks user for which Steam app they wish to open
        size_t index{};
        std::cin >> index;
        try {
            steam.launch_app(index);
        } catch (std::out_of_range& e) {
            Log::error("Index is out of range");
        }
        return 0;
    } 
    catch (std::runtime_error& e) {
        Log::error(e.what());
        return 1;
    }
}
