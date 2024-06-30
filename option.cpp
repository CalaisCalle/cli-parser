#include "option.h"

namespace Calle {

    Option::Option(
        const std::string_view long_form,
        const std::string_view short_form,
        Optionality optionality,    
        std::size_t min_args,
        std::size_t max_args
    ) : 
        m_long_form         { long_form },
        m_short_form        { short_form },
        m_min_args          { min_args },
        m_max_args          { max_args }
    {
    }
         

    bool Option::operator==(std::string_view option) const
    {
        return option == m_long_form || option == m_short_form;
    }


    void Option::add_argument(std::string_view arg)
    {
        m_given_arguments.emplace_back(arg);
    }


    void Option::check()
    {
        std::size_t num_args { m_given_arguments.size() };

    }
} // namespace Calle