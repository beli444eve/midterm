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
	
	//�ѥ���k�A�v�@��Ʀr���J��ثe�w�ƧǪ��}�C���C
	//�ݱN�j�q�Ʀr���k���A�H�˥X�Ŷ����J�Ʀr�C
	
	int temp,index,k,print;
	
	for(i=0;i<N;++i)
	{
		temp=v[i];
		for(j=0;j<i;++j)    	//����m 
		{	
			if(v[j]>temp)
			{
				index=j;
				break;
			}
		}
		
		for(k=i;k>j;--k){		//��m���᪺�Ʀr���Ჾ�@�� 
			v[k]=v[k-1];			
		}
		
		v[j]=temp;				//��Ʀr��쨺�Ӧ�m 
		
		for(print=0;print<N;++print)
		{
			printf("%d,",v[print]);
			
		}
		printf("\n");
		
	}
	
	for(i=0;i<N;++i)
	{
		printf("%d,",v[i]);
	}
	
	
	
	return 1;
}
