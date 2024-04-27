#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread> // for std::this_thread::sleep_for

using namespace std;
using namespace std::chrono;

int minval(int arr[], int n)
{
    int minval = arr[0];

#pragma omp parallel for reduction(min : minval)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < minval)
            minval = arr[i];
    }

    // Introduce some artificial delay
    this_thread::sleep_for(milliseconds(100));

    return minval;
}

int maxval(int arr[], int n)
{
    int maxval = arr[0];

#pragma omp parallel for reduction(max : maxval)
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxval)
            maxval = arr[i];
    }

    // Introduce some artificial delay
    this_thread::sleep_for(milliseconds(100));

    return maxval;
}

int sum(int arr[], int n)
{
    int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // Introduce some artificial delay
    this_thread::sleep_for(milliseconds(100));

    return sum;
}

int average(int arr[], int n)
{
    return (double)sum(arr, n) / n;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    // Measure execution time for each function
    auto start = high_resolution_clock::now();
    int min = minval(arr, n);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "The minimum value is: " << min << ", took " << duration.count() << " milliseconds\n";

    start = high_resolution_clock::now();
    int max = maxval(arr, n);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "The maximum value is: " << max << ", took " << duration.count() << " milliseconds\n";

    start = high_resolution_clock::now();
    int s = sum(arr, n);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "The sum is: " << s << ", took " << duration.count() << " milliseconds\n";

    start = high_resolution_clock::now();
    int avg = average(arr, n);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "The average is: " << avg << ", took " << duration.count() << " milliseconds\n";

    return 0;
}
