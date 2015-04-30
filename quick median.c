#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *v;

int main()
{
	int i,j, N;
	srand(time(0));
	N=11;
	v=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;++i)
	{
		v[i]=rand()%100;
		printf("%d,",v[i]);
	}
	printf("\n");
	
    //隨機選一個數 小的一邊大的一邊 
    //若不是中位數，則遞迴  000
	
	    
    int L,temp;
    L=0;
	i=0;	
	for (i=0;i<N;++i)
    {
    	if (v[i]<=v[N-1])
		{
        	temp = v[i];
			v[i] = v[L];
			v[L] = temp;
			L=L+1;
					}
		
	}
	printf("%d",L);
	return 1;
	
}






/*	for(i=0;i<N;++i)
	{
		printf("%d,",v[i]);
	}
	
	//printf("%d,",N/2);
	
	
	return 1;
}

void quicksort(p,r,N){
	int q;
	if(p<r){
		q=partition(p,r);
		if(q<=N/2)
			quicksort(q+1,r,N);
		else if(q>(N+1)/2)
			quicksort(p,q-1,N);
		else
			printf("%d,",q);
	}
}

int partition(p,r){
	int x,i,j,temp;
	x=v[r];
	i=p-1;
	for(j=p;j<=r-1;j++){
		if(v[i]<=x){
			i=i+1;
			//exchange A[i],A[j]
			temp=v[j];
			v[j]=v[i];
			v[i]=temp;
		}
	}
	//exchange A[i+1],A[r]
	temp=v[r];
	v[r]=v[i+1];
	v[i+1]=temp;
	
	return i+1;
} */
