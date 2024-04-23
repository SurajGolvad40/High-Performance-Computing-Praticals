#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int main()
{
    int arr[5] = {1,2,3,4,5};
    int min_val = INT_MAX, max_val = INT_MIN;
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < 5; i++)
    {
        sum += arr[i];
    }

    #pragma omp parallel for reduction(min:min_val)
    for(int i = 0; i < 5; i++)
    {
        if(arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }

    #pragma omp parallel for reduction(max:max_val)
    for(int i = 0; i < 5; i++)
    {
        if(arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    cout<<"Sum : "<<sum;
    cout<<"Avg : "<<sum/5;
    cout<<"Max : "<<min_val;
    cout<<"Min : "<<max_val;

    return 0;
}