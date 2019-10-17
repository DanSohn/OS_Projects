/*
A multi-threaded solution for computing the sum of a large array of integers.
Takes two arguments from command line:
    1. Name of file containing the integers (one number per line)
    2. <T> is number of threads to be created
Built under assumptions that:
    input contains N integers where N <= 1 000 000
    T <= N
*/

#include <iostream>
#include <fstream>

using namespace std;


int totalSum=0;
int numArr[1000000];


struct sum_struct
{
	int first;
	int last;
	int sum;
};

void* adder(void* arg)
{
	//cast arg from void* to desired type
	//cout<<"Entering adder function\n";
	struct sum_struct *arg_struct = (struct sum_struct*) arg;
	arg_struct->sum =0;
	//cout<<"Starting integer: "<<arg_struct->smallArr[0];
	//cout<<"First element: "<<arg_struct->first<<" Last element: "<<arg_struct->last;
	for(int i = arg_struct->first; i <= (arg_struct->last); i++)
	{
		//cout<<"Entered loop with i: "<<i<<endl;
		arg_struct-> sum += numArr[i];
	}
	totalSum+=arg_struct->sum;
	cout<<arg_struct->sum<<endl;
	pthread_exit(0);
}


int main(int argc, char * argv[])
{
	if(argc !=3){
		printf("Wrong amount of arguments, please try again");
	}
  	string filename;
  	filename = argv[1];
  	unsigned long numThreads = atol(argv[2]);
  	pthread_t tid[numThreads];
  	//create multithreads
  	sum_struct args[numThreads];

  	string line;
  	int arrSize = 0;

  	//open file for reading
 	 ifstream file;
 	 file.open(filename);
 	 if(file.is_open()){
	  //cout<<"here";
	  while(true){
		  int num;
		  file>>num;
		  if(file.eof()) break;
		  numArr[arrSize++]=num;
	  }
	  //for(int i = 0; i < arrSize; i++) cout <<numArr[i]<<" ";
	  //cout<<endl;
	  file.close();		  
  }
  else cout<<"unable to open file";
	//done creating array of integers from file


  for(int i=0;i<numThreads;i++){
	  if(i==0){ //our first amount
		  args[i].first = i;
		  args[i].last = args[i].first + arrSize/numThreads;
	  }else if(i<(arrSize%numThreads)){//while N%T containing N/T + 1 number of elements
		  args[i].first = args[i-1].last+1;
		  args[i].last = args[i].first + arrSize/numThreads;
	  }else{ //remaining T-N%T groups will contain N/T elements
		  args[i].first = args[i-1].last+1;
		  args[i].last = args[i].first + arrSize/numThreads - 1;
		  if(args[i].last>=arrSize){
			  args[i].last = arrSize - 1;
		  }
	  }
	  cout<<"Thread "<<i+1<<": ";

	  pthread_create(&tid[i], NULL, adder, &args[i]);
	 // kill all the threads after we are done using them
	  pthread_join(tid[i],NULL);
	    }
  cout<<"Sum = "<<totalSum<<endl;


  return 0;
}
