#include <stdio.h>  //  bcmc.c: (Business card) Monte Carlo -- Metro-
#include <stdlib.h> //  polis Monte Carlo simulation of a system of N
#include <math.h>   //  hard spheres  (periodic boundary conditions).
#define f(i,a,b) for(i=a;i<b;i++) // (c) M. Meléndez Schofield, 2016.
static unsigned int z=362436069,w=521288629,N,i;typedef float x; ////
#define UI (((z=36969*(z&65535)+(z>>16))<<16)+((w=18000*(w&65535)+(w\
>>16))&65535)) // Args: Num. spheres, vol fraction, samples and step.
void pbc(x ra[],x L){int j;f(j,0,3){if(ra[j]<-.5*L)ra[j]+=L;else if(\
ra[j]>.5*L)ra[j]-=L;}}int vm(x r[],x ra[],x L){int j,k;x d[3],r2;f(j,
0,N)if(j!=i){r2=0;f(k,0,3)d[k]=r[3*j+k]-ra[k];pbc(d,L);f(k,0,3)r2+=d[
k]*d[k];if(r2<4)return 0;}return 1;}void main(int c,char*av[]){if(c<5
){printf("Use: %s <N> <phi> <ns> <dx>\n",av[0]);return;}N=atoi(av[1])
;int j,k,m,ns,nx=ceil(pow(N/4.,1./3)),L,ts=0;x r[3*N],ra[3],dx=atof(\
av[4]),l=2.55888*pow(atof(av[2]),-1./3);L=nx*l;f(i,0,nx)f(j,0,nx)f(k,
0,nx)f(m,0,4)if((ns=4*(i*nx*nx+j*nx+k)+m)<N){r[3*ns]=-.5*L+l*((((ns/4
)%(nx*nx))%nx)+(m%3==0?0:.5));r[3*ns+1]=-.5*L+l*((((ns/4)%(nx*nx))/nx
)+(m%2==1?.5:0));r[3*ns+2]=-.5*L+l*(((ns/4)/(nx*nx))+(m>1?.5:0));}f(\
ns,0,atoi(av[3])){i=UI%N;f(j,0,3)ra[j]=r[3*i+j]+(UI*2.32830643708e-10
*2-1)*dx;pbc(ra,L);if(vm(r,ra,L))f(j,0,3)r[3*i+j]=ra[j];if(ns>=ts){f(
i,0,N){f(j,0,3)printf("%f""\t",r[3*i+j]);printf("1\n");}printf("\n");
ts+=N;}}}// NO WARRANTY!! gcc bcmc.c -o bcmc -lm -Ofast -march=native
