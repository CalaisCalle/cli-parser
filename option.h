#ifndef OPTION_H
#define OPTION_H

#include <deque>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include "argument.h"

enum class Optionality
{
    optional,
    required
};
enum class Argument_type
{
    has_argument,
    no_argument
};

namespace Calle
{
    class Option
    {
      public:
        Option() = delete;
        // Options may have handlers, but don't need to.
        // This could be useful when parsing commands
        //
        Option(const std::string_view long_form,
               const std::string_view short_form,
               Optionality            optionality = Optionality::optional,
               std::size_t            min_args    = 0,
               std::size_t            max_args    = 0);
        Option(const std::string_view long_form,
               Optionality            optionality = Optionality::optional,
               Argument_type          type        = Argument_type::no_argument);

        bool            operator==(std::string_view option) const;
        const Argument& operator[](std::size_t index) const;

        bool                         has_value() const;
        const std::vector<Argument>& arguments() const;
        void                         add_argument(std::string_view arg);
        void                         check();

      private:
        std::string m_long_form {};
        std::string m_short_form {};
        Optionality m_optionality { Optionality::optional };
        std::size_t m_min_args { 0 };
        std::size_t m_max_args { 0 };
        bool        m_has_value { false };

        Argument_type m_arg_type { Argument_type::no_argument };

        std::vector<Argument> m_given_arguments {};

        std::string remove_prefix(std::string_view token) const;
    };
}// namespace Calle

#endif