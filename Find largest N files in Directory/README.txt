scan.sh and scan.cpp
    Implemented using a bash script and C++.
    Input the suffix of the file (ex. .jpg) and the number of files to display (N).
    The current and all subdirectories are searched to find all files that end in the specified suffix and the N largest files are displayed. 
    How to compile and run:
        Script:
            ./scan.sh <extension> <N>
        CPP:
            g++ scan.cpp -o scan
            ./scan <extension> <N>