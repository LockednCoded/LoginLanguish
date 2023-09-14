#include "parse_args.h"
#include <sstream>

std::vector<std::string> parse_args(std::string args)
{
    std::vector<std::string> parsed_args;
    
    //remove [ and ] from argument string
    args = args.substr(1, args.length() - 2);

    //split string by comma
    std::istringstream iss(args);
    std::string arg;

    while (std::getline(iss, arg, ','))
    {
        // remove double quotes from argument
        arg.erase(std::remove(arg.begin(), arg.end(), '\"'), arg.end());

        parsed_args.push_back(arg);
    }

    
    return parsed_args;
}