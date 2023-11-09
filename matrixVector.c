#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>


struct Pan Func(int local_a, int local_b, int my_rank, int local_n);


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
int local_n;
// Función para crear un tipo de dato MPI personalizado para la estructura Pair
MPI_Datatype createPairMPIType() {
    MPI_Datatype mpiPair;
    int blocklengths[2] = {1, local_n};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Aint offsets[2];

    offsets[0] = offsetof(struct Pair, first);
    offsets[1] = offsetof(struct Pair, vec);

    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpiPair);
	MPI_Type_contiguous(local_n, MPI_INT, &mpiPair);
    MPI_Type_commit(&mpiPair);

    return mpiPair;
}
struct  Pan {
    int x;
    int y;
    int z;
};
MPI_Datatype createPanMPIType() {
    MPI_Datatype mpiPan;
    int blocklengths[3] = {1, 1, 1}; // Número de elementos en cada bloque
    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT}; // Tipo de dato de cada elemento
    MPI_Aint offsets[3]; // Desplazamiento en bytes desde el inicio de la estructura

    offsets[0] = offsetof(struct Pan, x);
    offsets[1] = offsetof(struct Pan, y);
    offsets[2] = offsetof(struct Pan, z);

    MPI_Type_create_struct(3, blocklengths, offsets, types, &mpiPan);
    MPI_Type_commit(&mpiPan);

    return mpiPan;
}


int main(){
	int my_rank, comm_sz;
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
	MPI_Datatype mpiPan = createPanMPIType();
	// struct Pair temp;
	struct Pan temp;
	temp = Func(local_a, local_b, my_rank,local_n);
	if(my_rank != 0){
		// printf("myrank != 0\n");
		// printf("%d %d %d\n", pan.x, pan.y, pan.z);
		int send_result = MPI_Send(&temp, 1, mpiPan, 0, 0, MPI_COMM_WORLD);
        if (send_result != MPI_SUCCESS) {
            fprintf(stderr, "Error en MPI_Send en el proceso %d\n", my_rank);
            MPI_Abort(MPI_COMM_WORLD, 1); // Abortar todos los procesos
        }
	}else{
		printf("%d %d %d\n", temp.x, temp.y, temp.z);
		// printf("\nin else antes for\n");
		// printf("viendo lo que hay en temp: \n");
		// printf("%d\n", temp.first);
		// for(int e = 0 ;e < local_n ; e++){
		// 	printf("%d ", temp.vec[e]);
		// }printf("\n");
		for(int source = 1; source < comm_sz; source++){
			// struct Pan algo;
			int recv_result = MPI_Recv(&temp, 1, mpiPan, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (recv_result != MPI_SUCCESS) {
                fprintf(stderr, "Error en MPI_Recv en el proceso %d\n", my_rank);
                MPI_Abort(MPI_COMM_WORLD, 1); // Abortar todos los procesos
            }
			// printf("\n in else dentro de for: \n");
			// printf("viendo lo que hay en temp: \n");
			// printf("%d\n", algo.first);
			//  if (algo.vec != NULL) {
            //     for (int j = 0; j < local_n; j++) {
			// 		printf("%d ", algo.vec[j]);
            //     }
            // } else {
            //     printf("NULL");
            // }
            // printf("\n");
			printf("%d %d %d\n", temp.x, temp.y, temp.z);

		}
	}
	MPI_Finalize();
	return 0;
}



struct Pan Func(int local_a, int local_b, int my_rank, int local_n){
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
	// printf("\ntesting\n");
	// printf("my_rank: %d\n", my_rank);
	// printf("second\n");
	// for(int e = 0 ;e < local_n ; e++){
	// 	printf("%d ", p.vec[e]);
	// }printf("\n");

	struct Pan pan;
	pan.x = my_rank+10;
	pan.y = my_rank+11;
	pan.z = my_rank+12;
	return pan;
	// return p;
}