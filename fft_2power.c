#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	//y_k = sum(x_n * w_N^{-kn},n=0..N-1)
	//w-n = cos(2*pi/N) + isin(2*pi/N)
	int k,n,N;
	double *x_r, *x_i, *y_r, *y_i, w_r, w_i;
	clock_t t1, t2;
		
	printf("please input N=");
	scanf("%d",&N);
	printf("N=%d\n",N);
		
	x_r = (double *) malloc(N*sizeof(double));
	x_i = (double *) malloc(N*sizeof(double));
	y_r = (double *) malloc(N*sizeof(double));	
	y_i = (double *) malloc(N*sizeof(double));
	for(n=0;n<N;++n)	
	{
		x_r[n] = n;
		x_i[n] = 0;
	}
	//y_k = sum(x_n * w_N^{-kn},n=0..N-1)
	//w-n = cos(2*pi/N) + isin(2*pi/N)
/*	t1 = clock();
	for(k=0;k<N;++k)	
	{
		y_r[k] = 0.0;
		y_i[k] = 0.0;
		for(n=0;n<N;++n)
		{
			//w^{-kn}
			//w^{-kn} = cos(-kn*2pi/N) + isin(-kn*2pi/N)
			w_r = cos(-k*n*2*M_PI/N);
			w_i = sin(-k*n*2*M_PI/N);
			y_r[k] = y_r[k] + x_r[n]*w_r - x_i[n]*w_i;
			y_i[k] = y_i[k] + x_r[n]*w_i + x_i[n]*w_r;
			
	
		}
	
		
	}	
	t2 = clock();
	printf("%f secs\n",1.0*(t2-t1)/CLOCKS_PER_SEC);
	system("pause");
	for(n=0;n<N;++n)
	{
		printf("%d : %f + %f i\n",n,y_r[n],y_i[n]);
	}
	//§Öªº 
	for(n=0;n<N;++n)	
	{
		x_r[n] = n;
		x_i[n] = 0;
	}*/
	FFT(x_r, x_i, y_r, y_i, N);
	
	for(n=0;n<N;++n)
	{
		printf("%d : %f + %f i\n",n,y_r[n],y_i[n]);
	}
	return 0;		
}

int FFT(double *x_r, double *x_i, double *y_r, double *y_i,int N)
{
	printf("%d\n",N);	
	system("pause");
	if(N==1)
	{
		y_r[0]=x_r[0];
		y_i[0]=x_i[0];
		return 0;
	}
	int k,n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i;
	
	u_r = (double *)malloc(N*sizeof(double));
	u_i = (double *)malloc(N*sizeof(double));
	v_r = (double *)malloc(N*sizeof(double));
	v_i = (double *)malloc(N*sizeof(double));
	for(n=0;n<N/2;++n)
	{
		u_r[n] = x_r[2*n];
		u_i[n] = x_i[2*n];
		u_r[n+N/2] = x_r[2*n+1];
		u_i[n+N/2] = x_i[2*n+1];
	}
	FFT(u_r, u_i, v_r, v_i, N/2);
	FFT(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	for(k=0;k<N/2;++k)
	{
		w_r=cos(-k*2*M_PI/N);
		w_i=sin(-k*2*M_PI/N);
		printf("%f %f\n",w_r,w_i);
		y_r[k]=v_r[k]+w_r*v_r[k+N/2]-w_i*v_i[k+N/2];
		y_i[k]=v_i[k]+w_r*v_i[k+N/2]+w_i*v_r[k+N/2];
		y_r[k+N/2]=v_r[k]-(w_r*v_r[k+N/2]-w_i*v_i[k+N/2]);
		y_i[k+N/2]=v_i[k]-(w_r*v_i[k+N/2]+w_i*v_r[k+N/2]);
	}
		return 0;
}

