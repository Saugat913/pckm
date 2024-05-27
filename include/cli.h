#ifndef _PCKM_CLI_H_
#define _PCKM_CLI_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "common/config.h"

struct CommandInfo
{
    char *command_name;
    char *command_description;
};

struct OptionInfo
{
    char *option_name;
    char *option_description;
    ConfigType compatibile_with;
};

const struct CommandInfo commands[] = {
    {"create", "Create a new binary/library"},
    {"build", "Build the project"},
    {"run", "Run the project"},
    {"clean", "Clean the whole project build"},
    {"add", "Add the external library or library src"},
    {"remove", "Remove the external library or library src"},
    {"help", "Display help message"},
    {"version", "Display the version of program"}};

const struct OptionInfo options[] = {
    {"lib", "Used with create command to specify if project is bin or library", CONFIG_CREATE},
    {"release", "Specify release build while building project", CONFIG_BUILD}};

void display_help(const char *app_name)
{
    int padding = 10;
    printf("Usage: %s <command> <options>\n", app_name);
    printf("Command:\n");
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        printf("    ");
        printf("%-*s   %s\n", padding, commands[i].command_name, commands[i].command_description);
    }
    printf("Options:\n");
    for (size_t i = 0; i < sizeof(options) / sizeof(options[0]); i++)
    {
        printf("    ");
        printf("--%-*s   %s\n", padding, options[i].option_name, options[i].option_description);
    }
}

ConfigType match_command(const char *command)
{
    // NOTE: The enum value i.e. numeric value is directly used so dont change position of enum
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        if (strcmp(command, commands[i].command_name) == 0)
            return i;
    }
    return CONFIG_UNKNOWN;
}

bool return_with_error(const char *app_name)
{
    display_help(app_name);
    return false;
}

void set_config_options(struct Config *config, OptionType opt_type)
{
    switch (opt_type)
    {
    case OPTION_LIB:
        config->data.config_create.project_type = PROJECT_LIB;
        break;

    case OPTION_RELEASE:
        config->data.build_type = BUILD_RELEASE;
        break;
    }
}

bool parse_arguments(int argc, char const *argv[], struct Config *config)
{

    config->type = CONFIG_UNKNOWN;
    bool is_value_expected = false;
    char **value_setter = NULL;

    if (argc < 2)
    {
        return return_with_error(argv[0]);
    }

    for (size_t i = 1; i < argc; i++)
    {
        // Check for the options(flag)
        if (argv[i][0] == '-' && argv[i][1] == '-')
        {

            OptionType opt_type = OPTION_UNKNOWN;
            for (size_t j = 0; j < sizeof(options) / sizeof(options[0]); j++)
            {
                if (strcmp(&argv[i][2], options[j].option_name) == 0)
                    opt_type = j;
            }

            if (opt_type == OPTION_UNKNOWN)
            {
                printf("[ERROR] Unknown option %s\n", argv[i]);
                return return_with_error(argv[0]);
            }

            if (config->type != options[opt_type].compatibile_with)
            {
                printf("[ERROR] Option %s is not compatible with command %s \n", argv[i], commands[config->type].command_name);
                return false;
            }

            set_config_options(config, opt_type);
        }
        else
        {
            // If not flag it should be command or the value
            ConfigType command_type = match_command(argv[i]);

            if (is_value_expected == true)
            {

                *value_setter = argv[i];
                is_value_expected = false;
                value_setter = NULL;
                continue;
            }

            if (command_type == CONFIG_UNKNOWN)
            {
                printf("[ERROR] Unexpected command or option  %s \n", argv[i]);
                return return_with_error(argv[0]);
            }

            if (config->type != CONFIG_UNKNOWN)
            {
                printf("[ERROR] Cannot use two command at a time  %s \n", argv[i]);
                return return_with_error(argv[0]);
            }

            switch (command_type)
            {
            case CONFIG_ADD:
                value_setter = &config->data.config_lib.library_name;
                is_value_expected = true;
                break;
            case CONFIG_CREATE:
                value_setter = &config->data.config_create.project_name;
                config->data.config_create.project_type = PROJECT_BIN;
                is_value_expected = true;
                break;
            case CONFIG_REMOVE:
                value_setter = &config->data.config_lib.library_name;
                is_value_expected = true;
                break;
            }
            config->type = command_type;
        }
    }

    if (is_value_expected == true)
    {
        switch (config->type)
        {
        case CONFIG_ADD:
        case CONFIG_REMOVE:
            printf("[ERROR] Library name is required!\n");
            break;
        case CONFIG_CREATE:
            printf("[ERROR] Project name is required!\n");
        }
        return return_with_error(argv[0]);
    }
    return true;
}

#endif