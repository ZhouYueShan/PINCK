#include "stdio.h"  
#include "string.h"  
#include "mpi.h"  
  
int main(int agc,char *agv[])  
{  
  
      
    int comm_size;  
    int my_rank;  
  
    MPI_Init(&agc,&agv);  
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);  
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);  
    for(int i=0;i<5;i++)  
        printf("process %d: %d\n",my_rank,i);  
    printf("waiting.....\n");  
    MPI_Barrier(MPI_COMM_WORLD);  
    for(int i=5;i<10;i++)  
        printf("process %d: %d\n",my_rank,i);  
      
    MPI_Finalize();  
    return 0;  
} 