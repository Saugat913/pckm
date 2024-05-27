#ifndef _PCKM_CONFIG_H_
#define _PCKM_CONFIG_H_

// usage : pckm <command> <options>
// Command:
//   create             Create a new binary/library
//   build              Build the project
//   run                Run the project
//   clean              Clean the whole project build
//   add                Add the external library or library src
//   remove             Remove the external library or library src
//   help               Display help message
//   version            Display the version of program

// Options:
//  --lib.              Used with create command to specify if project is bin or library
//  --release.          Specify release build while building project

typedef enum
{
    CONFIG_CREATE,
    CONFIG_BUILD,
    CONFIG_RUN,
    CONFIG_CLEAN,
    CONFIG_ADD,
    CONFIG_REMOVE,
    CONFIG_HELP,
    CONFIG_VERSION,
    CONFIG_UNKNOWN
} ConfigType;

typedef enum
{
    OPTION_LIB,
    OPTION_RELEASE,
    OPTION_UNKNOWN
} OptionType;

typedef enum
{
    PROJECT_BIN,
    PROJECT_LIB
} ProjectType;

typedef enum
{
    LIB_STATIC,
    LIB_DYNAMIC,
    LIB_BOTH
} LibType;

typedef enum
{
    BUILD_DEBUG,
    BUILD_RELEASE
} BuildType;

struct ConfigCreate
{
    char *project_name;
    ProjectType project_type;
    LibType lib_type;
};

struct ConfigLib
{
    char *library_name;
};

struct Config
{
    ConfigType type;
    union
    {
        struct ConfigCreate config_create;
        struct ConfigLib config_lib;
        BuildType build_type;
    } data;
};

// void display_config(struct Config *config)
// {
//     switch (config->type)
//     {
//     case CONFIG_CREATE:

//         printf("Creating the project type %d named %s\n", config->data.config_create.project_type, config->data.config_create.project_name);
//         break;
//     case CONFIG_BUILD:
//         printf("Building the project in mode %d\n", config->data.build_type);
//         break;
//     case CONFIG_RUN:
//         printf("Running the project\n");
//         break;
//     case CONFIG_CLEAN:
//         printf("Cleaning the project\n");
//         break;
//     case CONFIG_ADD:
//         printf("Adding library %s in the project\n", config->data.config_lib.library_name);
//         break;
//     case CONFIG_REMOVE:
//         printf("Removing library %s from the project\n", config->data.config_lib.library_name);
//         break;
//     case CONFIG_HELP:
//         printf("Help\n");
//         break;
//     case CONFIG_VERSION:
//         printf("Version\n");
//         break;
//     }
// }



#endif