#include "command.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace Calle
{

    // ------------------------------------------------------------------------
    // Constructors/Destructors
    //
    Command::Command(const std::string_view name, std::initializer_list<Option> options, std::size_t num_args) :
            m_command_name { name }, m_command_options { options }, m_num_arguments { num_args }
    {
    }


    // ------------------------------------------------------------------------
    // Public Methods
    //
    const Option& Command::operator[](std::string_view option) const
    {
        auto itr = std::find_if(
            m_command_options.begin(), m_command_options.end(), [&option](const Option& opt) { return opt == option; });

        if (itr == m_command_options.end())
        {
            std::stringstream ess {};
            ess << "Command [" << m_command_name << "] has no option \"" << option << "\"";
            throw std::invalid_argument(ess.str());
        }

        return *itr;
    }


    const Option& Command::operator[](const char* option) const
    {
        return operator[](std::string_view { option });
    }


    bool Command::operator==(std::string_view cmd) const
    {
        return cmd == m_command_name;
    }


    bool Command::has_value()
    {
        return m_has_value;
    }


    void Command::parse_args(const std::vector<std::string>& tokens)
    {
        auto current_option = m_command_options.begin();
        bool found_first_option { false };
        for (auto& token : tokens)
        {
            auto option_itr = std::find(m_command_options.begin(), m_command_options.end(), token);

            if (option_itr != m_command_options.end())
            {
                current_option     = option_itr;
                found_first_option = true;
                continue;
            }

            if (found_first_option)
            {
                current_option->add_argument(token);
                continue;
            }

            m_command_arguments.emplace_back(token);
        }

        m_has_value = true;
    }


    void Command::check()
    {
        if (m_command_arguments.size() > m_num_arguments)
        {
            std::stringstream oss {};
            oss << "Command " << m_command_name << " expects " << m_num_arguments << " args but "
                << m_command_arguments.size() << " were given.";
            throw std::invalid_argument(oss.str());
        }

        for (auto& option : m_command_options)
        {
            try
            {
                option.check();
            }
            catch (const std::exception& e)
            {
                // propagate error
                //
                throw std::invalid_argument("[" + m_command_name + "]: " + e.what());
            }
        }
    }
}// namespace Calle