// Author Name: Aditya Rajesh Bawangade
#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
// Partition function to st the pivot and create the partition around it
int partition(int arr[], int low, int high, int pivot)
{
    int piv = low;

    for (int i = low; i <= high; i++)
    {

        if (arr[i] <= pivot)
        {

            swap(arr[piv], arr[i]);

            piv++;
        }
    }

    piv--;

    return piv;
}

// after pivoting, we now call the quicksortbasic function which sorts the two subarrays around the pivot and returns void
void quickSortbasic(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];

        // Placing the pivot in the right position
        int piv = partition(arr, low, high, pivot);

        // Recursive calls for left and right subarrays around the pivot
        quickSortbasic(arr, low, piv - 1);
        quickSortbasic(arr, piv + 1, high);
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
// quicksort function sorts the array and outputs the sorted array
void quicksort(int arr[], int low, int high)
{
    quickSortbasic(arr, low, high);
    printArray(arr, high);
}
// TimeQuickSort function calculates the time for  quicksort function
int TimeQuickSort(int arr[], int low, int high)
{
    int answer;
    // measuring the time required for the execution
    auto start = high_resolution_clock::now();
    quicksort(arr, low, high);
    auto stop = high_resolution_clock::now();
    // Using the unit of time as nanoseconds to be able to get smaller numbers
    auto duration = duration_cast<nanoseconds>(stop - start);
    answer = duration.count();
    cout << "Time taken by the Quick Sort procedure for sorting and returning the output of the given array is: " << answer << " nanoseconds" << endl;
    return answer;
}
// OriginalOutputFunction returns k arrays sorted using quicksort with their running time and the variance and the mean of the ci's
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
        int Tn = TimeQuickSort(arr, 0, sizeOfArray - 1);
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
    cout << "Expected value of the Ci's is: " << Ci_mean << " nanoseconds" << endl;
    for (int h = 0; h < k; h++)
    {
        ci_variance += pow((Ci[h] - Ci_mean), 2);
    }
    ci_variance /= k;
    cout << "Variance of the Ci's is: " << ci_variance << " nanoseconds" << endl;
    return;
}
// Testing the outputs
int main()
{
    // OriginalOutputFunction(8);
    int size;
    cin>>size;
    int arr[size];
    for(int i = 0 ; i < size ; i++){
        cin>>arr[i];
    }
    int tn = TimeQuickSort(arr,0,size-1);
    cout<<tn;
    return 0;
}
