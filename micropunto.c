#include <stdio.h>    // micropunto.c: A tiny visualisation program for MD data
#include <stdlib.h>   // Use: micropunto <file>.  The file should contain x, y,
#include <X11/Xutil.h>// z and (possibly) radius and colour columns in that or-
#include <math.h>     // der. Frames are separated by a blank line. You may in-
#define c(i,a) case i:a;break; // clude comments with #,  but they are ignored.
#define f(i,a,b) for(i=a;i<b;i++) // (c) Marc Meléndez (2016) **NO WARRANTY!!**
typedef float x;typedef int n;n i,j,s,xs,ys,co,cr,cg,cb;x cf,r[5],c[12],z[3600\
00],p,L=10,th=0,ph=0,R=1;x dt(x a[],x b[]){x p=0;f(i,0,3)p+=a[i]*b[i];return p;
}void sc(){c[6]=-sin(ph);c[7]=cos(ph);c[8]=0;c[3]=-c[7]*cos(th);c[4]=c[6]*cos(\
th);c[5]=-sin(th);c[2]=4.732*L;c[0]=-c[2]*c[3];c[1]=-c[2]*c[4];c[2]*=-c[5];c[9]
=-sin(th)*cos(ph);c[10]=-sin(th)*sin(ph);c[11]=cos(th);f(i,0,360000)z[i]=2.5*L;
}n main(n ac,char*av[]){if(ac<2){printf("Use: %s <file> <L> <theta> <phi>\n",av
[0]);return 0;}if(ac>2)L=atof(av[2]);if(ac>3)th=atof(av[3]);if(ac>4)ph=atof(av[
4]);char bf[250],sb[1440000];FILE*fp=fopen(av[1],"r");Display*d=XOpenDisplay((\
char*)0);Window w=XCreateSimpleWindow(d,DefaultRootWindow(d),0,0,600,600,5,0,0)
;XStoreName(d,w,"micropunto (v. 0.2)");XEvent e;XSelectInput(d,w,KeyPressMask);
GC g=XCreateGC(d,w,0,0);XWindowAttributes wa;XGetWindowAttributes(d,w,&wa);XIm\
age*I;I=XCreateImage(d,DefaultVisual(d,0),wa.depth,ZPixmap,0,sb,600,600,32,0);\
XMapRaised(d,w);sc();while(1){if(!fgets(bf,250,fp))rewind(fp);s=sscanf(bf,"%f "
"%f %f %f %f",&r[0],&r[1],&r[2],&r[3],&r[4]);if(s>2){if(s>3)R=r[3];if(s>4)co=r[
4];else co=255;cr=co/65536;cg=(co/256)%256;cb=co%256;f(i,0,3)r[i]-=c[i];p=dt(r,
&c[3])/3.732;if(p>1){xs=(n)(300*(1+dt(r,&c[6])/p));ys=(n)(300*(1-dt(r,&c[9])/p)
);s=(n)(300*R/p);f(i,-s,s)f(j,-s,s)if(i*i+j*j<=s*s){cf=(1-(i*i+j*j)/(2.*s*s));\
if(xs+i>=0&&xs+i<600&&ys+j>=0&&ys+j<600)if(z[600*(xs+i)+(ys+j)]>p-cf){z[600*(xs
+i)+ys+j]=p-cf;cf*=(1-(p-1)/(2.5*L-1));XPutPixel(I,xs+i,ys+j,(int)(cr*cf)*65536
+(int)(cg*cf)*256+(int)(cb*cf));}}}}else if(bf[0]=='\n'){XPutImage(d,w,g,I,0,0,
0,0,600,600);XFlush(d);sc();f(i,0,600)f(j,0,600)XPutPixel(I,i,j,0);}while(XPen\
ding(d)>0){XNextEvent(d,&e);if(e.type==KeyPress){switch(e.xkey.keycode){c(35,L\
*=0.9)c(61,L/=0.9)c(113,ph-=0.1)c(114,ph+=0.1)c(111,if(th<1.56)th+=0.1)c(116,if
(th>-1.56)th-=0.1)case 9:c(24,XFreeGC(d,g);XDestroyWindow(d,w);XCloseDisplay(d)
;fclose(fp);return 0)}}}}}///// gcc micropunto.c -Ofast -lm -lX11 -march=native
