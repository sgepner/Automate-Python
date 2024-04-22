#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

double nrm(double* u, double *unew, int size)
{
  double v = fabs(u[0] - unew[0]);
  for(int i=1; i< size; ++i)
  {
    v += fabs(u[i] - unew[i]);
  }
  return v;
}

// First order, backward FD
void explicit_euler_bd_1(double *u, double *un, int nx, double c, double dt, double dx)
{
  printf("%p %p\n", u, un);
  double c1 = c * dt / dx;
  double *tmp;
  
  // 0
  un[0] = u[0] - c1 * ( u[0] - u[nx-1]);
  for(int i=1; i< nx; ++i)
    un[i] = u[i] - c1 * ( u[i] - u[i-1]);
    
  tmp = u;
  u = un;
  un = tmp;
}

// Second order, backward FD
void explicit_euler_bd_2(double *u, double *un, int nx, double c, double dt, double dx)
{
  double c1 = c * dt / dx;
  double *tmp;
  // 0
  un[0] = u[0] - c1 * ( 3.0/2.0*u[0] - 2*u[nx-1-1] +1.0/2.0*u[nx-1-2]);
  // 1
  un[1] = u[1] - c1 * ( 3.0/2.0*u[1] - 2*u[0] +1.0/2.0*u[nx-1-1]);
  for(int i=2; i< nx; ++i)
    un[i] = u[i] - c1 * ( 3.0/2.0*u[i] - 2*u[i-1] +1.0/2.0*u[i-2]);

  tmp = u;
  u = un;
  un = tmp;
}

// Second order, central FD
void implicit_euler_cn_2(double *u, double *b, double *un, int size, double c,
                         double dt, double dx, int N, double eps)
{
  int nx = size;
  double c1 = 0.5 * c * dt / dx;
  double err;
  double *tmp;
  
  // Jacobi iterations
  for(int i=0; i<N; ++i)
  {
    // 1/a_ii(u_i - sum a_ij uj)
    // 0
    un[0] = b[0] - (-c1 * u[nx-1] + c1*u[1]);
    // nx-1
    un[nx-1] = b[nx-1] - (- c1 * u[nx-2] + c1*u[0] );
    for(int i=1; i<nx-1; ++i)
      un[i] = b[i] - (-c1 * u[i-1] + c1 * u[i+1]);

    err = nrm(u, un, nx);
    
    if(err < eps)
    {
      tmp = u;
      u = un;
      un = tmp;
      return;
    }
    tmp = u;
    u = un;
    un = tmp;
  }
  printf("Failed to conerge in %d with err %lf \n", N, err);
}

void dump_solution(double *x, double *u, int nx, int idx)
{
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "data_%d.csv", idx);
  FILE *f = fopen(buffer, "w");
  for(int i=0; i< nx; ++i)
  {
    //printf("%lf, %lf \n", x[i], u[i]);
    fprintf(f, "%lf, %lf \n", x[i], u[i]);
  }
  fclose(f);
}

void solve_advection(int nx, int nt, double dt)
{
  int c = 1.0;
  double dx = 1.0 / ( nx - 1 );
  dt = 0.4*2*dx/c;
  double t = 0;
  double *x = (double *)malloc(nx * sizeof(double));
  double *u = (double *)malloc(nx * sizeof(double));
  // initial condition
  for(int i=0; i< nx; ++i)
  {
    x[i]=i*dx;
    u[i]=0.0;
    if( 0.4 <= x[i] && x[i] <= 0.6 )
    {
      u[i] = 0.5*(-cos(10*M_PI*x[i])+1.0);
    }
  }  
  double * b = (double *)malloc(nx * sizeof(double));
  memcpy(b,u,nx * sizeof(double));
  double * un= (double *)malloc(nx * sizeof(double));
  memcpy(un,u,nx * sizeof(double));

  dump_solution(x, u, nx, 0);
  for(int i=1; i<1000; ++i)
  {
    t = i*dt;
    implicit_euler_cn_2(u, b, un, nx, c, dt, dx, nx, 1.0e-6);
    memcpy(b,u,nx * sizeof(double));
    if(i % 100 == 0)
     dump_solution(x, u, nx, i);
  }
  free(x);
  free(u);
  free(b);
  free(un);  
}

int main()
{
  int size = 1000;
  solve_advection(size, 10000, 1e-4);
}

