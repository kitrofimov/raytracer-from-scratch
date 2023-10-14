#pragma once
#include <unordered_map>
#include <string>
#include <vector>

// Parses arguments in form of `bool-arg string-arg=option`
class Argparser
{
public:
    // `argv` - raw argument string, `boolean_args` - a map of boolean_arg:default_value,
    // `string_args` - a map of string_arg:default_value, `help_message` - help message
    Argparser(int argc, char** argv, std::vector<std::string> boolean_args,
              std::unordered_map<std::string, std::string> string_args);

    std::unordered_map<std::string, bool> parsed_boolean;
    std::unordered_map<std::string, std::string> parsed_string;
    bool help;

    Argparser(const Argparser&) = delete;
    Argparser& operator=(const Argparser&) = delete;

private:
    bool does_argument_exist(std::string argv, std::string arg);
    std::string get_argument_option(std::string argv, std::string arg);
};
