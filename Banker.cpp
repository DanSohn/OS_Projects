/*
 * banker.cpp
 *
 * Student Name: Jung Hyun Sohn
 * Student Number: 30017825
 *
 * Class: CPSC 457 Spring 2017
 * Instructor: Pavol Federl
 *
 * Copyright 2017 University of Calgary. All rights reserved.
 * Program that implements the Banker's Algorithm - determining whether there is a safe execution sequence for a given set of processes and a request. 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <string>
using namespace std;

class Banker
{
private:
    int numProc;      // the number of processes
    int numResources; // the number of resources
    int * available;  // number of available instances of each resource
    int ** max;       // the max demand of each process, e.g., max[i][j] = k
                      // means process i needs at most k instances of resource j
    int ** allocation;// the number of resource instances already allocated
    int ** need;      // the number of resource isntances needed by each process

public:

    /* Initializing the vectors and matrixes for the Banker's Algorithm. Takes ownership of
     * all arrays.
     * @param avail  The available vector
     * @param m      The max demand matrix
     * @param alloc  The allocation matrix
     * @param p      The number of processes
     * @param r      The number of resources
     */
    Banker (int * avail, int ** m, int ** alloc, int p, int r) {
        numProc = p;
        numResources = r;

        // Setup the available vector, the max matrix, and the allocation matrix
        available = avail;
        max = m;
        allocation = alloc;

        // Initialize the need matrix
        need = new int*[numProc];
        for (int i = 0; i < numProc; i++)
            need[i] = new int[numResources];
    }

    /* Destroy the vectors and matrixes
     */
    ~Banker() {
        numProc = 0;
        numResources = 0;

        // Free all allocated memory space
        delete[] available;
        for (int i = 0; i < numProc; i++)
        {
            delete[] need[i];
            delete[] max[i];
            delete[] allocation[i];
        }
        delete[] need;
        delete[] max;
        delete[] allocation;
    }

    /* Check whether it is safe to grant the request
     * @param pid    The process that is making the request
     * @param req    The request
     * @param sequenceOrReason  The safe execution sequence returned by the algorithm
     * @return Whether granting the request will lead to a safe state.
     */
    bool isSafe (int pid, int * req, string & sequenceOrReason) {
        //create sequence array
        int sequence[numProc];
        //create finish array
        bool finish[numProc];

        //Calculate Need matrix
        for(int i = 0; i < numProc; i++)
        {
            finish[i] = false;
            sequence[i] = 0;
            for(int j = 0; j < numResources; j++)
            {
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        //if request[] > need[i] raise error, process has exceeded max claim
        //if request[] > available then process must wait, not enough resources available
        for(int i = 0; i < numResources ; i++)
        {

            if(req[i] > need[pid][i]){
                sequenceOrReason = "Request is invalid (exceeding declared max for process).";
                return false;
            }
            if(req[i] > available[i])
            {
                sequenceOrReason = "Not enough Resources available.";
                return false;
            }
        }
        //if we reach this point, then we can start banker's algorithm

        //available = available - request for that specific process
        //alloc[i] = alloc[i] + request
        //need[i] = need[i] - request
        for(int i = 0; i < numResources ; i++)
        {
            available[i] = available[i] - req[i];
            allocation[pid][i] = allocation[pid][i] + req[i];
            need[pid][i] = need[pid][i] - req[i];
        }

        //Initialize temporary vectors work = available and finish[i] = false for all i

        //find an i such that finish[i] = false AND need[i] <= work
        //update sequence array by adding the process, which while be returned
        //if no such i exists, go to step 4
        bool tmp = true; // whether or not i is found so we can update avail and finish
        bool leave = false; //no such i exists, so break out of loop
        int count = 0; //for sequence

        while(!leave)
        {
            leave = true; //leave as long as we don't find
            for(int i = 0; i < numProc; i++)
            {
                tmp = true;
                if(finish[i] == false)
                {
                    for(int j = 0; j < numResources; j++)
                    {
                        if(need[i][j] > available[j])
                        {
                            tmp = false;
                            break;
                        }
                    }
                    if(tmp)
                    {
                        leave = false;
                        //if we find such i, update work and finish
                        for(int j = 0; j < numResources; j++)
                        {
                            available[j] += allocation[i][j];
                            finish[i] = true;
                        }
                        sequence[count] = i;
                        count++;
                        break;
                    }
                }
            }
        }
        //cout<<"MY count is " << count;
        //if finish[i] == true for all i, return true, else return false;
        for(int i = 0; i < numProc; i++)
        {
            if(finish[i] == false)
            {
                sequenceOrReason = "Request would result in an unsafe state.";
                return false;
            }
        }
        //finish[i] == true for all i, so we found a safe state
        sequenceOrReason = "";
        for(int i = 0; i < count; i++){
            sequenceOrReason += "P" + to_string(sequence[i]);
            if(i != count-1){
                sequenceOrReason += ", ";
            }
        }
        return true;
        //sequenceOrReason = "P" + to_string(sequence[0]) + ", P" + to_string(sequence[1])
        //+ ", P" + to_string(sequence[2]) + ", P" + to_string(sequence[3]) + ", P" + to_string(sequence[4]);
        //return true;
    }
};

int main (int argc, char * const argv[])
{
    ifstream config;       // Configuration file
    string conffile;       // The configuration file name
    int numProc;           // The number of processes
    int numResources;      // The number of resources
    string sequenceOrReason;       // The execution sequence returned by the Banker's Algorithm
    int i, j, index;       // Indices for the vectors and matrixes
    int pid;               // The ID of the process that is making the request
    string reqStr;         // The request vector in string format

    // Read in the config file name from the commanda-line arguments
    if (argc < 2)
    {
        cout << "Usage: banker <config file>\n";
        return 0;
    }
    else
    {
        conffile = argv[1];
    }

    // Open the file
    config.open(conffile.c_str());

    // Get the number of process and the number of resources
    string line, var, equal;    // strings for parsing a line in the config file
    getline(config, line);
    istringstream iss(line);
    iss >> var >> equal >> numProc;     // Get the number of processes
    iss.clear();

    getline(config, line);
    iss.str(line);
    iss >> var >> equal >> numResources;    // Get the number of resources
    iss.clear();

    // Create the available vector, the max matrix, and the allocation matrix
    // according to the number of processes and the number of resources
    int * available = new int[numResources];
    int ** max = new int*[numProc];
    int ** allocation = new int*[numProc];
    for (int i = 0; i < numProc; i++)
    {
        max[i] = new int[numResources];
        allocation[i] = new int[numResources];
    }

    // Get the available vector
    getline(config, line);
    replace(line.begin(), line.end(), '<', ' ');  // Remove "<" and ">"
    replace(line.begin(), line.end(), '>', ' ');
    iss.str(line);
    iss >> var >> equal;
    for (j = 0; j < numResources; j++)        // Read in the "available" vector
        iss >> available[j];
    iss.clear();

    // Get the max matrix and the allocation matrix
    for (i = 0; i < numProc; i++)
    {
        getline(config, line);
        replace(line.begin(), line.end(), '<', ' ');
        replace(line.begin(), line.end(), '>', ' ');
        iss.str(line);
        iss >> var;
        index = atoi(&var.at(1));            // Get the process ID
        if (index < 0 || index >= numProc)
        {
            cerr << "Invalid process ID: " << var << endl;
            return 0;
        }

        // Get the number of resources allocated to process "index".
        for (j = 0; j < numResources; j++)
            iss >> allocation[index][j];

        // Get the max allocation to process "index".
        for (j = 0; j < numResources; j++)
            iss >> max[index][j];

        iss.clear();
    }

    // Get the request vector
    int * request = new int[numResources];
    getline(config, line);
    reqStr = line.substr(line.find('<'), line.find('>') - line.find('<') + 1);
    replace(line.begin(), line.end(), '<', ' ');
    replace(line.begin(), line.end(), '>', ' ');
    iss.str(line);
    iss >> var >> pid >> equal;
    for (j = 0; j < numResources; j++)          // Read in the "request" vector
        iss >> request[j];
    iss.clear();

    // Check the request using the Banker's algorithm.
    Banker * banker = new Banker(available, max, allocation, numProc, numResources);
    if (banker -> isSafe(pid, request, sequenceOrReason))
        cout << "Grant request " << reqStr << " from P" << pid << ".\n"
             << "Sequence: " << sequenceOrReason << ".\n";
    else
        cout << "Reject request " << reqStr << " from P" << pid << ".\n"
             << "Reason: " << sequenceOrReason << "\n";
}
