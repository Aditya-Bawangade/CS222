// Aditya Rajesh Bawangade
// ROll Number 2103111
#include <iostream>
using namespace std;
void multiply(long long int F[2][2], long long int M[2][2]) // Implementing a function to multiply 2x2 matrices
{
    long long int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
// Implementing a power function using repeated squaring keeping return type void
void power(long long int F[2][2], long long int n)
{
    if (n == 0)
    {
        F[0][0] = 1;
        F[0][1] = 0;
        F[1][0] = 0;
        F[1][1] = 1;
        return;
    }
    if (n == 1)
    {
        F[0][0] = 1;
        F[0][1] = 1;
        F[1][0] = 1;
        F[1][1] = 0;
        return;
    }
    long long int M[2][2] = {{1, 1}, {1, 0}};
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
        multiply(F, M);
}

// Implementation of the Fibaonacci function to calculate nth fibonacci
long long int Fibonacci(int n)
{
    long long int F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}
// Implementation of the Fibaonacci function to calculate numbers until n using repeated squaring of a 2x2 matrix
long long int Fib(int n)
{
    for (int i = 0; i <= n; i++)
    {
        cout << "The " << i << "th Fibonacci number is " << Fibonacci(i) << endl;
    }
    return Fibonacci(n);
}
int main()
{
    Fib(35);
    return 0;
}
