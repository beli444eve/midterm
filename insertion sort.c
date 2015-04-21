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
	
	//由左到右，逐一把數字插入到目前已排序的陣列當中。
	//需將大量數字往右挪，以騰出空間插入數字。
	
	int temp,index,k,print;
	
	for(i=0;i<N;++i)
	{
		temp=v[i];
		for(j=0;j<i;++j)    	//找到位置 
		{	
			if(v[j]>temp)
			{
				index=j;
				break;
			}
		}
		
		for(k=i;k>j;--k){		//位置之後的數字往後移一格 
			v[k]=v[k-1];			
		}
		
		v[j]=temp;				//把數字放到那個位置 
		
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
