#include "argument.h"

namespace Calle
{
    Argument::Argument(std::string_view arg_value) : m_value { arg_value }
    { }

    
    const std::string& Argument::value() const
    {
        return m_value;
    }
} // namespace Calle