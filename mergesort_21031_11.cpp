// Author Name: Aditya Rajesh Bawangade
// Roll NUmber 2103111
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
// Merge function for merging two arrays
void merge(int arr[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    // Maintaining current index of sub-arrays and the main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    // Conditioning and looping if one of the arrays exhausts befor the other
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}
// PrintArray function for printing the sorted array in the mergesort function
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
// mergeSortBasic function is a recursive mergesort which sorts the input array and returns void
void mergeSortBasic(int arr[], int l, int r)
{
    if (l < r)
    {
        // m is the point where the array is divided into two subarrays
        int m = l + (r - l) / 2;

        mergeSortBasic(arr, l, m);
        mergeSortBasic(arr, m + 1, r);

        // Merge the sorted subarrays
        merge(arr, l, m, r);
    }
}
// Actual mergesort function which outputs sorted array and has a return type of null
void mergesort(int arr[], int l, int r)
{
    mergeSortBasic(arr, l, r);
    printArray(arr, r + 1);
}
// TimeMergeSort function calculates the time required for the execution of the mergesort function

int TimeMergeSort(int arr[], int l, int r)
{
    int answer;
    // measuring the time required for the execution
    auto start = high_resolution_clock::now();
    mergesort(arr, l, r);
    auto stop = high_resolution_clock::now();
    // Using the unit of time as nanoseconds to be able to get smaller numbers
    auto duration = duration_cast<nanoseconds>(stop - start);
    answer = duration.count();
    cout << "Time taken by the Merge Sort procedure for sorting and returning the output of the given array is: " << answer << " nanoseconds" << endl;
    return answer;
}
// OriginalOutputFunction returns k arrays sorted using mergesort with their running time and the variance and the mean of the ci's
void OriginalOutputFunction(int k = 1)
{
    // Creating an array to store ci's
    int Ci[k];
    // looping until k
    for (int a = 1; a <= k; a++)
    {
        int sizeOfArray = pow(2, a);
        int arr[sizeOfArray];
        for (int i = 0; i < sizeOfArray; i++)
        { // generating an array of random numbers
            arr[i] = rand();
        }
        int Tn = TimeMergeSort(arr, 0, sizeOfArray - 1);
        Ci[a - 1] = float((Tn) / (a * sizeOfArray));
        cout << "(" << a << "," << sizeOfArray << "," << Tn << "ns," << a * sizeOfArray << "," << Ci[a - 1] << "ns)" << endl;
    }
    int Ci_mean = 0;
    int ci_variance = 0;
    for (int g = 0; g < k; g++)
    {
        Ci_mean += Ci[g];
    }
    Ci_mean /= k;
    cout << "Expected Value of the Ci's is: " << Ci_mean << " nanoseconds" << endl;
    for (int h = 0; h < k; h++)
    {
        ci_variance += pow((Ci[h] - Ci_mean), 2);
    }
    ci_variance /= k;
    cout << "Variance of the Ci's is: " << ci_variance << " nanoseconds" << endl;
    return;
}
// Testing the function
int main()
{
    OriginalOutputFunction(8);
    return 0;
}