#include "argument_parser.h"

#include <charconv>
#include <iostream>
#include <string_view>

ArgumentParser::ArgumentParser(int argc, char** argv)
{
    if (argc != 2) {
        print_usage();
        return;
    }

    std::string_view s = argv[1];

    unsigned value;
    if (std::from_chars(s.begin(), s.end(), value).ec != std::errc()) {
        print_usage();
        return;
    }

    if (value < m_port_interval.first || value > m_port_interval.second) {
        print_usage();
        return;
    }

    m_port = value;
}

void ArgumentParser::print_usage() const
{
    std::cout << "Usage: program [PORT]" << std::endl;
    std::cout << "  Port number must be in interval from " << m_port_interval.first << " to " << m_port_interval.second << std::endl;
}
