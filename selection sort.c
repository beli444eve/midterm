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
	//掃描一遍所有數字，找到最小值，挪至陣列左端。
	//遞迴處理尚未排序的 N-1 個元素。
	
	int min,temp;
	
	for(i=0;i<N;++i)		//遞迴N-1次 
	{
		min=i;
		
		for(j=i;j<N;++j)   	//找最小值 
		{	                
			if(v[min]>v[j])
				min=j;		
		}
		
		temp=v[min];     	//交換 
		v[min]=v[i];
		v[i]=temp;		
	}
	
	for(i=0;i<N;++i)
	{
		printf("%d,",v[i]);
	}
	
	
	
	return 1;
}
