#ifndef _PCKM_UTILS_H_
#define _UTILS_H_


#define MAX_FILEPATH 256

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>



bool make_folder_struct(struct Config *config, struct ConfigCreate create) { 

	char cwd[MAX_FILEPATH];
	char project_path[MAX_FILEPATH];
 	char *_project_name = config->data.config_create.project_name; 

  
	if(getcwd(cwd, sizeof(cwd)) != NULL){

		snprintf(project_path, sizeof(project_path), "%s/%s", cwd, _project_name);

	}

	if(project_path != NULL){

		if(mkdir(project_path, 0755) == 0){
			printf("Project directory is Created, %s\n", _project_name);
		}
	}

	char *sub_directory[] ={
		"include", "src", "build", "lib", "test", "doc",
	};

	char sub_directory_path[MAX_FILEPATH];

	struct stat statbuff;	
	if(stat(project_path, &statbuff) == 0 && S_ISDIR(statbuff.st_mode)){
		for(int i = 0; i < sizeof(sub_directory) / sizeof(sub_directory[0]); i++){
			snprintf(sub_directory_path, sizeof(sub_directory_path), "%s/%s", project_path, sub_directory[i]);
			if(sub_directory_path != NULL){
				if(mkdir(sub_directory_path, 0755) == 0){
					printf("Sub Directory is created, %s\n", sub_directory[i]);


					if(sub_directory[i] == "lib"){
						DIR *dir = opendir(sub_directory_path);
						if(dir == NULL){
							perror("opendir");
							return false;
						}

						char bin_path[MAX_FILEPATH];
						snprintf(bin_path, sizeof(bin_path), "%s/%s", sub_directory_path, "bin");

						if(bin_path != NULL){
							if(mkdir(bin_path, 0755) == 0){
								printf("Directory, bin created\n");
							}
						}
					}


					if(sub_directory[i] == "src"){
						DIR *dir = opendir(sub_directory_path);
						if(dir == NULL){
							perror("opendir");
							return false;
						}

						char filename[MAX_FILEPATH];
						snprintf(filename, sizeof(filename), "%s/%s.c", sub_directory_path, "main");

						FILE *file  = fopen(filename, "w");
						if( file == NULL){
							perror("fopen");
							closedir(dir);
							return false;
						} 

						fprintf(file, "#include <stdio.h>\n\nint main(int argc, char *argv){ \n\n\n\treturn 0; \n}\n");
						fclose(file);
						closedir(dir);
					}
				}
			}
		}
		return true;
	}



	return false;

}

#endif