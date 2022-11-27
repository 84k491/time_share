#pragma once

#include <optional>

class ArgumentParser
{
    static constexpr unsigned defalut_port = 55555;

public:
    ArgumentParser(int argc, char ** argv);
    std::optional<unsigned> port() const { return m_port; }

private:
    void print_usage() const;

private:
    std::optional<unsigned> m_port;
    const std::pair<unsigned, unsigned> m_port_interval = {1, 65535};
};
