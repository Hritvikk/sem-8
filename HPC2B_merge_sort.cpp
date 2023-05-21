#include<iostream>
#include<omp.h>

using namespace std;


void merge(int arr[],int low,int mid,int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for(int i=0;i<n1;i++) {
        left[i] = arr[low+i];
    }
    for(int j=0;j<n2;j++) {
        right[j] = arr[mid+j+1];
    }
    int i=0,j=0,k=low;

    while(i<n1 && j<n2){
        if(left[i]<=right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k]=right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int low, int high){
    if(low<high){
        int mid=(low+high)/2;

        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
}


void pMergeSort(int arr[], int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                pMergeSort(arr,low,mid);
            }

            #pragma omp section
            {
                pMergeSort(arr,mid+1,high);
            }
        }
        merge(arr,low,mid,high);
    }
}

void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}

int main(){
    int n=10;
    int arr1[n] = {1,5,6,9,2,4,12,11,7,3};
    int arr2[n] = {1,5,6,9,2,4,12,11,7,3}; 

    double start_time,end_time;
    start_time = omp_get_wtime();
    mergeSort(arr1,0,n-1);
    end_time = omp_get_wtime();
    cout<<'\n';
    printArray(arr1,n);
    cout<<"\nMerge Sort Took "<<end_time - start_time<<" seconds";

    start_time = omp_get_wtime();
    pMergeSort(arr2,0,n-1);
    end_time = omp_get_wtime();
    cout<<'\n';
    printArray(arr2,n);
    cout<<"\nParallel Merge Sort Took "<<end_time - start_time<<" seconds";

    return(0);
}
