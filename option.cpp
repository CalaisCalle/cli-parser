#include "option.h"
#include <iostream>
#include <sstream>

namespace Calle
{

    // ------------------------------------------------------------------------
    // Constructors/Destructors
    //
    Option::Option(const std::string_view long_form,
                   const std::string_view short_form,
                   Optionality            optionality,
                   std::size_t            min_args,
                   std::size_t            max_args) :
            m_long_form { remove_prefix(long_form) },
            m_short_form { remove_prefix(short_form) },
            m_optionality { optionality },
            m_min_args { min_args },
            m_max_args { (min_args > 0 && max_args == 0 ? 1 : max_args) }
    {
    }


    // ------------------------------------------------------------------------
    // Public Methods
    //
    bool Option::operator==(std::string_view option) const
    {
        std::string no_prefix = remove_prefix(option);
        return no_prefix == m_long_form || no_prefix == m_short_form;
    }


    const Argument& Option::operator[](std::size_t index) const
    {
        return m_given_arguments[index];
    }


    bool Option::has_value() const
    {
        return m_has_value;
    }


    const std::vector<Argument>& Option::arguments() const
    {
        return m_given_arguments;
    }


    void Option::add_argument(std::string_view arg)
    {
        m_given_arguments.emplace_back(arg);
        m_has_value = true;
    }


    void Option::check()
    {
        std::size_t num_args { m_given_arguments.size() };

        if (num_args < m_min_args || num_args > m_max_args)
        {
            std::stringstream oss {};
            oss << "Option [--" << m_long_form << "] expects between " << m_min_args << " & " << m_max_args
                << " args, but " << num_args << " were given";
            throw std::invalid_argument(oss.str());
        }

        if (m_optionality == Optionality::required && !m_has_value)
        {
            std::stringstream oss {};
            oss << "Required option [--" << m_long_form << "] was not given";
            throw std::invalid_argument(oss.str());
        }
    }


    // ------------------------------------------------------------------------
    // Private Methods
    //
    std::string Option::remove_prefix(std::string_view token) const
    {
        std::string out { token };

        for (std::size_t i { 0 }; i < 2; ++i)
        {
            if (*(out.begin()) == '-') out.erase(out.begin());
        }

        return out;
    }

}// namespace Calle