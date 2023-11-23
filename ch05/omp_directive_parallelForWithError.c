/*
	^ compile: gcc -g -Wall -fopenmp omp_directive_parallelForWithError.c 
	! this program return a error:
	! error: invalid branch to/from OpenMP structured block
  	!  35 |   if (A[i] == key) return i;
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int linearSearch(int key, int A[], int n);
void Usage(char* prog_name);
int     thread_count;
int ans;
#define N 10
int data[N];

int main(int argc, char* argv[]) {
   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
	for(int e = 0 ; e < N; e++) data[e] = e*e;
   ans = linearSearch(7, data,thread_count);

   return 0;
}  /* main */

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */

int linearSearch(int key, int A[], int n) {
	int i;
#	pragma omp parallel for num_threads(thread_count)
	for (i = 0; i < n; i++)
		if (A[i] == key) return i;
	return -1;
}
