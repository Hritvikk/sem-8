!pip install git+https://github.com/afnan47/cuda.git

%load_ext nvcc_plugin

//TEST
%%cu

#include<iostream>
using namespace std;

int main(){
    cout<<"Hello World";
}

%%cu
//HPC 4A P2

#include<iostream>
using namespace std;

__global__ void add(int *a,int *b, int *c, int size){
    int tid=blockIdx.x*blockDim.x + threadIdx.x;
    if(tid<size){
        c[tid] = a[tid] + b[tid];
    }
}

void initialize(int *a,int size){
    for(int i=0;i<size;i++){
        a[i] = rand()%10;
    }
}

void print(int *a,int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<" ";
    }
}

int main(){
    int n=5;
    int *a,*b,*c;

    int vecBytes = n*sizeof(int);

    a = new int[n];
    b = new int[n];
    c = new int[n];

    initialize(a,n);
    initialize(b,n);
    
    cout<<"\nVector 1\n";
    print(a,n);
    cout<<"\nVector 2\n";
    print(b,n);

    int *x,*y,*z;

    cudaMalloc(&x,vecBytes);
    cudaMalloc(&y,vecBytes);
    cudaMalloc(&z,vecBytes);
    cudaMemcpy(x,a,vecBytes,cudaMemcpyHostToDevice);
    cudaMemcpy(y,b,vecBytes,cudaMemcpyHostToDevice);

    int threads=4;
    int blocks=4;

    add<<<blocks,threads>>>(x,y,z,n);

    cudaMemcpy(c,z,vecBytes,cudaMemcpyDeviceToHost);

    cout<<"\nAddition \n";
    print(c,n);

    delete[] a;
    delete[] b;
    delete[] c;

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);

    return(0);
}

%%cu
//HPC 4B P2

#include<iostream>
using namespace std;

__global__ void multiply(int *a,int *b,int *c,int size){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;

    if(row<size&&col<size){
        int sum=0;
        for(int i=0;i<size;i++){
            sum+=a[row*size+i]*b[size*i+col];
        }
        c[row*size+col]=sum;
    }
}

void initialize(int *a,int size){
    for(int i=0;i<size*size;i++){
        a[i]= rand()%10;
    }
}

void print(int *a,int size){
    for(int row=0;row<size;row++){
        for(int col=0;col<size;col++){
            cout<<a[row*size+col]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    int n=2;
    int *a,*b,*c;

    int size=n*n;

    int matBytes = size*sizeof(int);

    a = new int[size];
    b = new int[size];
    c = new int[size];

    initialize(a,n);
    initialize(b,n);

    cout<<"\nMatrix 1\n";
    print(a,n);

    cout<<"\nMatrix 2\n";
    print(b,n);

    int *x,*y,*z;

    cudaMalloc(&x,matBytes);
    cudaMalloc(&y,matBytes);
    cudaMalloc(&z,matBytes);

    cudaMemcpy(x,a,matBytes,cudaMemcpyHostToDevice);
    cudaMemcpy(y,b,matBytes,cudaMemcpyHostToDevice);

    int THREADS = 2;
    int BLOCKS = 2;

    dim3 threads(THREADS,THREADS);
    dim3 blocks(BLOCKS,BLOCKS);

    multiply<<<blocks,threads>>>(x,y,z,n);

    cudaMemcpy(c,z,matBytes,cudaMemcpyDeviceToHost);

    cout<<"\nMultiplication \n";
    print(c,n);

    delete[] a;
    delete[] b;
    delete[] c;

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);

    return(0);
}
