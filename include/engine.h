#ifndef _PCKM_ENGINE_H_
#define _PCKM_ENGINE_H_
#include "common/config.h"
#include "cli.h"
#include <stdio.h>

void run_engine(const char *app_name, struct Config *config)
{
    switch (config->type)
    {
    case CONFIG_CREATE:
        
        break;
    case CONFIG_BUILD:
        printf("Building the project in mode %d\n", config->data.build_type);
        break;
    case CONFIG_RUN:
        printf("Running the project\n");
        break;
    case CONFIG_CLEAN:
        printf("Cleaning the project\n");
        break;
    case CONFIG_ADD:
        printf("Adding library %s in the project\n", config->data.config_lib.library_name);
        break;
    case CONFIG_REMOVE:
        printf("Removing library %s from the project\n", config->data.config_lib.library_name);
        break;
    case CONFIG_HELP:
        display_help(app_name);
        break;
    case CONFIG_VERSION:
        printf("pckm (Package Manager) 0.0.1 20240527\n");
        break;
    }
}

#endif