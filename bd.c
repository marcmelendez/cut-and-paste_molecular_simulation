#include <stdio.h>  // bcbd.c -- (Business card) Brownian Dynamics --
#include <stdlib.h> // Diffusion of independent Brownian particles in
#include <math.h>   // a force field defined as F. Program arguments:
#define F 0         // N: number of particles, rho: density, D0: dif-
#define f(i,a,b) for(i=a;i<b;i++) // fusion coefficient, t: time. Use
static unsigned int z=362436069,w=521288629; // gcc -lm -Ofast bcbd.c
#define URN (((((z=36969*(z&65535)+(z>>16))<<16)+((w=18000*(w&65535)\
+(w>>16))&65535))*2.32830643708e-10)*2-1) // (c) Marc Meléndez, 2016.
void main(int c,char* av[]){if(c<5){printf("Use: %s <N> <rho> <D0> <"
"t>\n",av[0]);return;}int i,j,N=atoi(av[1]),smp=100;float t,r[3*N],f[
3*N],r2,R,u1,u2,s,D0=atof(av[3]),dt=0.001,ts=0;R=pow(.238732415*N/at\
of(av[2]),1./3);f(i,0,N){do{r2=0;f(j,0,3){r[3*i+j]=URN*R;r2+=r[3*i+j]
*r[3*i+j];}}while(r2>R*R);}f(t,0,atof(av[4])/0.001){f(i,0,N){f(j,0,3)
{do{u1=URN;u2=URN;s=u1*u1+u2*u2;}while(s>=1);r[3*i+j]+=D0*F*dt+sqrt(2
*D0*dt)*u1*sqrt(-2*log(s)/s);}}if(t>ts){f(i,0,N)printf("%f\t%f\t%f\n"
,r[3*i],r[3*i+1],r[3*i+2]);printf("\n");ts+=smp;}}}// *NO WARRANTY!!*
