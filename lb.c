# include <stdio.h>  // Two-dimensional lattice-Boltzmann simulation of the flow
# include <stdlib.h> // around a circular obstacle. Freely copy, modify & share.
# include <math.h>   // To use, specify the Reynolds number, simulation time and
# define pf printf   // obstacle radius. NO WARRANTY!! comp: gcc -Ofast lb.c -lm
# define f(i,a,b) for(i=a;i<b;i++) // (c) M. Meléndez Schofield, 2018. /////////
typedef float z; typedef int i;z in=0.04,w[]={4./9,1./9,1./36,1./9,1./36,1./9,1.
/36,1./9,1./36};i vx[]={0,0,1,1,1,0,-1,-1,-1},vy[]={0,1,1,0,-1,-1,-1,0,1},nx=200
,ny=500;z feq(i j,z d,z u1,z u2){z uv;uv=u1*vx[j]+u2*vy[j];return d*w[j]*(1+3*uv
+4.5*uv*uv-1.5*(u1*u1 + u2*u2));}i main(i ac,char *av[]){if(ac<4){pf("Use: %s <"
"Reynolds number> <time> <obstacle radius>\n",av[0]);return 0;}i t,j,k,nn=nx*ny,
m[nn];z Re=atof(av[1]),tm=atof(av[2]),ob=atof(av[3]),tau=3*in*ob/Re+0.5,f[9*nn],
r[nn],ux[nn],uy[nn];f(j,0,nn)m[j]=(pow(j%nx-nx/2,2)+pow(j/nx-ny/4,2)<ob*ob)?0:1;
f(j,0,nn)f(k,0,9)f[9*j+k]=feq(k,1,in*m[j],0);pf("# x \t\t y \t\t rho \t\t ux \t"
"\t uy #\n");f(t,0,tm){if(t%50==0)pf("\n# t = %d\n",t);f(j,nn-nx,nn){f[9*j+4]=f[
9*(j-nx)+4];f[9*j+5]=f[9*(j-nx)+5];f[9*j+6]=f[9*(j-nx)+6];}f(j,0,nx){ux[j]=0;uy[
j]=in;r[j]=(f[9*j]+f[9*j+3]+f[9*j+7]+2*(f[9*j+4]+f[9*j+5]+f[9*j+6]))/(1-in);f[9*
j+8]=feq(8,r[j],ux[j],uy[j])+(f[9*j+4]-feq(4,r[j],ux[j],uy[j]));f[9*j+1]=feq(1,r
[j],ux[j],uy[j])+(f[9*j+5]-feq(5,r[j],ux[j],uy[j]));f[9*j+2]=feq(2,r[j],ux[j],uy
[j])+(f[9*j+6]-feq(6,r[j],ux[j],uy[j]));}f(j,0,nn){if(m[j]){ux[j]=uy[j]=0;r[j]=f
[9*j];f(k,1,9){r[j]+=f[9*j+k];ux[j]+=f[9*j+k]*vx[k];uy[j]+=f[9*j+k]*vy[k];}ux[j]
/=r[j];uy[j]/=r[j];}}f(j,0,nn){if(m[j]){f(k,0,9){f[9*j+k]-=(f[9*j+k]-feq(k,r[j],
ux[j],uy[j]))/tau;}}}f(j,0,nn){f(k,1,5){i nbx=j%nx+vx[k],nby=j/nx+vy[k];if(nbx>=
nx)nbx=0;if(nby>=ny)continue;if(nby<0)continue;i nbj=nby*nx+nbx;z ft=f[9*j+k];f[
9*j+k]=f[9*nbj+k+4];f[9*nbj+k+4]=ft;}}f(j,0,nn){if(m[j]){f(k,1,5){z ft=f[9*j+k];
f[9*j+k]=f[9*j+k+4];f[9*j+k+4]=ft;}}if(t%50==0){if(j%nx==0)pf("\n");pf("%f\t%f"\
"\t%f\t%f\t%f\n",j%nx-.5*nx,j/nx-.5*ny,r[j],ux[j],uy[j]);}}}return 0;}//////////
