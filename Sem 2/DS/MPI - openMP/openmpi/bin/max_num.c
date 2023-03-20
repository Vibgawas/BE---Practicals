	#include <stdio.h>
	#include "mpi.h"

	int main(int argc, char* argv[])
	{
		int rank, size;
		//int num[20]; //N=20, n=4

		MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		
		//for(int i=0;i<20;i++)
		//	num[i]=i+1;
			
		int num[]={10,5,15,2,3,8,20,100,50,42,16,5,55,24,7,3,42,80,70,90};

		if(rank == 0){
			int s[4];
			printf("Distribution at rank %d \n", rank);
			for(int i=1;i<4;i++)
				MPI_Send(&num[i*5], 5, MPI_INT, i, 1, MPI_COMM_WORLD); //N/n i.e. 20/4=5
			
			int max=0, local_max=0;
			for(int i=0;i<5;i++)
			{
				if (num[i]>local_max){
					local_max=num[i];
				}
				//local_sum=local_sum+num[i];
			}
			
			for(int i=1;i<4;i++)
			{
				MPI_Recv(&s[i], 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			
			printf("local max at rank %d is %d\n", rank,local_max);
			max=local_max;
			
			for(int i=1;i<4;i++)
			{
				if(s[i]>max){
					max=s[i];
				}
			}
			//sum=sum+s[i];
			
			printf("final max_num = %d\n\n",max);
		}

		else
		{
			int k[5];
			MPI_Recv(k, 5, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			int local_max=0;
			
			for(int i=0;i<5;i++)
			{
			    if(k[i]>local_max){
			    	local_max=k[i];
			    }
				//local_sum=local_sum+k[i];
			}
			
			printf("local max at rank %d is %d\n", rank, local_max);
			MPI_Send(&local_max, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

		}
		MPI_Finalize();

	return 0;
	}

