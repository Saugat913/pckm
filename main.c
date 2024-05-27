#include <stdio.h>
#include "cli.h"
#include "engine.h"

int main(int argc, char const *argv[])
{

    struct Config config;
    if (parse_arguments(argc, argv, &config) == true)
    {
        run_engine(argv[0],&config);
    }
    return 0;
}
