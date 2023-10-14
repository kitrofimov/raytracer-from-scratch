#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "Argparser.hpp"

Argparser::Argparser(int argc, char** argv, std::vector<std::string> boolean_args,
                     std::unordered_map<std::string, std::string> string_args)
{
    // Convert argument vector to contiguous string
    std::string args;
    for (int i = 1; i < argc; i++)
        args += (std::string(argv[i]) + " ");

    // Check for --help flag
    if (this->does_argument_exist(args, "--help"))
    {
        this->help = true;
        return;
    }
    this->help = false;

    // Initialize parsed maps
    this->parsed_string = string_args;
    for (auto& arg : boolean_args)
        this->parsed_boolean[arg] = false;

    // Parse arguments
    for (auto& arg : boolean_args)
    {
        bool temp = this->does_argument_exist(args, arg);
        this->parsed_boolean[arg] = temp;
    }

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
    int begin = argv.find(arg);
    if (begin == std::string::npos)
        return std::string();
    begin = begin + arg.length() + 1;
    int end = argv.find(" ", begin);
    return argv.substr(begin, end - begin);
}
