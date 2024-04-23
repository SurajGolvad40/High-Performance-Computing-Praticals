#include <iostream>
#include <omp.h> // Include the OpenMP header

using namespace std;

void parallelBubbleSort(int* arr, int n) {
    int i, j, temp;
    // Parallel region begins
    #pragma omp parallel shared(arr, n) private(i, j, temp) num_threads(1)
    for (i = 0; i < n; i++) {

        // Odd-even transposition
        #pragma omp for
        for (j = i % 2; j < n-1; j += 2) {
            cout<<"Thread "<<omp_get_thread_num()<<" , ";
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

    }
    // Parallel region ends
}

int main() {
    int n = 8; // Size of the array
    int arr[] = {64, 34, 25, 12, 22, 11, 90, 88};

    cout << "Original array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    parallelBubbleSort(arr, n);

    cout << "Sorted array:   ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
