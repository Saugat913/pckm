#ifndef _PCKM_UTILS_H_
#define _PCKM_UTILS_H_

#ifdef _WIN32
#include <WinBase.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <stdio.h>

bool create_dir(char *dir_path)
{
#ifdef _WIN32
    return CreateDirectory(directoryPath, NULL);
#else
    return mkdir(dir_path, 0755) == 0 ? true : false;
#endif
}

void change_dir(char *path)
{
    chdir(path);
}

bool create_file(char *file_name)
{
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
        return false;

    fclose(fp);
}

bool write_to_file(char *file_name, char *content, size_t n)
{
    bool status = true;
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
        return false;

    if (fwrite(content, sizeof(char), n, fp) != n)
        status = false;
    fclose(fp);

    return status;
}

#endif