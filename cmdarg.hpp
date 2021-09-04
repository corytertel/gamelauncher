#pragma once
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string_view>
#include <vector>

struct CmdArg {
    //Constructor
    explicit CmdArg(std::string_view flag);
    
    //Essentials: Destructor, Copy and Move Constructors, and Copy and Move Assignment Operators
    ~CmdArg();
    CmdArg(const CmdArg& other);
    CmdArg(CmdArg&& other) noexcept;
    auto operator=(const CmdArg& other) -> CmdArg&;
    auto operator=(CmdArg&& other) noexcept -> CmdArg&;

    //Getter for flag
    [[nodiscard]]
    auto get_flag() const -> const std::string_view&;

    //Getter for args
    [[nodiscard]]
    auto get_args() const -> const std::vector<std::string_view>&;
    
    //Add arg
    void add_arg(std::string_view new_arg);

    //Exec the function associated with the passed in flag
    void exec() const;
    
private:
    std::string_view flag;
    std::vector<std::string_view> args;
    void (*arg_function)(const CmdArg&);
};