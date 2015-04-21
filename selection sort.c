#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, N, *v;
	srand(time(0));
	N=10;
	v=(int*)malloc(N*sizeof(int));
	for(i=0;i<N;++i)
	{
		v[i]=rand()%100;
		printf("%d,",v[i]);
	}
	printf("\n");
	return 1;
}
