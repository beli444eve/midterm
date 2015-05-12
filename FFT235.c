#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
int FFT2(double *x_r, double *x_i, double *y_r, double *y_i,int N);
int FFT3(double *x_r, double *x_i, double *y_r, double *y_i,int N);
int FFT5(double *x_r, double *x_i, double *y_r, double *y_i,int N);
int main()
{
	//y_k = sum(x_n * w_N^{-kn},n=0..N-1)
	//w-n = cos(2*pi/N) + isin(2*pi/N)
	int k,n,N;
	double *x_r, *x_i, *y_r, *y_i, w_r, w_i;
	clock_t t1, t2;
	printf("Please input N=");
	scanf("%d", &N);
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
    t1 = clock();
    if(N%2==0)
    {
    	FFT2(x_r, x_i, y_r, y_i, N);
	}
    else
    {
    	if(N%3==0)
    	{
    		FFT3(x_r, x_i, y_r, y_i, N);
		}
		else
		{
			FFT5(x_r, x_i, y_r, y_i, N);
		}
	}
	t2 = clock();
	printf("%f secs\n",1.0*(t2-t1)/CLOCKS_PER_SEC);
	system("pause");
	
	for(n=0;n<N;++n)
	{
		printf("%d : %f + %f i\n",n,y_r[n],y_i[n]);
	}
	return 0;		
}
int Generate_N(int p, int q, int r)
{
	int i, N = 1;
	// N = 2^p 3^q 5^r
	for(i=0;i<p;++i) N = N * 2;
	for(i=0;i<q;++i) N = N * 3;
	for(i=0;i<r;++i) N = N * 5;	
	
	return N;
}
int FFT2(double *x_r, double *x_i, double *y_r, double *y_i,int N)
{
	//printf("%d\n",N);	
	//system("pause");
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
	if(n%2==0)
	{
		FFT2(u_r, u_i, v_r, v_i, N/2);
		FFT2(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	}
	else
	{
		if(n%3==0)
		{
			FFT3(u_r, u_i, v_r, v_i, N/2);
			FFT3(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);		
		}
		else
		{
			FFT5(u_r, u_i, v_r, v_i, N/2);
			FFT5(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
		}
	}
	for(k=0;k<N/2;++k)
	{
		w_r=cos(-k*2*M_PI/N);
		w_i=sin(-k*2*M_PI/N);
		//printf("%f %f\n",w_r,w_i);
		y_r[k]=v_r[k]+w_r*v_r[k+N/2]-w_i*v_i[k+N/2];
		y_i[k]=v_i[k]+w_r*v_i[k+N/2]+w_i*v_r[k+N/2];
		y_r[k+N/2]=v_r[k]-(w_r*v_r[k+N/2]-w_i*v_i[k+N/2]);
		y_i[k+N/2]=v_i[k]-(w_r*v_i[k+N/2]+w_i*v_r[k+N/2]);
	}
		return 0;
}

int FFT3(double *x_r, double *x_i, double *y_r, double *y_i,int N)
{
//	printf("%d\n",N);	
//	system("pause");
	if(N==1)
	{
		y_r[0]=x_r[0];
		y_i[0]=x_i[0];
		return 0;
	}
	int k,n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i,w2r,w2i;
	
	u_r = (double *)malloc(N*sizeof(double));
	u_i = (double *)malloc(N*sizeof(double));
	v_r = (double *)malloc(N*sizeof(double));
	v_i = (double *)malloc(N*sizeof(double));
	for(n=0;n<N/3;++n)
	{
		u_r[n] = x_r[3*n];
		u_i[n] = x_i[3*n];
		u_r[n+N/3] = x_r[3*n+1];
		u_i[n+N/3] = x_i[3*n+1];
		u_r[n+2*N/3] = x_r[3*n+2];
		u_i[n+2*N/3] = x_i[3*n+2];

	}
	if(n%2==0)
	{
		FFT2(u_r, u_i, v_r, v_i, N/3);
		FFT2(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
		FFT2(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);
	}
	else
	{
		if(n%3==0)
		{
			FFT3(u_r, u_i, v_r, v_i, N/3);
			FFT3(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
			FFT3(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);	
		}
		else
		{
			FFT5(u_r, u_i, v_r, v_i, N/3);
			FFT5(u_r+N/3, u_i+N/3, v_r+N/3, v_i+N/3, N/3);
			FFT5(u_r+2*N/3, u_i+2*N/3, v_r+2*N/3, v_i+2*N/3, N/3);
		}
		
	}
	for(k=0;k<N/3;++k)
	{
		w_r=cos(-k*2*M_PI/N);
		w_i=sin(-k*2*M_PI/N);
		w2r=cos(-2*k*2*M_PI/N);
		w2i=sin(-2*k*2*M_PI/N);
//		printf("%f %f %f %f\n",w_r,w_i,w2r,w2i);
		y_r[k]=v_r[k]+w_r*v_r[k+N/3]-w_i*v_i[k+N/3]+w2r*v_r[k+2*N/3]-w2i*v_i[k+2*N/3];
		y_i[k]=v_i[k]+w_r*v_i[k+N/3]+w_i*v_r[k+N/3]+w2r*v_i[k+2*N/3]+w2i*v_r[k+2*N/3];
		y_r[k+N/3]=v_r[k]
		           +(w_r*v_r[k+N/3]-w_i*v_i[k+N/3])*cos(-2*M_PI/3)-(w_r*v_i[k+N/3]+w_i*v_r[k+N/3])*sin(-2*M_PI/3)
		           +(w2r*v_r[k+2*N/3]-w2i*v_i[k+2*N/3])*cos(-4*M_PI/3)-(w2r*v_i[k+2*N/3]+w2i*v_r[k+2*N/3])*sin(-4*M_PI/3);
		y_i[k+N/3]=v_i[k]
		          +(w_r*v_r[k+N/3]-w_i*v_i[k+N/3])*sin(-2*M_PI/3)+(w_r*v_i[k+N/3]+w_i*v_r[k+N/3])*cos(-2*M_PI/3)
				  +(w2r*v_r[k+2*N/3]-w2i*v_i[k+2*N/3])*sin(-4*M_PI/3)+(w2r*v_i[k+2*N/3]+w2i*v_r[k+2*N/3])*cos(-4*M_PI/3);
		y_r[k+2*N/3]=v_r[k]
		           +(w_r*v_r[k+N/3]-w_i*v_i[k+N/3])*cos(-4*M_PI/3)-(w_r*v_i[k+N/3]+w_i*v_r[k+N/3])*sin(-4*M_PI/3)
		           +(w2r*v_r[k+2*N/3]-w2i*v_i[k+2*N/3])*cos(-2*M_PI/3)-(w2r*v_i[k+2*N/3]+w2i*v_r[k+2*N/3])*sin(-2*M_PI/3);
				   
		y_i[k+2*N/3]=v_i[k]
		            +(w_r*v_r[k+N/3]-w_i*v_i[k+N/3])*sin(-4*M_PI/3)+(w_r*v_i[k+N/3]+w_i*v_r[k+N/3])*cos(-4*M_PI/3)
				    +(w2r*v_r[k+2*N/3]-w2i*v_i[k+2*N/3])*sin(-2*M_PI/3)+(w2r*v_i[k+2*N/3]+w2i*v_r[k+2*N/3])*cos(-2*M_PI/3);
		}
		return 0;
}

int FFT5(double *x_r, double *x_i, double *y_r, double *y_i,int N)
{
	//printf("%d\n",N);	
	//system("pause");
	if(N==1)
	{
		y_r[0]=x_r[0];
		y_i[0]=x_i[0];
		return 0;
	}
	int k,n;
	double *u_r, *u_i, *v_r, *v_i, w_r, w_i,w2r,w2i,w3r,w3i,w4r,w4i,
           	w5_r,w5_i,w52r,w52i,w53r,w53i,w54r,w54i ;
	
	u_r = (double *)malloc(N*sizeof(double));
	u_i = (double *)malloc(N*sizeof(double));
	v_r = (double *)malloc(N*sizeof(double));
	v_i = (double *)malloc(N*sizeof(double));
	for(n=0;n<N/5;++n)
	{
		u_r[n] = x_r[5*n];
		u_i[n] = x_i[5*n];
		u_r[n+N/5] = x_r[5*n+1];
		u_i[n+N/5] = x_i[5*n+1];
		u_r[n+2*N/5] = x_r[5*n+2];
		u_i[n+2*N/5] = x_i[5*n+2];
		u_r[n+3*N/5] = x_r[5*n+3];
		u_i[n+3*N/5] = x_i[5*n+3];
  		u_r[n+4*N/5] = x_r[5*n+4];
		u_i[n+4*N/5] = x_i[5*n+4];
	}
		if(n%2==0)
	{
		FFT2(u_r, u_i, v_r, v_i, N/5);
		FFT2(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
		FFT2(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
		FFT2(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
		FFT2(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
	}
	else
	{
		if(n%3==0)
		{
			FFT3(u_r, u_i, v_r, v_i, N/5);
			FFT3(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
			FFT3(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
			FFT3(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
			FFT3(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
		}
		else
		{
			FFT5(u_r, u_i, v_r, v_i, N/5);
			FFT5(u_r+N/5, u_i+N/5, v_r+N/5, v_i+N/5, N/5);
			FFT5(u_r+2*N/5, u_i+2*N/5, v_r+2*N/5, v_i+2*N/5, N/5);
			FFT5(u_r+3*N/5, u_i+3*N/5, v_r+3*N/5, v_i+3*N/5, N/5);
			FFT5(u_r+4*N/5, u_i+4*N/5, v_r+4*N/5, v_i+4*N/5, N/5);
		}
		
	}
	
	for(k=0;k<N/5;++k)
	{
        w_r=cos(-k*2*M_PI/N);
		w_i=sin(-k*2*M_PI/N);
		w2r=cos(-2*k*2*M_PI/N);
		w2i=sin(-2*k*2*M_PI/N);
		w3r=cos(-3*k*2*M_PI/N);
		w3i=sin(-3*k*2*M_PI/N);
		w4r=cos(-4*k*2*M_PI/N);
		w4i=sin(-4*k*2*M_PI/N);
        w5_r=cos(-2*M_PI/5);
        w5_i=sin(-2*M_PI/5);
        w52r=cos(-2*2*M_PI/5);
        w52i=sin(-2*2*M_PI/5);
        w53r=cos(-3*2*M_PI/5);
        w53i=sin(-3*2*M_PI/5);
        w54r=cos(-4*2*M_PI/5);
        w54i=sin(-4*2*M_PI/5);
        
		y_r[k]=v_r[k]
		       +w_r*v_r[k+N/5]-w_i*v_i[k+N/5]
			   +w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5]
               +w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5]
	           +w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5];
	    y_i[k]=v_i[k]
		       +w_r*v_i[k+N/5]+w_i*v_r[k+N/5]
			   +w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5]
	           +w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5]
	           +w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5];
	    
		y_r[k+N/5]=v_r[k]
		           +w5_r*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
                   -w5_i*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])	
				   +w52r*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])          
				   -w52i*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])   
				   +w53r*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				   -w53i*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
	               +w54r*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5])
	               -w54i*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5]);
	    
		y_i[k+N/5]=v_i[k]
		           +w5_r*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])  
		           +w5_i*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
		           +w52r*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])
		           +w52i*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])
	               +w53r*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
                   +w53i*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				   +w54r*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5])	
	               +w54i*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5]);
	   
	    y_r[k+2*N/5]=v_r[k]
		            +w52r*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
                    -w52i*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])	
				    +w54r*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])          
				    -w54i*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])   
				    +w5_r*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    -w5_i*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
	                +w53r*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5])
	                -w53i*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5]);             
	               
	    y_i[k+2*N/5]=v_i[k]
	                +w52r*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])  
		            +w52i*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
		            +w54r*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])
		            +w54i*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])
	                +w5_r*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
                    +w5_i*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    +w53r*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5])	
	                +w53i*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5]);
	               
	    y_r[k+3*N/5]=v_r[k]
		            +w53r*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
                    -w53i*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])	
				    +w5_r*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])          
				    -w5_i*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])   
				    +w54r*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    -w54i*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
	                +w52r*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5])
	                -w52i*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5]);
	               
	    y_i[k+3*N/5]=v_i[k]
	                +w53r*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])  
		            +w53i*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
		            +w5_r*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])
		            +w5_i*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])
	                +w54r*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
                    +w54i*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    +w52r*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5])	
	                +w52i*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5]);           
	    
		y_r[k+4*N/5]=v_r[k]
		            +w54r*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
                    -w54i*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])	
				    +w53r*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])          
				    -w53i*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])   
				    +w52r*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    -w52i*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
	                +w5_r*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5])
	                -w5_i*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5]);           
	            
	    y_i[k+4*N/5]=v_i[k]
	                +w54r*(w_r*v_i[k+N/5]+w_i*v_r[k+N/5])  
		            +w54i*(w_r*v_r[k+N/5]-w_i*v_i[k+N/5])
		            +w53r*(w2r*v_i[k+2*N/5]+w2i*v_r[k+2*N/5])
		            +w53i*(w2r*v_r[k+2*N/5]-w2i*v_i[k+2*N/5])
	                +w52r*(w3r*v_i[k+3*N/5]+w3i*v_r[k+3*N/5])
                    +w52i*(w3r*v_r[k+3*N/5]-w3i*v_i[k+3*N/5])
				    +w5_r*(w4r*v_i[k+4*N/5]+w4i*v_r[k+4*N/5])	
	                +w5_i*(w4r*v_r[k+4*N/5]-w4i*v_i[k+4*N/5]);            
	}
	   return 0;
}
	

