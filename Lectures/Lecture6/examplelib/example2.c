
void fibonaci(double a[], int n)
{
    int i=2;
    if(n <= 0) return;
    a[0] = 0;
    if(n == 1) return;
    a[1] = 1;
    for(; i<n; ++i)
    {
        a[i] = a[i-1] + a[i-2];
    }
    return;
}