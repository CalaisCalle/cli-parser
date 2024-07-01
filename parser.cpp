#include "parser.h"
#include <iostream>
#include <stdexcept>

namespace Calle
{

    Parser::Parser(std::string_view name, std::initializer_list<Command> commands, std::size_t positional_args) :
            m_name { name }, m_commands { commands }, m_num_positional_args { positional_args }
    {
    }


    Parser::Parser(std::string_view name, std::initializer_list<Option> options, std::size_t positional_args) :
            m_name { name }, m_options { options }, m_num_positional_args { positional_args }
    {
    }


    Parser::Parser(std::string_view               name,
                   std::initializer_list<Command> commands,
                   std::initializer_list<Option>  options,
                   std::size_t                    positional_args) :
            m_name { name }, m_commands { commands }, m_options { options }, m_num_positional_args { positional_args }
    {
    }


    void Parser::parse_args(std::size_t argc, char* argv[])
    {
        // for each command/option,
        // take up to num_args values from queue
        //
        std::list<std::string> tokens = tokenise(argc, argv);

        Processing               process { Processing::option };
        auto                     current_option  = m_options.begin();
        auto                     current_command = m_commands.begin();
        std::vector<std::string> collected_tokens {};

        for (auto& token : tokens)
        {
            auto option_itr  = std::find(m_options.begin(), m_options.end(), token);
            auto command_itr = std::find(m_commands.begin(), m_commands.end(), token);

            if (option_itr != m_options.end() || command_itr != m_commands.end())
            {
                if (process == Processing::command)
                {
                    current_command->parse_args(collected_tokens);
                    collected_tokens.clear();
                }

                if (option_itr != m_options.end())
                {
                    current_option = option_itr;
                    process        = Processing::option;
                }

                if (command_itr != m_commands.end())
                {
                    current_command = command_itr;
                    process         = Processing::command;
                }

                continue;
            }

            switch (process)
            {
            case Processing::option:
                current_option->add_argument(token);
                break;
            case Processing::command:
                collected_tokens.emplace_back(token);
                break;
            }
        }


        if (process == Processing::command && collected_tokens.size() > 0)
        {
            current_command->parse_args(collected_tokens);
        }

        for (auto& option : m_options)
            option.check();
        for (auto& command : m_commands)
            command.check();
    }


    const Command& Parser::operator[](std::string_view cmd) const
    {
        auto itr = std::find(m_commands.begin(), m_commands.end(), cmd);

        if (itr == m_commands.end())
        {
            throw std::invalid_argument("Parser has no command name [" + std::string { cmd } + "]");
        }

        return *itr;
    }


    const std::vector<Argument>& Parser::positional_arguments()
    {
        return m_positional_args;
    }


    const Option& Parser::global_option(std::string_view opt) const
    {
        auto itr = std::find(m_options.begin(), m_options.end(), opt);

        if (itr == m_options.end())
        {
            throw std::invalid_argument("Parser has no option [" + std::string { opt } + "]");
        }

        return *itr;
    }


    // ------------------------------------------------------------------------
    // Private Parser methods
    //
    std::list<std::string> Parser::tokenise(std::size_t argc, char* argv[])
    {
        std::list<std::string> output_tokens {};

        for (std::size_t i { 1 }; i < argc; ++i)
        {
            output_tokens.emplace_back(argv[i]);
        }

        return output_tokens;
    }

}// namespace Calle