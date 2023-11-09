#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>


struct Pair -Func(int local_a, int local_b, int my_rank, int local_n);


struct Pair{
	int first;
	int *vec;
};

#define R 10
#define C 10

struct Pair totalSolution[R];
int M[R][C] = {
	{6, 8, 6, 1, 6, 4, 4, 0, 3, 6}, 
	{1, 8, 7, 8, 9, 1, 6, 5, 7, 4}, 
	{6, 1, 3, 4, 1, 1, 9, 4, 8, 9}, 
	{0, 6, 0, 8, 7, 6, 3, 3, 6, 8}, 
	{0, 8, 6, 7, 8, 5, 0, 7, 2, 8}, 
	{1, 9, 1, 7, 5, 2, 0, 4, 9, 9}, 
	{6, 1, 7, 8, 1, 5, 4, 6, 8, 2}, 
	{4, 0, 2, 2, 9, 3, 9, 0, 0, 2}, 
	{0, 3, 1, 1, 0, 6, 5, 1, 3, 4}, 
	{2, 1, 7, 9, 9, 9, 6, 5, 5, 7}
};

int V[R] = {2, 5, 6, 7, 8, 3, 7, 5, 9, 2};

// Función para crear un tipo de dato MPI personalizado para la estructura Pair
MPI_Datatype createPairMPIType() {
    MPI_Datatype mpiPair;
    int blocklengths[2] = {1, 1};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Aint offsets[2];

    offsets[0] = offsetof(struct Pair, first);
    offsets[1] = offsetof(struct Pair, vec);

    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpiPair);
    MPI_Type_commit(&mpiPair);

    return mpiPair;
}


int main(){
	int my_rank, comm_sz,local_n;
	int a = 0, local_a, local_b;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// OBSERVACION:
	// comm_sz tiene que dividir exacto a R
	local_n = R/comm_sz;

	local_a = a + my_rank*local_n;
	local_b = local_a+ local_n;
	
	MPI_Datatype mpiPair = createPairMPIType(); // Crear el tipo de dato MPI personalizado
	struct Pair temp;
	temp = Func(local_a, local_b, my_rank,local_n);
	if(my_rank != 0){
		// MPI_Send(&temp,1,MPI_INT,0,0,MPI_COMM_WORLD);
		MPI_Send(&temp, 1, mpiPair, 0, 0, MPI_COMM_WORLD);
	}else{
		total_int = temp;
		for(int source = 1; source < comm_sz; source++){
			// MPI_Recv(&temp,1,MPI_INT,source,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&temp, 1, mpiPair, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			total_int += temp;
		}
	}
	if(my_rank == 0){
		printf("total_int: %d\n", total_int);
	}
	MPI_Finalize();
	return 0;
}



struct Pair Func(int local_a, int local_b, int my_rank, int local_n){
	struct Pair p;
	p.first = my_rank;
	int position = 0;
	p.vec = (int *)malloc(local_n * sizeof(int));
	if (p.vec == NULL) {
        // Manejar el error si la asignación de memoria falla
        exit(1);  // O puedes tomar medidas apropiadas según tu aplicación
    }
	
	for(int row = local_a; row < local_b; row++){
		int temp = 0;
		for(int col = 0 ;col < R ; col++){
			temp += (M[row][col]* V[col]);
		}
		p.vec[position] =temp;
		position++;
	}
	printf("\ntesting\n");
	printf("my_rank: %d\n", my_rank);
	printf("second\n");
	for(int e = 0 ;e < local_n ; e++){
		printf("%d ", p.vec[e]);
	}printf("\n");
	return p;
	// printf("\na:%d, b:%d, myrank:%d\n",local_a, local_b, my_rank);
	// return my_rank;
}