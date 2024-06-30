#ifndef COMMAND_H
#define COMMAND_H

#include <deque>
#include <functional>
#include <string>

#include "option.h"
#include "initializer_list"

namespace Calle {

    class Command {
    public:
        Command() = delete;
        Command(
            const std::string_view name,
            std::initializer_list<Option> options = { },
            std::size_t num_args = 0
        );

        operator bool() { return m_has_value; }
        const Option& operator[](std::string_view option);

        void parse_args(const std::deque<std::string>& tokens);

    private:
        std::string m_command_name { };
        bool m_has_value { false };
        
        std::vector<Option>     m_command_options   { };
        std::vector<Argument>   m_command_arguments { };

        std::size_t     m_num_arguments { };
    };

} // namespace Calle

#endif