/*
Student : Jung Hyun Sohn
ID : 30017825
TA: Sina
CPSC457
Assignment 3
Simulates execution of processes using non-preemptive shortest-job-first and preemptive round-robin.

*/

#include<iostream>
#include<fstream>
#include<string> // for string class
#define MAX_NUMBER 30
using namespace std;


int queue[100], num = 100, front = - 1, rear = - 1;
typedef struct {
    int arrivalTime;
    int burstTime;
    int status;//0 = not ini / finished, 1 = ready, 2 = running
    double waitTime;
} Process;
//used queues taught from this tutorial. The next three methods are with queues
//https://www.tutorialspoint.com/cplusplus-program-to-implement-queue-using-array
void ins(int ele){
   int value;
   if (rear == num - 1){
      cout<<"Queue Error, too much"<<endl;
   }else {
      if (front == -1){
          front = 0;
      }
      value = ele;
      rear++;
      queue[rear] = value;
   }
}
void del(){
   if (front == -1 || front>rear) {
      cout<<"Queue Error, too little ";
      return ;
   } else {
      front++;
   }
}
void display(){
   if (front == - 1)
   cout<<"Queue is empty";
   else {
      for (int i = front; i <= rear; i++)
         cout<<queue[i]<<" ";
   }
}
void RR(Process *myProc, int numProcess, int totalTime, int timeQuantum ){
    int currentProcess = -1;
    int quantum = timeQuantum;
    bool changed = false;
    cout<<"Time   ";
    for(int i=0;i<numProcess;i++){
        printf("P%d\t", i);
    }
    cout<<"\n---------------------------------------------------------------\n";

    for(int i = 0; i<totalTime;i++){
        printf(" %2d     ", i);
        for(int j=0;j<numProcess;j++){
            //printf("tester %d ", myProc[j].burstTime);
            if(myProc[j].status == 0){
                //if its not done
                if(myProc[j].burstTime>0){
                    //if the arrival time is this specific time then ready it

                    if(myProc[j].arrivalTime == i){
                        //if theres nothing else then immediately goes to running
                        //printf("test");
                        if(currentProcess == -1){
                            myProc[j].status = 2;
                            ins(j);
                            currentProcess = j;
                            printf(".\t");
                            myProc[j].burstTime--;
                            quantum--;
                        }else{
                            if(!changed){
                                ins(j);
                                //changed = false;
                            }else{
                                changed = false;
                            }
                            myProc[j].status = 1;
                            myProc[j].waitTime++;
                            printf("+\t");
                        }
                    }else printf(" \t");
                }else{ //it is fully done
                    printf(" \t");
                }
            }else if(myProc[j].status == 1){
            //if the process is ready state
                //if there is no current process currently
                //printf("lop");
                if(currentProcess == j){
                    //if currentProcess changed to be this process
                    myProc[j].status = 2;
                    //currentProcess = j;
                    printf(".\t");
                    myProc[j].burstTime--;
                    quantum--;
                }else{//if there is a current process running already
                    myProc[j].waitTime++;
                    printf("+\t");
                }
            //if the process is running
            }else if(myProc[j].status == 2 ){
                //if there is still fuel left then stay as current process
                //and decrement the bursttime, otherwise change it to done
                //printf("check");
                if(myProc[j].burstTime > 1){
                    if(quantum>1){
                        //currentProcess = j;
                        printf(".\t");
                        quantum--;
                        myProc[j].burstTime--;
                    }else if(quantum<=1){
                        for(int p = j+1; p < numProcess;p++){
                            if(myProc[p].status == 0 && myProc[p].arrivalTime ==i){
                                changed = true;
                                ins(p);
                            }
                        }
                        del();
                        ins(j);
                        myProc[j].status = 1;
                        //currentProcess = queue[front];
                        //cout<<currentProcess;
                        myProc[j].burstTime--;
                        quantum = timeQuantum;
                        printf(".\t");
                    }
                }else{
                    del();
                    myProc[j].status = 0;
                    quantum = timeQuantum;
                    printf(".\t");
                }
            }

        }
        if (currentProcess != -1) currentProcess = queue[front];
        //display();
	    //printf("quantum: %d", quantum);
        printf("\n");
    }
    myProc[0].waitTime--;
    cout<<"\n---------------------------------------------------------------\n";
    double avgWaitTime=0;
    for(int p = 0;p<numProcess;p++){
        printf("P%d  waited %.3f sec\n", p, myProc[p].waitTime);
        avgWaitTime+=myProc[p].waitTime;
    }
    //printf("Total wait time: %f secs", )
    avgWaitTime = avgWaitTime/numProcess;
    printf("Average Waiting Time = %.3f sec", avgWaitTime);

    cout<<endl;

}
//SJF scheduler process, needing the process array struct, number of
// processes and the total amount of time.
void SJF(Process *myProc, int numProcess, int totalTime ){
    int currentProcess = -1;
    cout<<"Time   ";
    for(int i=0;i<numProcess;i++){
        printf("P%d\t", i);
    }
    cout<<"\n---------------------------------------------------------------\n";

    int smallest;
    int smallIni = 100;;

    for(int i=0;i<totalTime;i++){
        printf(" %2d     ", i);

        //this for statement is only to find in the very beginning which
        //is the shortest job when the arrival times are equal
        for(int k=0; k<numProcess;k++){
            if(myProc[k].status == 0){
                if(myProc[k].arrivalTime == i){
                    if(myProc[k].burstTime<smallIni){
                        smallIni = myProc[k].burstTime;
                        //cout<<"smallest ini"<<smallIni<<endl;
                    }
                }
            }
        }

        for(int j=0;j<numProcess;j++){
            //if process is not here or done

            //printf("smallest : %d\n", smallest);
            if(myProc[j].status == 0){
                //if its not done
                if(myProc[j].burstTime>0){
                    //if the arrival time is this specific time then ready it
                    if(myProc[j].arrivalTime == i){
                        //if theres nothing else then immediately goes to running
                        if(currentProcess == -1){
                            if(myProc[j].burstTime == smallIni){
                                myProc[j].status = 2;
                                currentProcess = j;
                                printf(".\t");
                                smallest = myProc[j].burstTime;
                                myProc[j].burstTime--;
                            }else{
                                myProc[j].status = 1;
                                //printf("Wait time: %d", myProc[j].waitTime);
                                myProc[j].waitTime++;
                                //printf("Wait time: %d", myProc[j].waitTime);
                                printf("+\t");
                            }
                        }else{
                            myProc[j].status = 1;
                            //printf("Wait time: %d", myProc[j].waitTime);
                            myProc[j].waitTime++;
                            //printf("Wait time: %d", myProc[j].waitTime);
                            printf("+\t");
                        }
                    }else{
                        printf(" \t");
                    }
                }else{ //it is fully done
                    printf(" \t");
                }
            }else if(myProc[j].status == 1){
            //if the process is ready state
                //if there is no current process currently
                if(currentProcess == -1){
                    //check if there is a process with a smaller amount of burstTime
                    if(myProc[j].burstTime==smallest){
                        myProc[j].status = 2;
                        currentProcess = j;
                        printf(".\t");
                        myProc[j].burstTime--;
                    }else{
                        myProc[j].waitTime++;
                        printf("+\t");
                    }
                }else{
                    //if there is a current process running already
                    myProc[j].waitTime++;
                    printf("+\t");
                }
            //if the process is running
            }else if(myProc[j].status == 2 ){
                //if there is still fuel left then stay as current process
                //and decrement the bursttime, otherwise change it to done
                if(myProc[j].burstTime>1){
                    currentProcess = j;
                    printf(".\t");
                    myProc[j].burstTime--;
                }else{
                    myProc[j].status = 0;
                    currentProcess = -1;
                    smallest = 100;
                    myProc[j].burstTime--;
                    printf(".\t");
                }
            }
        }
        for(int k=0; k<numProcess;k++){
            if(myProc[k].status == 1){
                if(myProc[k].burstTime<smallest){
                    smallest = myProc[k].burstTime;
                }
            }
        }
        printf("\n");
    }
    myProc[0].waitTime--;
    cout<<"\n---------------------------------------------------------------\n";
    double avgWaitTime=0;
    for(int p = 0;p<numProcess;p++){
        printf("P%d  waited %.3f sec\n", p, myProc[p].waitTime);
        avgWaitTime+=myProc[p].waitTime;
    }
    //printf("Total wait time: %f secs", )
    avgWaitTime = avgWaitTime/numProcess;
    printf("Average Waiting Time = %.3f sec", avgWaitTime);

    cout<<endl;

}


int main( int argc, char ** argv)
{
    string process;
    int timeQuantum;
    ifstream myFile;
    int x;
    int i = 0;
    int arrival;
    int burst;
    int totalTime=0;

    int numProcess = 0;
    bool temp = true;
    if( argc != 3 && argc != 4) {
        printf("Usage: process textfile RR/SJF <time quantum>(optional)\n");
        exit(-1);
    }
    if( argc == 3){

        process = argv[2];
        if(process == "RR"){
            printf("Missing time quantum argument. Try again\n");
            exit(-1);
        }
        if(process != "SJF"){
            printf("Input RR or SJF for scheduler, try again\n");
            exit(-1);
        }
    }
    if(argc == 4){
        process = argv[2];
        timeQuantum = atoi(argv[3]);
        if(process == "SJF"){
            printf("No time quantum component for SJF. Try again\n");
            exit(-1);
        }
        if(process != "RR"){
            printf("Input RR or SJF for scheduler, try again\n");
            exit(-1);
        }
    }
    myFile.open(argv[1]);
    if(!myFile){
        printf("Unable to open file\n");
        exit(1); //terminate
    }

    Process myProc[MAX_NUMBER];
    while(myFile >> x){
        //i use temp to switch between the two columns. Temp = arrivaltime
        if(temp){
            myProc[i].arrivalTime = x;
            temp = !temp;
            //printf("process %d has arrival time: %d\n", i, myProc[i].arrivalTime);
        }else{
            myProc[i].burstTime = x;
            temp = !temp;
            numProcess++;
            totalTime +=x;
            i++;
            //printf("process %d has burst time: %d\n", i, myProc[i].burstTime);
        }

        myProc[i].status = 0; //does it twice per process, not efficient but i want it in while loop
        myProc[i].waitTime = 0;

    }
    //printf("Wait time: %d", myProc[0].waitTime);
    myProc[0].waitTime++;
    //printf("Wait time: %d", myProc[0].waitTime);
    totalTime +=myProc[0].arrivalTime;
    //cout<<"Number of processes: "<<numProcess<<endl;

    //for(int i=0;i<numProcess;i++){
    //    printf("Process %d has arrival time: %d burst time: %d\n", i,myProc[i].arrivalTime, myProc[i].burstTime);
    //}
    if(process == "SJF"){
        SJF(myProc, numProcess, totalTime);
    }else if(process == "RR"){
        RR(myProc, numProcess, totalTime, timeQuantum);
    }
    myFile.close();
    return 0;
}
