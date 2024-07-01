#include <iostream>
#include "argument.h"
#include "parser.h"

using namespace Calle;

int main(std::int32_t argc, char* argv[])
{
    Parser parser {
        "test app",
        { Command { "yes", { Option { "--plum", "-l", Optionality::optional, 1 } }, 1 }, Command { "no", {} } },
        { Option { "--plop", "-p", Optionality::required, 1 }, Option { "--hi", "-p", Optionality::optional, 0 } }
    };

    parser.parse_args(argc, argv);

    auto p = parser.global_option("-p");

    if (p.has_value()) { std::cout << p[0].to_float<float>() << std::endl; }

    std::cout << parser["yes"]["-l"][0].to_int<std::uint16_t>() << std::endl;
    return 0;
}