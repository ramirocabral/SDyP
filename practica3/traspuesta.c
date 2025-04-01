#include<stdio.h>
#include<stdlib.h>
#include<omp.h> 
#include "../utils/utils.c"


int main(int argc,char*argv[]){
	double *A;
	double temp; 
	int i,j, N,tid;
	int check=1;
	double timetick;

	if (argc < 3){
		printf("\n Faltan argumentos:: N dimension de la matriz, T cantidad de threads \n");
		return 0;
	}
	N=atoi(argv[1]);
	int numThreads = atoi(argv[2]);
	omp_set_num_threads(numThreads);	

	A=(double*)malloc(sizeof(double)*N*N);


	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if (i>=j)
				A[i*N+j]= 1.0;
			else
				A[i*N+j]= 0.0;
		}
	}   

	#pragma omp parallel default(none) private(i,j,temp,timetick,tid) shared(A,N)
	{ 
		tid= omp_get_thread_num();
		timetick = dwalltime();
		#pragma omp for private(i,j,temp) nowait schedule(dynamic, 48)
		// #pragma omp for private(i,j,temp) nowait
		for(i=0;i<N;i++){
			for(j=i+1;j<N;j++){
				temp = A[i*N+j];
				A[i*N+j]= A[j*N+i];
				A[j*N+i]= temp;

			}
		}   
		printf("Tiempo en segundos para el thread %d: %f \n", tid,dwalltime() - timetick);
	}

	//Chequea los resultados
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if (i>j)
				check= check&&(A[i*N+j]==0.0);
			else
				check= check&&(A[i*N+j]== 1.0);

		}
	}   

	if(check){
		printf("Resultado correcto\n");
	}else{
		printf("Resultado erroneo\n");
	}
	free(A);
	return(0);
}
