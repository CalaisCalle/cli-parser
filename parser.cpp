#include "parser.h"

namespace Calle {

    void Parser::parse_args(std::size_t argc, char* argv[])
    {
        // for each command/option,
        // take up to num_args values from queue
        //

        // Everything else: get parsed as an argument to the parser itself
        //
    }


    const std::vector<Argument>& Parser::positional_arguments()
    {
        return m_positional_args;
    }

    
} // namespace Calle