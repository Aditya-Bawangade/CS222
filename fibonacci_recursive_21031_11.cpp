#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
// using header file chrono and namespace chrono to be able to calculate time in nanoseconds prehand
using namespace std::chrono;
using namespace std;
// The recursive implementation of the fibonacci function
int Fib1(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return Fib1(n - 1) + Fib1(n - 2);
}
int TimeFib1(int n)
{
    int answer;
    // measuring the time required for the execution
    auto start = high_resolution_clock::now();
    Fib1(n);
    auto stop = high_resolution_clock::now();
    // Using the unit of time as nanoseconds to be able to get smaller numbers
    auto duration = duration_cast<nanoseconds>(stop - start);
    answer = duration.count();
    cout << "Time taken by the recursive implementation of the " << n << "th fibonacci number is: " << answer << " nanoseconds" << endl;
    return answer;
}

int main()
{
    // Storing the output of the file in a .csv file to be able to plot the graph
    ofstream file;
    file.open("myArray.csv");

    for (int i = 10; i <= 42; i++)
    {
        file << log2(Fib1(i)) << ",";
    }

    file.close();

    // Storing the output of the file in a .csv file to be able to plot the graph
    ofstream file1;
    file1.open("myArray2.csv");

    for (int i = 10; i <= 42; i++)
    {
        file1 << log2(TimeFib1(i)) << ",";
    }

    file1.close();
}
