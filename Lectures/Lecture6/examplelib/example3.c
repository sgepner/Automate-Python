#include <stdlib.h>
#include <time.h>

void manipuator(double *pd)
{
    srand(time(NULL));
    *pd = (double)rand() / RAND_MAX;
}