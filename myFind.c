/*
Implemented a C program that replicates a small subset of the functionality of the 'find' system utility. The output is identifical to executing 'find . -type f'
Finds all files in currennt directory and prints them one line at a time to standard output.
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>

void find(const char* path)
{
	DIR *directory = opendir(path);
	struct dirent* element = NULL;
	//if directory is null then just return without doing anything
	if(!directory)
	   return;
	
	while((element = readdir(directory)) != NULL){
		//if the file is a regular file then just print the file name
		if(element->d_type == DT_REG)
			printf("%s/%s\n", path,  element->d_name);
		//if the "file" is a folder than recursively loop, but inside that folder / directory
		if(element->d_type == DT_DIR){
			if(strcmp(element->d_name, ".") && strcmp(element->d_name, "..")){
				char buffer[1000];
				//add the current folder into the path name and print it out
				sprintf(buffer, "%s/%s", path, element->d_name);
				find(buffer);
			}
		}
	}
}

int main(){
	find("."); //since current directory, use .
	return 0;
}

