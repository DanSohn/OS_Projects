/*
Improving countLines.cpp file provided by Professor Federl.
Implementing a line count utility program that closely follows the performance of the 'wc' command in linux. This program is written to only use low level file APIs such as open() close() and read()

How to compile and run:
g++ myWc.cpp -o myWc
./myWc <file.txt>
*/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

using namespace std;
int main (int argc, char * const argv[])
{
	string filename;
	filename = argv[1];

	// open the file for reading
	int fd = open( filename.c_str(), O_RDONLY);
	// read file character by character and count lines

	int upper = 10000;
	int count = 0;
	int r = 0;
	while(1)
	{
		char c[upper];
		r = read( fd, & c, upper);
		for (int i = 0; i < upper; i++)
		{
			//if the character is a line break then that's an end of the line and so we incr count
			if(c[i] == '\n' ) count ++;
		}
		//once we finish reading the last <10 000 the code recognizes that since its less than upper variable, it is the very end hence we break out of the loop
		if ( r < upper) break;
	}
	close (fd);
	//print number of lines plus file name
	cout << count << " " << filename << endl;
	return 0;
}
