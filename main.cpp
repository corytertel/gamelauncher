#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <span>
#include <string_view>
#include "steam_library.hpp"
#include "log.hpp"
#include "cmdarg.hpp"

//Arg Functions follow void(*)(const Arg&)
void change_path(const CmdArg& arg);

auto main(int argc, char** argv) -> int {
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
            if (!file) { 
                Log::error("Could not read 'whoami' for $USER\nError getting file.");
                return 1; 
            }
            if (fgets(name_buffer, sizeof(name_buffer), file) == nullptr) {
                Log::error("Count not read 'whoami' for $USER\nError reading file.");
                return 1;
            }
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

    //Helper for safer c-array access
    std::span<char*> args{ argv, size_t(argc) };
    //Container for all flags and their arguments
    std::vector<CmdArg> flags{};

    //Check to see if the first flag is valid
    if (args[1][0] != '-') {
        Log::error("Invalid flag.");
        return 1;
    }

    //Populate the args vector with the args from cmdline
    //Add all flags and their arguments to the flags vector
    for (size_t i = 1; i < args.size(); i++) {
        if (args[i][0] == '-') {
            flags.push_back(CmdArg{ std::string_view{ args[i] } });
        }
        else {
            flags.back().add_arg(std::string_view{ args[i] });
        }
    }

    // DEBUG: print out flags and their arguments
    for (const auto& flag : flags) {
        Log::debug("Flag: " + std::string{ flag.get_flag() } + "\n");
        for (auto arg : flag.get_args()) {
            Log::debug("Arg: " + std::string{ arg } + "\n");
        }
    }

    //Assign the function to execute to each arg
    for (const auto& arg : flags) {
        if (arg.get_flag() == "--path") {
            change_path(arg);        
        }
        else if (arg.get_flag() == "-p") {
            change_path(arg);
        }
        else {
            Log::error("Invalid argument");
            return 1;
        }
    }

    //Reorder flags in terms of priority

    //Execute each function for each arg
    for (const auto& flag : flags) {
        flag.exec();
    }

    return 0;
}

void change_path(const CmdArg& arg) {
    std::ofstream new_conf_file{ "gamelauncher.conf" };
    new_conf_file << "# gamelauncher conf file. Do not modify.\n\n";
    new_conf_file << "# path to steamapps\n";
    new_conf_file << arg.get_args()[0] << std::endl;
    new_conf_file.close();
    Log::info("Changed path in gamelauncher.conf");
}