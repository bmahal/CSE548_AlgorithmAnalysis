#include<iostream>
#include<climits>
#include <bits/stdc++.h>
using namespace std;
int par_partition(int arr[],int x);
void prefix_sum(int arr[],int n,int flag);
int randomPartition(int arr[], int l, int r);
int partition(int arr[], int l, int r) ;
int randomizedQuickSelect(int arr[],int q,int r,int k);
void swap(int *a, int *b) ;

int n=7;
int z[7];
int s[7];


int main()
{

    int arr[]={10,20,4,3,5,27,50};
    int q,r;
    q=0;r=6;
    int k=6;
    int res=randomizedQuickSelect(arr,q,r,k);
    cout<<"Kth smallest element in arr is "<<res<<endl;
    return 0;
}

int randomizedQuickSelect(int arr[],int q,int r,int k)
{
    int pos,t;
    pos=randomPartition(arr,q,r);
    cout<<"randomly selected number = "<<arr[pos]<<endl;
    t=par_partition(arr,arr[pos]);
    if (k==(t-q+1))
    {
        return arr[t];
    }
    else if(k<(t-q+1)) //left subarray
    {
        return randomizedQuickSelect(arr,q,t-1,k);

    }
    else //right subarray
    {
         return randomizedQuickSelect(arr,t+1,r,k-t+q-1);
    }

}//end of function


int par_partition(int arr[],int x)
{
    int q,r,n;
    q=0;
    r=6;
    n=r-q+1;
    if(n==1)
    {
        return q;
    }
    int b[n];
    int lt[n];
    int gt[n];
    int flag=-1;

    //parallelize for loop
    cilk_for (int i=0;i<n;i++)
    {

        b[i]=arr[q+i];
        if(b[i]<x)
        {
            lt[i]=1;
        }
        else
        {
            lt[i]=0;
        }
        if(b[i]>x)
        {
            gt[i]=1;
        }
        else
        {
            gt[i]=0;
        }

    }//end of parallel-for

    for(int i=0;i<n;i++)
    {
        cout<<"lt = "<<lt[i]<<endl;
    }
    for(int i=0;i<n;i++)
    {
        cout<<"gt = "<<gt[i]<<endl;
    }
    prefix_sum(lt,n,0);
    cilk_for(int i=0;i<n;i++) //copy to lt
    {
        lt[i]=s[i];
    }

    prefix_sum(gt,n,0);
    cilk_for(int i=0;i<n;i++) //copy prefix sum to gt
    {
        gt[i]=s[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<"ltsum = "<<lt[i]<<endl;
    }

    for(int i=0;i<n;i++)
    {
        cout<<"gtsum = "<<gt[i]<<endl;
    }

    int k=q+lt[n-1];
    arr[k]=x;
    cilk_for(int i=0;i<n;i++)
    {
        if(b[i]<x)
        {
            arr[q+lt[i]-1] =b[i];
        }
        else if(b[i]>x)
        {
            arr[k+gt[i]]=b[i];
        }
    }
    cout<<"k = "<<k<<endl;
    for(int m=q;m<k;m++)
    {
        cout<<"elements in left range are "<<arr[m]<<endl;
    }
    for(int m=k+1;m<=r;m++)
    {
        cout<<"elements in right range are "<<arr[m]<<endl;
    }
    return k;
}

void prefix_sum(int arr[],int n,int flag)
{

    //int s[n];
    int y[n/2];
    if (n==1)
    {
        s[0]=arr[0];
    }
    else{
       cilk_for(int i=0;i<n/2;i++)
        {
            y[i]=arr[2*i]+arr[2*i+1];
        }
        prefix_sum(y,n/2,1);
        cilk_for(int i=0;i<n;i++)
        {
            if(i==0)
            {
                s[0]=arr[0];
            }
            else if(i%2!=0)
            {
                s[i]=z[i/2];
            }
            else{
                s[i]=z[(i-1)/2]+arr[i];
            }
        }
    }

    if(flag==1)
    {
        for(int i=0;i<n;i++)
        {
            z[i]=s[i];
            cout<<"z[i]= "<<z[i]<<endl;
        }
        return;
    }
    else{
        for(int i=0;i<n;i++)
        {

            cout<<"s[i]= "<<s[i]<<endl;
        }
    }
    return ;

}

//picks and returns the position of random pivot element
int randomPartition(int arr[], int l, int r)
{
    int n = r-l+1;
    int pivot = rand() % n;
    swap(&arr[l + pivot], &arr[r]);
    return partition(arr, l, r);
}

//helper swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//standard quicksort partition function
int partition(int arr[], int l, int r)
{
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}
