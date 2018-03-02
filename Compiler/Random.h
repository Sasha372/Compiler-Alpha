#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include <time.h>
int vvvv = 0;

int random(int a, int b)
{
	b = b + 1;
    int r = a - 1;
    int i = 0;
	while (r<a)
	{
        srand(time(0) + vvvv + i);
	    r = rand()%b;
	    i += 1;
	    vvvv = vvvv + 1;
	}
	return r;
}

int randomizer(int a, int b, int c, int d, int e, int f, int g,int h, int i,int j)
{
    int s = random(1, 10);
    if(s==1){return a;}
    if(s==2){return b;}
    if(s==3){return c;}
    if(s==4){return d;}
    if(s==5){return e;}
    if(s==6){return f;}
    if(s==7){return g;}
    if(s==8){return h;}
    if(s==9){return i;}
    if(s==10){return j;}
}

int gen(int h)
{
    int Ns = random(1, 100);
    if(Ns<h){return 1;}else{return 0;}
}

#endif // RANDOM_H_INCLUDED
