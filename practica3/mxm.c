#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include "../utils/utils.c"

int main(int argc,char*argv[]){
    double *A,*B,*C,*D,*E;
    int i,j,k,N;
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
    B=(double*)malloc(sizeof(double)*N*N);
    C=(double*)malloc(sizeof(double)*N*N);
    D=(double*)malloc(sizeof(double)*N*N);
    E=(double*)malloc(sizeof(double)*N*N);


    for(i=0;i<N;i++){
	for(j=0;j<N;j++){
	    A[i*N+j]=1;
	    B[i+j*N]=1;
	    C[i*N+j]=1;
	}
    }   

    timetick = dwalltime();

    #pragma omp parallel sections
    {
	{
	    //Realiza la multiplicacion D= AxB
	    for(i=0;i<N;i++){
		for(j=0;j<N;j++){
		    D[i*N+j]=0;
		    for(k=0;k<N;k++){
			D[i*N+j]= D[i*N+j] + A[i*N+k]*B[k+j*N];
		    }
		}
	    }   
	}
	#pragma omp section
	{
	    //Realiza la multiplicacion E= CxB
	    for(i=0;i<N;i++){
		for(j=0;j<N;j++){
		    E[i*N+j]=0;
		    for(k=0;k<N;k++){
			E[i*N+j]= E[i*N+j] + C[i*N+k]*B[k+j*N];
		    }
		}
	    }   
	}
    }


    printf("Tiempo en segundos %f \n", dwalltime() - timetick);

    //Verifica el resultado
    for(i=0;i<N;i++){
	for(j=0;j<N;j++){
	    check=check&&(D[i*N+j]==N)&&(E[i*N+j]==N);
	}
    }   

    if(check){
	printf("Multiplicacion de matrices resultado correcto\n");
    }else{
	printf("Multiplicacion de matrices resultado erroneo\n");
    }
    free(A);
    free(B);
    free(C);
    free(D);
    free(E);
    return(0);
}
