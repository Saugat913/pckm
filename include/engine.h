#ifndef _PCKM_ENGINE_H_
#define _PCKM_ENGINE_H_
#include "common/config.h"
#include "common/utils.h"
#include "cli.h"
#include <stdio.h>

char *template_folder[] = {"include", "src", "doc"};

char template_file_content[] = "#include<stdio.h>\nint main(int argc, char const *argv[]){\nreturn 0;\n}";

void create_template_folder()
{
    for (size_t i = 0; i < sizeof(template_folder) / sizeof(template_folder[0]); i++)
    {
        create_dir(template_folder[i]);
    }
}

void run_engine(const char *app_name, struct Config *config)
{
    switch (config->type)
    {
    case CONFIG_CREATE:
        create_dir(config->data.config_create.project_name);
        change_dir(config->data.config_create.project_name);
        create_template_folder();
        create_file("src/main.c");
        write_to_file("src/main.c", template_file_content, sizeof(template_file_content) / sizeof(template_file_content[0]) - 1);
        change_dir("..");
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