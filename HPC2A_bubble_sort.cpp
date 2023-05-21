#include<iostream>
#include<omp.h>

using namespace std;

void bubble(int arr[],int n){
    for(int i=0;i<n;i++){
        for(int j=1;j<n-i;j++){
            if(arr[j-1]>arr[j]) swap(arr[j],arr[j-1]);
        }
    }
}

void pBubble(int arr[],int n){
    for(int i=0;i<n;++i){
        //Odd
        #pragma omp for
        for(int j=1;j<n;j+=2){
            if(arr[j-1]>arr[j]) swap(arr[j],arr[j-1]);
        }
        //Synchronize
         #pragma omp barrier

        //Even
        #pragma omp for
        for(int j=2;j<n;j+=2){
            if(arr[j-1]>arr[j]) swap(arr[j],arr[j-1]);
        }
    }

}

void printArray(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}

int main(){
    int n=10;
    int arr[n] = {2,3,5,1,10,18,12,13,4,1};
    double start_time,end_time;

    start_time = omp_get_wtime();
    bubble(arr,n);
    end_time = omp_get_wtime();

    cout<<"\nBubble Sort Took : "<<end_time - start_time<<" seconds";
    printArray(arr,n);
    int brr[n] = {2,3,5,1,10,18,12,13,4,1};

    start_time = omp_get_wtime();
    pBubble(brr,n);
    end_time=omp_get_wtime();

    cout<<"\nParaller Bubble Sort Took : "<<end_time - start_time<<" seconds";
    printArray(brr,n);

}
