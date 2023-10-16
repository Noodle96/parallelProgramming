#include <stdio.h>
#include <string.h>  /* For strlen             */
#include "mpi.h"    /* For MPI functions, etc */ 
#include <unistd.h>

const int MAX_STRING = 100;

int main(void) {
	char hostname[256];					 /* name of hostname*/
	int 		  valueTemp = 1;             /* Value goal */
   int        comm_sz;               /* Number of processes    */
   int        my_rank;               /* My process rank        */
   
	//if (gethostname(hostname, sizeof(hostname)) == 0) {
   //     printf("Hostname: %s\n", hostname);
   //} else {
   //     perror("Error getting hostname");
   //}

   /* Start up MPI */
   MPI_Init(NULL, NULL); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   //printf("\nprint comm_sz %d", comm_sz);

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   //printf("\nprint my_rank %d", my_rank);

   while (valueTemp <= 100) {
        if (my_rank == 0) {
            int received_value;
            MPI_Recv(&received_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            valueTemp = received_value;
            printf("Proceso %d recibió el valor: %d\n", my_rank, valueTemp);
        } else if (my_rank == 1) {
            valueTemp++; // Aumenta la variable valueTemp
            MPI_Send(&valueTemp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
