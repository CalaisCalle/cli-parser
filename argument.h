#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <cstdint>
#include <string>

namespace Calle
{

    class Argument
    {
      public:
        Argument() = delete;
        Argument(std::string_view arg_value);

        const std::string& value() const;

        template<typename T> T to_float() const;
        template<typename T> T to_int() const;

      private:
        std::string m_value {};
    };


    template<typename T> T Argument::to_float() const
    {
        return static_cast<T>(std::stof(m_value));
    }


    template<typename T> T Argument::to_int() const
    {
        return static_cast<T>(std::stoi(m_value));
    }
}// namespace Calle

#endif