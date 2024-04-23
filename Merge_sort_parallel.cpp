#include<iostream>
#include<omp.h>
using namespace std;

void merge(int arr[], int l, int mid, int r)
{
    int s = r-l;
    int arr2[r-l + 1];
    int i = l, j = mid+1, k = 0;

    while(i <= mid && j <= r)
    {
        if(arr[i] < arr[j])
        {
            arr2[k] = arr[i];
            i++;
        }
        else
        {
            arr2[k] = arr[j];
            j++;
        }

        k++;
    }

    if(i > mid)
    {
        while(j <= r)
        {
            arr2[k] = arr[j];
            j++;
            k++;
        }
    }
    else
    {
        while(i <= mid)
        {
            arr2[k] = arr[i];
            i++;
            k++;
        }
    }

    k = 0;
    for(i = l; i <= r; i++)
    {
        arr[i] = arr2[k];
        k++;
    }
}


void mergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int mid = (l+r)/2;
        cout<<"Thread : "<<omp_get_thread_num()<<" , ";

        omp_set_nested(1); // this enable parallelism inside another parallel regin try one to remove this line to understand  
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, l, mid);
            }

            #pragma omp section
            {
                mergeSort(arr, mid+1, r);
            }
        }
        
        merge(arr, l, mid, r);
    }
}

int main()
{
    int arr[] = {8,5,4,2,1,10,6,7,0};
    int size = sizeof(arr)/sizeof(arr[0]);
    int l = 0, r = size-1;

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            mergeSort(arr, l, r);
        }    
    }

    for(int i = 0; i < size; i++)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}
