#ifndef PARSER_H
#define PARSER_H

#include <initializer_list>
#include <list>

#include "command.h"
#include "option.h"

namespace Calle
{

    class Parser
    {
      public:
        Parser() = delete;
        Parser(std::string_view name, std::initializer_list<Command> commands, std::size_t positional_args = 0);
        Parser(std::string_view name, std::initializer_list<Option> options, std::size_t positional_args = 0);
        Parser(std::string_view               name,
               std::initializer_list<Command> commands,
               std::initializer_list<Option>  options,
               std::size_t                    positional_args = 0);

        void parse_args(std::size_t argc, char* argv[]);

        const Command& operator[](std::string_view cmd) const;
        const Option&  global_option(std::string_view opt) const;

        // Getters/setters
        //
        const std::vector<Argument>& positional_arguments();
        const std::vector<Option>&   global_option();

      private:
        enum class Processing
        {
            option,
            command
        };

        std::string           m_name {};
        std::vector<Command>  m_commands {};
        std::vector<Option>   m_options {};
        std::size_t           m_num_positional_args {};
        std::vector<Argument> m_positional_args {};

        std::list<std::string> tokenise(std::size_t argc, char* argv[]);
    };

}// namespace Calle
#endif