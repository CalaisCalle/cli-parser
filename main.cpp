#include "argument.h"
#include "parser.h"
#include <iostream>

using namespace Calle;

int main(std::int32_t argc, char* argv[])
{
    Parser parser {
        "test app",
        {
            Option { "--plop", "-p" }
        }
    };

    parser.parse_args(argc, argv);
    return 0;
}