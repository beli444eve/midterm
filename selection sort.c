#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i,j, N, *v;
	srand(time(0));
	N=10;
	v=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;++i)
	{
		v[i]=rand()%100;
		printf("%d,",v[i]);
	}
	printf("\n");
	
	//selection sort
	//���y�@�M�Ҧ��Ʀr�A���̤p�ȡA���ܰ}�C���ݡC
	//���j�B�z�|���ƧǪ� N-1 �Ӥ����C
	
	int min,temp;
	
	for(i=0;i<N;++i)		//���jN-1�� 
	{
		min=i;
		
		for(j=i;j<N;++j)   	//��̤p�� 
		{	                
			if(v[min]>v[j])
				min=j;		
		}
		
		temp=v[min];     	//�洫 
		v[min]=v[i];
		v[i]=temp;		
	}
	
	for(i=0;i<N;++i)
	{
		printf("%d,",v[i]);
	}
	
	
	
	return 1;
}
