# OS_Projects

Simple Operating System Projects in C/C++, implementing paging, CPU scheduling, and deadlock detection algorithms

1.  myWc.cpp
    Implementing a line count utility program that closely follows the performance of the 'wc' command in linux.
    How to compile and run:
        g++ myWc.cpp -o myWc
        ./myWc <file.txt>

2.  Find the N largest files in a directory.
    Implemented using a bash script and C++.
    Input the suffix of the file (ex. .jpg) and the number of files to display (N).
    The current and all subdirectories are searched to find all files that end in the specified suffix and the N largest files are displayed. 
    How to compile and run:
        Script:
            ./scan.sh <extension> <N>