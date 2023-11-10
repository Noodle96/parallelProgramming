#include<stdio.h>
#include <stdlib.h>
#include<mpi.h>


struct Leones Func(int local_a, int local_b, int my_rank, int local_n);

int local_n;

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
    int blocklengths[2] = {1, local_n};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};
    MPI_Aint offsets[2];

    offsets[0] = offsetof(struct Pair, first);
    offsets[1] = offsetof(struct Pair, vec);

    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpiPair);
	// MPI_Type_contiguous(local_n, MPI_INT, &mpiPair);
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


struct Monos {
    int *a;
    float *b;
    int *c;
};
MPI_Datatype createMonosMPIType() {
    MPI_Datatype mpiMonos;
    int blocklengths[3] = {1, 1, 1}; // Número de elementos en cada bloque
    MPI_Datatype types[3] = {MPI_INT, MPI_FLOAT, MPI_INT}; // Tipo de dato de cada elemento
    MPI_Aint offsets[3]; // Desplazamiento en bytes desde el inicio de la estructura

    offsets[0] = offsetof(struct Monos, a);
    offsets[1] = offsetof(struct Monos, b);
    offsets[2] = offsetof(struct Monos, c);

    MPI_Type_create_struct(3, blocklengths, offsets, types, &mpiMonos);
    MPI_Type_commit(&mpiMonos);

    return mpiMonos;
}

struct Gatos {
    int patas[4];
    float colores[2];
};

MPI_Datatype createGatosMPIType() {
    MPI_Datatype mpiGatos;
    int block_lengths[2] = {4, 2};  // Número de elementos en cada parte de la estructura
    MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};  // Tipos de datos de cada parte de la estructura
    MPI_Aint offsets[2];  // Desplazamientos de cada parte de la estructura

    // Calcula los desplazamientos de cada parte en la estructura Gatos
    offsets[0] = 0;
    offsets[1] = sizeof(int) * 4;  // Desplazamiento de la segunda parte

    // Crea el tipo de dato MPI personalizado para Gatos
    MPI_Type_create_struct(2, block_lengths, offsets, types, &mpiGatos);
    MPI_Type_commit(&mpiGatos);

    return mpiGatos;
}

struct Delgfines {
    int algo[2];
    int varios[4];
};
MPI_Datatype createDelgfinesMPIType() {
    MPI_Datatype mpiDelgfines;
    int blocklengths[2] = {2, 4};  // Cantidad de elementos en cada campo
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};  // Tipos de datos de cada campo
    MPI_Aint offsets[2];  // Desplazamientos de cada campo

    offsets[0] = offsetof(struct Delgfines, algo);  // Desplazamiento del campo algo
    offsets[1] = offsetof(struct Delgfines, varios);  // Desplazamiento del campo varios

    // Crear el nuevo tipo de dato MPI
    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpiDelgfines);
    MPI_Type_commit(&mpiDelgfines);

    return mpiDelgfines;
}


struct Leones {
    int fuerza;
    int colores[2];
};

MPI_Datatype createLeonesMPIType() {
    MPI_Datatype mpiLeones;
    int blocklengths[2] = {1, 2};  // Cantidad de elementos en cada campo
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};  // Tipos de datos de cada campo
    MPI_Aint offsets[2];  // Desplazamientos de cada campo

    offsets[0] = offsetof(struct Leones, fuerza);  // Desplazamiento del campo fuerza
    offsets[1] = offsetof(struct Leones, colores);  // Desplazamiento del campo colores

    // Crear el nuevo tipo de dato MPI
    MPI_Type_create_struct(2, blocklengths, offsets, types, &mpiLeones);
    MPI_Type_commit(&mpiLeones);

    return mpiLeones;
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
	MPI_Datatype mpiMonos = createMonosMPIType();
	MPI_Datatype mpiGatos = createGatosMPIType();
	MPI_Datatype mpiLeones = createLeonesMPIType();
	// struct Pair temp;
	struct Leones temp;
	temp = Func(local_a, local_b, my_rank,local_n);
	if(my_rank != 0){
		// printf("myrank != 0\n");
		// printf("%d %d %d\n", pan.x, pan.y, pan.z);
		int send_result = MPI_Send(&temp, 1, mpiLeones, 0, 0, MPI_COMM_WORLD);
        if (send_result != MPI_SUCCESS) {
            fprintf(stderr, "Error en MPI_Send en el proceso %d\n", my_rank);
            MPI_Abort(MPI_COMM_WORLD, 1); // Abortar todos los procesos
        }
	}else{
		// printf("printf patas\n");
		// for(int e = 0 ;e < 4; e++){
		// 	printf("%d ",temp.patas[e]);
		// }printf("\n");
		// printf("printf colores\n");
		// for(int e = 0 ;e < 2; e++){
		// 	printf("%f ",temp.colores[e]);
		// }printf("\n");

		// printf("printf algo\n");
		// for(int e = 0 ;e < 2; e++){
		// 	printf("%d ",temp.algo[e]);
		// }printf("\n");
		// printf("printf varios\n");
		// for(int e = 0 ;e < 4; e++){
		// 	printf("%f ",temp.varios[e]);
		// }printf("\n");

		printf("printf leones\n");
		printf("%d\n", temp.fuerza);
		for(int e = 0; e < 2 ; e++){
			printf("%d ", temp.colores[e]);
		}printf("\n");


		

		// printf("%d %f %d\n", temp.a, temp.b, temp.c);
		// printf("\nin else antes for\n");
		// printf("viendo lo que hay en temp: \n");
		// printf("%d\n", temp.first);
		// for(int e = 0 ;e < local_n ; e++){
		// 	printf("%d ", temp.vec[e]);
		// }printf("\n");
		for(int source = 1; source < comm_sz; source++){
			// struct Pan algo;
			int recv_result = MPI_Recv(&temp, 1, mpiLeones, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
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
			// printf("%d %f %d\n", temp.a[0], temp.b[0], *temp.c[0]);

			// printf("printf algo\n");
			// for(int e = 0 ;e < 2; e++){
			// 	printf("%d ",temp.algo[e]);
			// }printf("\n");
			// printf("printf varios\n");
			// for(int e = 0 ;e < 4; e++){
			// 	printf("%f ",temp.varios[e]);
			// }printf("\n");

			printf("printf leones\n");
			printf("%d\n", temp.fuerza);
			for(int e = 0; e < 2 ; e++){
				printf("%d ", temp.colores[e]);
			}printf("\n");


			// printf("printf vec\n");
			// printf("local_n %d\n", local_n);
			// for(int e = 0; e < local_n ; e++){
			// 	printf("%d ", temp.vec[e]);
			// }

		}
	}
	MPI_Finalize();
	return 0;
}



struct Leones Func(int local_a, int local_b, int my_rank, int local_n){
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

	// struct Pan pan;
	// pan.x = my_rank+10;
	// pan.y = my_rank+11;
	// pan.z = my_rank+12;
	// return pan;

	// struct Monos myMonos;
	// myMonos.a = malloc(sizeof(int));
	// *myMonos.a = my_rank+100;  // Ejemplo de asignación para 'a'

	// myMonos.b = malloc(sizeof(float));
	// *myMonos.b = my_rank+112.78;  // Ejemplo de asignación para 'b'

	// myMonos.c = malloc(sizeof(int));
	// *myMonos.c = my_rank+120; 
	// return myMonos;
	// struct Gatos miGato;
	// miGato.patas[0] = my_rank+4;;
    // miGato.patas[1] = my_rank+4;
    // miGato.patas[2] = my_rank+4;
    // miGato.patas[3] = my_rank+4;

    // miGato.colores[0] = 0.5;  // Por ejemplo, color 1
    // miGato.colores[1] = 0.8;
	// return miGato;
	//  struct Delgfines delfines;
	//  delfines.algo[0] = my_rank+10;
	//  delfines.algo[1] = my_rank+11;

	//  delfines.varios[0] = my_rank+12;
	//  delfines.varios[1] = my_rank+13;
	//  delfines.varios[2] = my_rank+14;
	//  delfines.varios[3] = my_rank+15;
	//  return delfines;

	struct Leones leon;
	leon.fuerza = my_rank;
	leon.colores[0] = my_rank+1;
	leon.colores[1] =my_rank +2;
	return leon;
	// return p;
}