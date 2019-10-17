/* 
Student : Jung Hyun Sohn
ID : 30017825
TA: Sina
CPSC457
Assignment 3
*/
/*
Improving a C program provided by Professor Federl, by making it multi-threads using pthreads. Program takes in a single command arg "N" which determines number of threads allowed to run at a time.
Counts number of primes from standard input
Compile with:
g++ -lpthread primes.cpp -02 -o count -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
using namespace std;
int arr_index;
int64_t count = 0;
int n;
int myArr[3];
bool condFlag = false;
pthread_mutex_t index_mutex;
pthread_mutex_t count_mutex;

long long * arr;

/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n, int incr, int numThreads, bool big)
{
    int multiplier;
    if(big){
        multiplier = numThreads;
    }else{
        multiplier = 1;
    }
    //printf("checking number %lld\n", (long long)n);
    if( n <= 1) return 0; // small numbers are not primes
    if( n <= 3) return 1; // 2 and 3 are prime
    if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
    int64_t i = incr;
    int64_t max = sqrt(n);
    while( i <= max) { //&& condFlag
        if(condFlag) return 0;
        if (n % i == 0 || n % (i+2) == 0) return 0;
        i += 6 * multiplier;
    }
    condFlag = true;
    return 1;
}

void* countPrimes(void* args){ //maybe pass in a struct?
    int *myArray = (int *)args;
    //printf("thread num %d\n", threadNum);

    int i;
    int64_t start;
    int64_t finish;
    while(1) {

        pthread_mutex_lock(&index_mutex);
        i = arr_index++;
        pthread_mutex_unlock(&index_mutex);
        //printf("thread num %d\n", i);
        if(i >= n)
            break;
        long long num = arr[i];
        condFlag = false;
        int is_prime;
        if(num > 1000000000000000000){
            is_prime = isPrime(num, myArray[0], myArray[1], true);
        }else{
            is_prime = isPrime(num, myArray[0], myArray[1], false);
        }
        //printf("checking\n");
        if (is_prime) {
            //printf("%lld is a prime\n", (long long)num);
            pthread_mutex_lock(&count_mutex);
            //condFlag = 0;
            count++;
            pthread_mutex_unlock(&count_mutex);
        }
    }
    return NULL;
}

int main( int argc, char ** argv)
{
    /// parse command line arguments
    int nThreads = 1;
    if( argc != 1 && argc != 2) {
        printf("Usage: countPrimes [nThreads]\n");
        exit(-1);
    }
    if( argc == 2) nThreads = atoi( argv[1]);

    /// handle invalid arguments
    if( nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }

    arr = new long long[10000];

    /// count the primes
    printf("Counting primes using %d thread%s.\n", nThreads, nThreads == 1 ? "" : "s");
    //int64_t count = 0;

    n = 0;
    while(1) {
        int64_t num;
        if( 1 != scanf("%lld", &arr[n])) break;
        //arr[n] = num;
        //if(isPrime(num)) count ++;
        n++;
    }

    pthread_t myThread[nThreads];
    pthread_mutex_init(&index_mutex, NULL);
    pthread_mutex_init(&count_mutex, NULL);

    for(int i = 0; i < nThreads; i++){
        myArr[0] = 5 + (i*6);
        //myArr[1] = arr[i];
        myArr[1] = nThreads;
        pthread_create(&myThread[i], NULL, countPrimes, &myArr);
    }
    for(int i = 0; i < nThreads; i++)
        pthread_join(myThread[i], NULL);

    /// report results
    printf("Found %lld primes.\n", count);

    return 0;
}
