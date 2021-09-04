#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "library.hpp"
#include "log.hpp"

struct SteamApp {
    SteamApp()
    : name{}, id{} {}

    ~SteamApp() = default;
    
    bool launch() const;

    std::string name;
    std::string id;
};

struct SteamLibrary : Library<SteamApp> {
    //Constructor
    SteamLibrary(std::string path);

    //Destructor
    ~SteamLibrary();

    //Methods
    void launch_app(size_t index) const;
    std::string library_to_string() const;

private:
    //Helper methods
    static bool alphabetical_cmp(const SteamApp& a, const SteamApp& b);

    //Interface Required Methods
    bool get_apps_from_path() override;
};
