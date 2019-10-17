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
	  //cout<<"New place";
	  //cout<<"Array Size: "<<arrSize<<endl;
	  //cout<<"Number of threads: "<<numThreads<<endl;
	  /*if (i < (arrSize%numThreads)){//first N%T groups 
		  cout<<"First version"<<endl;
		  args[i].first = i*(arrSize/numThreads+1);
		  args[i].last = (i+1)*(arrSize/numThreads + 1)-1;
			  //copy numArr into args[i].smallArr[count]
			  //increase count 
	          std::copy(numArr + args[i].first, numArr + (args[i].last+1), args[i].smallArr);
		 
		  pthread_create(&tid[i], NULL, adder, &args[i]);

	  }else{
		  cout<<"Second version"<<endl;
		  cout<<"last:"<<args[i].last<<endl;
		  args[i].first = (arrSize%numThreads)*(arrSize/numThreads) + (i-arrSize%numThreads)*(arrSize/numThreads)+1;
		  args[i].last = (arrSize%numThreads)*(arrSize/numThreads) + (i + 1 -arrSize%numThreads)*(arrSize/numThreads);
		  cout<<"First and last:"<<args[i].first<<"  "<<args[i].last<<endl;
		  std::copy(numArr + args[i].first, numArr + (args[i].last+1), args[i].smallArr);
		cout<<"Last element again:"<<args[i].last<<endl;
		  pthread_create(&tid[i], NULL, adder, &args[i]);

		
	  }
	  Please respect this mistakes that I made it took time and i shed a tear over my mistakes I want to cry
	  */

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
