#ifndef COMMAND_H
#define COMMAND_H

#include <deque>
#include <functional>
#include <string>


#include "initializer_list"
#include "option.h"

namespace Calle
{

    class Command
    {
      public:
        Command() = delete;
        Command(const std::string_view name, std::initializer_list<Option> options = {}, std::size_t num_args = 0);

        const Option& operator[](std::string_view option) const;
        // Necessary to disambiguify the operator for the compiler
        // This avoid template stuff that I REALLY don't want to get into
        //
        const Option& operator[](const char* option) const;

        bool operator==(std::string_view cmd) const;

        bool has_value();
        void parse_args(const std::vector<std::string>& tokens);
        void check();

        std::string m_command_name {};

      private:
        bool m_has_value { false };

        std::vector<Option>   m_command_options {};
        std::vector<Argument> m_command_arguments {};

        std::size_t m_num_arguments { 0 };
    };

}// namespace Calle

#endif