#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "steam_library.h"
#include "log.h"

struct Arg {
    Arg(std::string flag) : flag{ flag }, args{}, arg_function{} {}
    std::string flag;
    std::vector<std::string> args;
    void (*arg_function)(const Arg&);
    void exec() { arg_function(*this); }
};

//Arg Functions follow void(*)(const Arg&)
void change_path(const Arg& arg);

int main(const int argc, const char** argv) {
    //Default run
    if (argc == 1) {
        //Will try to load path from gamelauncher.conf first
        //If unable to load path/settings from gamelauncher.conf, 
        //then get the default path and ask the user if that's the path.
        //If not, then ask them to enter a path manually.
        std::string path{};

        std::ifstream conf_file{ "gamelauncher.conf" };
        if (conf_file.is_open()) {
            Log::info("Loading path from file\n");
            std::string line{};
            getline(conf_file, line);
            getline(conf_file, line);
            getline(conf_file, line);
            getline(conf_file, line);
            path = line;
            conf_file.close();
        } 
        else {
            Log::warning("No conf file found\n");
            Log::info("Creating conf file\n");

            //Get $USER
            char name_buffer[256]{};
            FILE *file{ popen("whoami", "r") };
            if (!file) { Log::error("Could not read 'whoami' for $USER"); return 1; }
            fgets(name_buffer, sizeof(name_buffer), file);
            pclose(file);
            std::string user_name{ name_buffer };
            user_name.pop_back();

            //Create default path
            path += "/home/";
            path += user_name;
            path += "/.local/share/Steam/steamapps/";

            //Prompt user to specify correct path
            Log::standard("Is " + path + " the correct \'steamapps\' path?\n");
            std::string input{};
            while (input != "y" && input != "Y" && input != "n" && input != "N") {
                Log::standard("(y/n) : ");
                std::cin >> input;
            }
            if (input == "n" || input == "N") {
                Log::standard("Path to \'steamapps\' folder : ");
                std::cin >> path;
            } 

            //Create the missing or restricted conf_file
            std::ofstream new_conf_file{ "gamelauncher.conf" };
            new_conf_file << "# gamelauncher conf file. Do not modify.\n\n";
            new_conf_file << "# path to steamapps\n";
            new_conf_file << path << std::endl;
            new_conf_file.close();
        }

        //Get user's Steam library
        try {
            SteamLibrary steam{ path };
            Log::standard("Steam Library at " + path + "\n");
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

    //FLAGS

    //Populate the args vector with the args from cmdline
    std::vector<Arg> args{};
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            args.push_back(Arg{ std::string{ argv[i] } });
        }
        else {
            args.back().args.push_back(std::string{ argv[i] });
        }
    }

    /*for (const auto& arg : args) {
        Log::debug("Flag: " + arg.flag + "\n");
        for (const auto& arg2 : arg.args) {
            Log::debug("Arg arg: " + arg2 + "\n");
        }
    }*/

    //Assign the function to execute to each arg
    for (const auto& arg : args) {
        if (arg.flag == "--path") {
            change_path(arg);        
        }
        else if (arg.flag == "-p") {
            change_path(arg);
        }
        else {
            Log::error("Invalid argument");
            return 1;
        }
    }

    //Execute each function for each arg
    for (const auto& arg : args) {
        arg.exec();
    }

    return 0;
}

void change_path(const Arg& arg) {
    std::ofstream new_conf_file{ "gamelauncher.conf" };
    new_conf_file << "# gamelauncher conf file. Do not modify.\n\n";
    new_conf_file << "# path to steamapps\n";
    new_conf_file << arg.args[0] << std::endl;
    new_conf_file.close();
    Log::info("Changed path in gamelauncher.conf");
}