#include <stdio.h>  //  bcmd.c: (Business card) Molecular Dynamics --
#include <stdlib.h> //  NVE simulation of a Lennard-Jones system with
#include <math.h>   //  periodic boundary conditions. *NO WARRANTY!!*
#define f(i,a,b) for(i=a;i<b;i++) // (c) M. Meléndez Schofield, 2016.
#define UM if(z<5){printf("Use: %s <N> <V> <E> <t>\n",av[0]);return;}
#define D r2=0;f(k,0,3){r[k]=q[3*j+k]-q[3*i+k];if(fabs(r[k])>L/2.0)r\
[k]-=L*r[k]/fabs(r[k]);r2+=r[k]*r[k];}i6=1/pow(r2,3);// Begin program
typedef float x;typedef int n;typedef void v;n i,j,k,N,nc;x t,L,r[3],
r2,i6,i8,fm,E,dt=0.001,ts=0,sm=100;v F(x q[],x f[]){f(i,0,3*N)f[i]=0;
f(i,0,N-1){f(j,i+1,N){D i8=i6/r2;fm=24*i8*(1-2*i6); f(k,0,3){f[3*i+k]
+=fm*r[k];f[3*j+k]-=fm*r[k];}}}} v e(x q[],x p[]){E=0;f(i,0,N)f(k,0,3
)E+=0.5*pow(p[3*i+k],2); f(i,0,N-1){f(j,i+1,N){D E+=4*i6*(i6-1);}}} v
pbc(x q[]){f(i,0,N)f(k,0,3) if(q[3*i+k]>L || q[3*i+k]<0) q[3*i+k]-=L*
floor(q[3*i+k]/L);}v main(n z,char *av[]){UM N=atoi(av[1]); x q[3*N],
p[3*N],f[3*N];L=pow(atof(av[2]),1/3.0);nc=ceil(pow(N,1/3.0));f(i,0,N)
{q[3*i]=L*(i%(int)nc)/nc;q[3*i+1]=L*((i%(int)(nc*nc))/(int)nc)/nc;q[3
*i+2]=L*(i/(int)(nc*nc))/nc;}f(i,0,3*N)p[i]=0;e(q,p);E=atof(av[3])-E;
f(i,0,3*N) p[i]=pow(-1,i)*sqrt(2*E/(3.0*N));F(q,f);f(t,0,atof(av[4])/
dt){f(i,0,N)f(k,0,3){p[3*i+k]+=0.5*f[3*i+k]*dt;q[3*i+k]+=p[3*i+k]*dt;
} pbc(q); F(q,f);f(i,0,N)f(k,0,3)p[3*i+k]+=0.5*f[3*i+k]*dt; if(t>ts){
printf("#\n");f(i,0,N){f(k,0,3)printf("%f\t",q[3*i+k]);printf("0.5\t"
);printf("1\n");}ts+=sm;}}} // gcc -o md bcmd.c -O3 -march=native -lm
