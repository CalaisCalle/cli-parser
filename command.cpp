#include "command.h"

#include <algorithm>
#include <stdexcept>
#include <sstream>

namespace Calle {

    // ------------------------------------------------------------------------
    // Constructors/Destructors
    //
    Command::Command(
        const std::string_view name,
        std::initializer_list<Option> options,
        std::size_t num_args
    ) : 
        m_command_name      { name },
        m_command_options   { options },
        m_num_arguments     { num_args }
    {
    }


    const Option& Command::operator[](std::string_view option)
    {
        auto itr = std::find_if(
            m_command_options.begin(), m_command_options.end(),
            [&option] (const Option& opt) { return opt == option; }
        );

        if (itr == m_command_options.end())
        {
            std::stringstream ess { };
            ess << "Command [" << m_command_name << "] has no option \""
                << option << "\"";
            throw std::invalid_argument(ess.str());
        }

        return *itr;
    }
} // namespace Calle