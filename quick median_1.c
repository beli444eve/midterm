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
    //若不是中位數，則遞迴  
    
    quicksort(0,10,N);
	printf("%d,",v[(N+1)/2-1]);
		
	return 1;
}

void quicksort(p,r,N){
	int q;
	if(p<r){
		q=partition(p,r);
		quicksort(q+1,r,N);
		quicksort(p,q-1,N);
	}
}

int partition(p,r){
	int x,i,j,temp;
	x=v[r];
	i=p-1;
	for(j=p;j<=r-1;j++){
		if(v[j]<=x){
			i=i+1;
			//exchange v[i],v[j]
			temp=v[j];
			v[j]=v[i];
			v[i]=temp;
		}
	}
	//exchange v[i+1],v[r]
	temp=v[r];
	v[r]=v[i+1];
	v[i+1]=temp;
	
	return (i+1);
}
