/*
Implementing the same scan as the bash. Takes in two arguments, extension and number of files to list.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

using namespace std;

//create a struct called fileinfo that contains two pieces of information: filename and filesize
typedef struct 
{
	char * fileName;
	int fileSize;
}fileInfo;

//compare funtion
bool compSize(const fileInfo &a, const fileInfo &b)
{
	if(a.fileSize > b.fileSize) return true;
	if(a.fileSize == b.fileSize)
	{
	       	return a.fileName < b.fileName;
	}
	return false;
}

int main( int argc, char ** argv) 
{
     if(argc <=2)
     {
	    printf("Not enough arguments, please try again");
	    exit(-1);
    }else if(argc>3)
    {
	    printf("Too many arguments, please try again");
	    exit(-1);
    }
    //Have the correct amount of arguments at this point
    string suffix = argv[1];
    int num = stoi(argv[2]);
   

    // open 'find...'
    FILE * fp = popen( "find . -type f", "r");
    if( fp == NULL)
    {
        perror("popen failed:");
        exit(-1);
    }
    // read in all filenames
    char buff[MAX_FNAME_SIZE];
    int nFiles = 0;
    struct stat st;
    fileInfo files[MAX_FILES];

    while(fgets(buff,MAX_FNAME_SIZE,fp))
    {
        int len = strlen(buff) - 1;
        string myName = strndup(buff,len);
	
        //remaining string length is subtracted
	int remstringlen = myName.size() - suffix.size();

	string mySuffix = myName.substr(remstringlen, suffix.size());

	int number;

	if((number = mySuffix.compare(suffix) !=0))
	{
		continue;
	}
	files[nFiles].fileName = strndup(buff,len);

	if(0 != stat(myName.c_str(),&st))
	{
		perror("stat struct has failed");
		exit(-1);
	}
	//st.st_size returns size of files, storing them into our array of structs
	files[nFiles].fileSize = st.st_size;
	nFiles++;
    }
    fclose(fp);
    //call our sort function, and so our array of structs, files, will now be sorted numerically
    sort(files, nFiles + files, compSize);

    if(nFiles > num){
	    nFiles = num;
    }

    long long totalSize =0;
    //print files
    for(int i =0; i<nFiles;i++){
	    //printf(files[i].fileName + " " + files[i].fileSize);
	    //printf(files[i].fileName);
	    //printf(" ");
	    //printf(files[i].fileSize); errors?
	    cout<<files[i].fileName<<" "<<files[i].fileSize<<endl;
	    totalSize += files[i].fileSize;
    }

    printf("Total size: %lld bytes\n", totalSize);

    // return success
    return 0;
}




