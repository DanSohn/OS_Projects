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
            
3.  myFind.c
    Implemented a C program that replicates a small subset of the functionality of the 'find' system utility.
    The output is identifical to executing 'find . -type f'.
    Finds all files in currennt directory and prints them one line at a time to standard output.
    How to compile and run:
        gcc myFind.c -o myFind
        ./myFind
    
4.  sum.cpp
    A multi-threaded solution for computing the sum of a large array of integers.
    Takes two arguments from command line:
        1. Name of file containing the integers (one number per line)
        2. <T> is number of threads to be created
    Built under assumptions that:
        input contains N integers where N <= 1 000 000
        T <= N
    How to compile and run:
        g++ sum.cpp -o sum
        ./sum <file.txt> <T>
        
        
        
        
        
        