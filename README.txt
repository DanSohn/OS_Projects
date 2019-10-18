OS Projects

Simple Operating System projects and assignments in C/C++, implementing paging, CPU scheduling, and deadlock detection algorithms. The following states what each file does and how to compile and run them. Feel free to look around!

1.  myWc.cpp
    Implementing a line count utility program that closely follows the performance of the 'wc' command in linux.
    How to compile and run:
        g++ myWc.cpp -o myWc
        ./myWc <file.txt>

2.  Find the N largest files in a directory.
    Check it's README.txt
            
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
        
5.  primes.cpp
    Improving a C program provided by Professor Federl, by making it multi-threads using pthreads. Program takes in a single command arg "N" which determines number of threads allowed to run at a time.
    Counts number of primes from standard input
    Compile with:
        g++ -lpthread primes.cpp -02 -o count -lm      
        ./count < <test.txt> (where test.txt contains numbers)
        
6.  scheduler.cpp
    Simulates execution of processes using non-preemptive shortest-job-first and preemptive round-robin.
    Accepts 3 arguments:
        1) name of config file
        2) name of algorithm ('RR' or 'SJF')
        3) time quantum for RR algorithm (Don't add if SJF)
    
    Sample Config file:
    1 10
    3 5
    5 3
    
    How to compile and run:
        g++ scheduler.cpp -o scheduler
        ./scheduler <config.txt> <RR/SJF> <Quantum>
    
7.  Banker's Algorithm
    Check it's README.txt
    
8.  deadlock.cpp
    Check it's README.txt
    
9.  Page Replacement Algorithms
    Check it's README.txt
    
    
    
    
        
        
        