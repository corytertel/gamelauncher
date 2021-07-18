#include "steam_library.h"

//SteamApp Required Launch Method
bool SteamApp::launch() const {
    std::string exec = "steam steam://rungameid/" + this->id;
    system(exec.c_str());
    return true;
}

//Constructor
SteamLibrary::SteamLibrary(std::string path)
: Library<SteamApp>{ "Steam", path } {
    //Get apps at the current path
    if (!get_apps_from_path()) { 
        throw std::runtime_error{ "Directory either does not exist or is not a steamapps directory" }; 
    }

    //Sort all the apps alphabetically through bubble sort
    //No need for a fancy sorting algorithm
    sort(apps.begin(), apps.end(), alphabetical_cmp);
}

//Alphabetical comparator function
bool SteamLibrary::alphabetical_cmp(const SteamApp& a, const SteamApp& b) {
    return a.name < b.name;
}

//Destructor
SteamLibrary::~SteamLibrary() {
    /*for (auto app : apps) {
        std::cout << "Deleting app: " << app->name << std::endl;
        delete app;
    }*/
}

//Interface Methods
bool SteamLibrary::get_apps_from_path() {
    if (!std::filesystem::is_directory(path)) { return false; }

    //Loop through all files in the steamapps path
    //For the appmanifest files, go into the file and retrieve the ID and Name
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        //Filters out non-appmanifest files
        if (entry.is_directory()) { continue; }
        auto file_path = entry.path();
        if (file_path.filename().string().substr(0, 11) != "appmanifest") {
            continue;
        }

        //ID and Name retrieval from appmanifest files
        std::ifstream file{ file_path.string() };
        std::string line{};
        SteamApp app{};
        if (file.is_open()) {
            //Skip first two lines, then read "appid"
            //Then skip another line, then read "name", and quit
            getline(file, line);
            getline(file, line);
            getline(file, line);
            //Get app id from "appid" line
            line = line.substr(11);
            for (size_t i = 0; i < line.length(); i++) {
                std::string c = &line[i];
                if (c == "\"") {
                    app.id = line.substr(0, i);
                    break;
                }
            } 
            getline(file, line);
            getline(file, line);
            //Get app name from "name" line
            line = line.substr(10);
            for (size_t i = 0; i < line.length(); i++) {
                std::string c = &line[i];
                if (c == "\"") {
                    app.name = line.substr(0, i);
                    break;
                }
            }
        }

        apps.push_back(app); 
    }

    if (apps.size() == 0) { return false; }
    else { return true; }
}

//Methods
void SteamLibrary::launch_app(size_t index) const {
    if (index >= apps.size()) { throw std::out_of_range{ "Requested index is out of range" }; }
    apps[index].launch();
}

std::string SteamLibrary::library_to_string() const {
    std::string list{};
    for (size_t i = 0; i < apps.size(); i++) {
        list += std::to_string(i) + ".\t" + apps[i].name + "\n";
    }
    return list;
}