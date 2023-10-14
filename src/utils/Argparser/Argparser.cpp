#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "Argparser.hpp"

Argparser::Argparser(int argc, char** argv, std::unordered_map<std::string, bool> boolean_args,
                     std::unordered_map<std::string, std::string> string_args)
{
    std::string args;
    for (int i = 1; i < argc; i++)
        args += (std::string(argv[i]) + " ");

    if (this->does_argument_exist(args, "help"))
    {
        this->help = true;
        return;
    }
    this->help = false;

    this->parsed_boolean = boolean_args;
    this->parsed_string = string_args;

    for (auto& pair : boolean_args)
        this->parsed_boolean[pair.first] = this->does_argument_exist(args, pair.first);

    for (auto& pair : string_args)
    {
        std::string option = this->get_argument_option(args, pair.first);
        if (option.length() != 0)
            this->parsed_string[pair.first] = option;
    }
}

bool Argparser::does_argument_exist(std::string argv, std::string arg)
{
    return argv.find(arg) != std::string::npos;
}

std::string Argparser::get_argument_option(std::string argv, std::string arg)
{
    int begin = argv.find(arg) + arg.length() + 1;
    int end = argv.find(" ", begin);
    return argv.substr(begin, end);
}
