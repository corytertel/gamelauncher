#include "cmdarg.hpp"

//Constructor
CmdArg::CmdArg(std::string_view flag)
: flag{ flag }, args{}, arg_function{} {}

//Destructor
CmdArg::~CmdArg() = default;

//Copy Constructor
CmdArg::CmdArg(const CmdArg& other) = default;

//Move Constructor
CmdArg::CmdArg(CmdArg&& other) noexcept = default;

//Copy Assignment Operator
auto CmdArg::operator=(const CmdArg& other) -> CmdArg& = default;

//Move Assignment Operator
auto CmdArg::operator=(CmdArg&& other) noexcept -> CmdArg& = default;

//Getter for flag
auto CmdArg::get_flag() const -> const std::string_view& {
    return this->flag;
}

//Getter for args
auto CmdArg::get_args() const -> const std::vector<std::string_view>& {
    return this->args;
}

//Add arg
void CmdArg::add_arg(std::string_view new_arg) {
    args.emplace_back(new_arg);
}

//Exec the function associated with the passed in flag
void CmdArg::exec() const {
    arg_function(*this);
}