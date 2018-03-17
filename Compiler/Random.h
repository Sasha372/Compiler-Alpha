#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include <time.h>
#include <random>

int random(int a, int b)
{
	b = b + 1;
    int r = a - 1;
    int i = 0;
	while (r<a)
	{
        srand(time(0) + i);
	    r = rand() % b;
	    i += 1;
	    //vvvv = vvvv + 1;
	}
	return r;
}

int randomizer(std::vector<int> option)
{
    int s = random(1, option.size());
	return option[s];
}

int gen(int h)
{
    int Ns = random(1, 100);
    if(Ns<h){return 1;}else{return 0;}
}

#endif // RANDOM_H_INCLUDED
