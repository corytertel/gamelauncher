#pragma once
#include <string>
#include <vector>

template<typename T>
concept App = requires(T a) {
    {a.name} -> std::convertible_to<std::string>;
    {a.launch()} -> std::convertible_to<bool>;
};

template <App T>
struct Library {
    //Constructor
    Library(std::string lab_title, std::string path)
    : lib_title{ lab_title },
    path{ path },
    apps{} {}

    //Destructor
    virtual ~Library() = default;
    
protected:
    const std::string lib_title;
    const std::string path; 
    std::vector<T> apps;

    //Required Functions
    virtual bool get_apps_from_path() = 0;
};
