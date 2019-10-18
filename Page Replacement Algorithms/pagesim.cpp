/*
Jung Hyun Sohn
Simulation of three page replacement algorithms: Optimal, LRU, and Clock.
Program outputs content of frames and number of page faults for each algorithm.

*/
#include<bits/stdc++.h>
#include <iostream>
#include <array>
using namespace std;

//following the algorithm found here:
//https://cs.stackexchange.com/questions/24011/clock-page-replacement-algorithm-already-existing-pages
//which is a desccrption of the algorithm
void clock(int pages[], int size, int capacity){
    cout<<"Clock:"<<endl;
    int currFrame[capacity];
    int usedFlag[capacity];
    int pos = 0;
    int numFaults = 0;
    int *p;

    //initialize current frame and used flags to be -1 and 0 respectively
    for(int i=0; i < capacity; i++){
        currFrame[i] = -1;
        usedFlag[i] = 0;
    }


    for(int i = 0; i<size;i++){

        p = find(currFrame,currFrame+capacity, -1);
        //if current frame not filled up
        if(p != currFrame + capacity)
        {
            //if the value at i is not in current frame
            p = find(currFrame,currFrame+capacity, pages[i]);
            if(p == currFrame + capacity)
            {
                //add it at the pos
                currFrame[pos] = pages[i];
                usedFlag[pos] = 1;
                if(pos == capacity - 1){
                    pos = 0;
                }else{
                    pos++;
                }
                // increment page fault
                numFaults++;
            }

            // Store the recently used index of
            // each page
            //indexes[pages[i]] = i;
            //cout << "Number " << i << " last seen at index " << i<<endl;
        }else{
            //actual algorithm
            p = find(currFrame, currFrame + capacity, pages[i]);
            if(p != currFrame + capacity){
                //present in memory
                //cout<<"entered here"<<endl;
                if(usedFlag[*p] != 1){
                    //recently used is false
                    //just change it to recently used
                    if(i != size -1){
                        usedFlag[*p] = 1;
                    }
                }

            }else{
                //not present in memory
                //In this case we look at the clock-hand.
                //While the clock-hand is pointing to a page with the recently-used bit set
                //true we flip the recently-used bit to false, and then increment clock-hand
                //to point to the next page. When we find a page with recently-used already cleared,
                //that is the page we replace. Then we mark the new page as
                //recently-used and increment the clock-hand to the next page.

                while(usedFlag[pos] == 1){
                    usedFlag[pos] = 0;
                    if(pos == capacity - 1){
                        pos = 0;
                    }else{
                        pos++;
                    }
                }

                currFrame[pos] = pages[i];
                usedFlag[pos] = 1;
                if(pos == capacity - 1){
                    pos = 0;
                }else{
                    pos++;
                }
                numFaults++;
            }
        }

        //print out current frame
        /* for(int k = 0; k < capacity; k++){
            cout<< currFrame[k] << " ";
        }
        cout<<endl; */

    }
        cout << "  - frames: ";
    for(int j = 0; j < capacity; j++){
        cout << currFrame[j] << " ";
    }
    cout <<"\n  - page faults: "<<numFaults<<endl;
}
void optimal(int pages[], int size, int capacity){
    cout<<"Optimal:"<<endl;
    int currFrame[capacity];
    for(int i = 0; i < capacity; i ++){
        currFrame[i] = -1;
    }
    int *p;

    // To store next used indexes
    // of pages.
    unordered_map<int, int> indexes;

    int numFaults = 0;
    //pos in frames
    int pos = 0;

    for(int i = 0; i<size;i++){

        p = find(currFrame,currFrame+capacity, -1);
        //if current frame not filled up
        if(p != currFrame + capacity)
        {
            //if the value at i is not in current frame
            p = find(currFrame,currFrame+capacity, pages[i]);
            if(p == currFrame + capacity)
            {
                //add it at the pos
                currFrame[pos] = pages[i];
                if(pos == capacity - 1){
                    pos = 0;
                }else{
                    pos++;
                }
                // increment page fault
                numFaults++;
            }

            // Store the recently used index of
            // each page
            //indexes[pages[i]] = i;
            //cout << "Number " << i << " last seen at index " << i<<endl;
        }

        // If the array is full then need to perform optimal page alg
        // i.e. for all the values in current frame, find the next
        // time they are in use
        else
        {
            // Check if current page is not already
            // present in the set
            //cout<<"Looking for " << pages[i]<<endl;
            p = find(currFrame,currFrame+capacity, pages[i]);
            if(p == currFrame + capacity)
            {
                //cout<<"Not found!" <<endl;
                // Find the least recently used pages
                // that is present in the set
                //5000 is max number of entries
                int furthest = i;
                int val;

                //check each number in current frames,
                // and for each number go from current index + 1
                // to the very end and find which one has the furthest index
                // currFrame[j] is how to reference
                //cout<<"Rest of reference string"<<endl;
                //cout <<"size and current i: " << size << " " << i<<endl;
                for(int j = 0; j < capacity; j++){
                    for(int k = i + 1; k < size; k++){
                        //cout<<"Entered here"<<endl;
                        //cout<< pages[k] << " .";
                        if(pages[k] == currFrame[j]){
                            indexes[currFrame[j]] = k;
                            break;
                        }
                        if(k == size - 1){
                            //5k is max possible num of entries
                            indexes[currFrame[j]] = 5000;
                        }
                    }
                    //cout<<endl;
                    //cout<<"Distance for number " << currFrame[j]<<" is " << indexes[currFrame[j]]<<endl;
                }
                for(int j = 0; j < capacity; j++){
                    if(indexes[currFrame[j]] > furthest){
                        furthest = indexes[currFrame[j]];
                        val = currFrame[j];
                    }
                }
                //cout<<"Gotta get rid of number: " <<val<<endl;
                for(int j = 0; j < capacity; j++){
                    if(currFrame[j] == val){
                        currFrame[j] = pages[i];
                    }
                }

                // Increment page faults
                numFaults++;
            }

        }
        //for testing
        /*for(int j = 0; j < capacity; j++){
            cout << currFrame[j] << " ";
        }
        cout<<endl;
        */
    }
    cout << "  - frames: ";
    for(int j = 0; j < capacity; j++){
        cout << currFrame[j] << " ";
    }
    cout <<"\n  - page faults: "<<numFaults<<endl;

}



void LRU(int pages[], int size, int capacity){
    cout<<"LRU:"<<endl;
    // array for current frames
    int currFrame[capacity];
    for(int i = 0; i < capacity; i ++){
        currFrame[i] = -1;
    }
    int *p;
    // To store least recent used pages
    unordered_map<int, int> indexes;

    // number of faults
    int numFaults = 0;
    // position in the frames
    int pos = 0;
    for (int i = 0; i < size; i++)
    {
        // Check if the arr can hold more pages
        p = find(currFrame,currFrame+capacity, -1);
        if(p != currFrame + capacity)
        {
            //if the current value doesn't exist in frame yet
            p = find(currFrame,currFrame+capacity, pages[i]);
            if(p == currFrame + capacity)
            {
                currFrame[pos] = pages[i];
                if(pos == capacity - 1){
                    pos = 0;
                }else{
                    pos++;
                }
                // increment page fault
                numFaults++;
            }

            // Store the recently used index of
            // each page
            indexes[pages[i]] = i;
            //cout << "Number " << i << " last seen at index " << i<<endl;
        }else{
            // if the current val is in our frame
            //cout<<"Looking for " << pages[i]<<endl;
            p = find(currFrame,currFrame+capacity, pages[i]);
            if(p == currFrame + capacity){
                //cout<<"Not found!" <<endl;
                // Find the least recently used pages
                //5000 is max number of entries
                int lru = 5000;
                int val;

                for(int j = 0; j < capacity; j++){
                    if(indexes[currFrame[j]] < lru){
                        lru = indexes[currFrame[j]];
                        val = currFrame[j];
                    }
                }
                //cout<<"Gotta get rid of number: " <<val<<endl;
                for(int j = 0; j < capacity; j++){
                    if(currFrame[j] == val){
                        currFrame[j] = pages[i];
                    }
                }
                // Increment page faults
                numFaults++;
            }

            // Update the current page index
            indexes[pages[i]] = i;
        }
        //for testing
        /*
        for(int j = 0; j < capacity; j++){
            cout << currFrame[j] << " ";
        }
        cout<<endl;
        */
    }
    cout << "  - frames: ";
    for(int j = 0; j < capacity; j++){
        cout << currFrame[j] << " ";
    }
    cout <<"\n  - page faults: "<<numFaults<<endl;


}

int main( int argc, char ** argv){

    /// parse command line arguments
    int cap = 0;
    if(argc != 2) {
        printf("Usage: pagesim [number of available frames]\n");
        exit(-1);
    }
    if( argc == 2) cap = atoi( argv[1]);

    /// handle invalid arguments
    if( cap < 1 || cap > 20) {
        printf("Bad arguments. 1 <= available frames <= 20!\n");
    }

    int arr[5000];// = new int[5000];
    for(int i = 0; i < 5000; i ++){
        arr[i] =-1;
    }

    int position = 0;
    while(1) {
        if( 1 != scanf("%lld", &arr[position])) break;
        position++;
    }
    //int pages[] = {1,2,3,4,1,2,5,1,2,3,4,5};

    int newArr[position];
    copy(arr, arr + position, newArr);

    int n = sizeof(newArr)/sizeof(newArr[0]);
    //int cap = 4;
    optimal(arr, n, cap);
    LRU(arr, n, cap);
    clock(newArr, n, cap);
    return 0;
}
