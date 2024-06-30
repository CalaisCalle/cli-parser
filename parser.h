#ifndef PARSER_H
#define PARSER_H

#include <initializer_list>

#include "command.h"
#include "option.h"

namespace Calle {
    class Parser {
    public:
        Parser() = delete;
        Parser(
            std::string_view name,
            std::initializer_list<Command> commands,
            std::size_t positional_args = 0
        );
        Parser(
            std::string_view name,
            std::initializer_list<Option> options,
            std::size_t positional_args = 0
        );
        Parser(
            std::string_view name, 
            std::initializer_list<Command> commands,
            std::initializer_list<Option> options,
            std::size_t positional_args = 0
        );

        void parse_args(std::size_t argc, char* argv[]);

        // Getters/setters
        //
        const std::vector<Argument>& positional_arguments();

    private:
        std::size_t m_num_positional_args { };

        std::vector<Argument> m_positional_args { };
    };

}
#endif