#include<iostream>
#include<climits>
#include <bits/stdc++.h>
using namespace std;
int par_partition(int arr[],int x);
void prefix_sum(int arr[],int n,int flag);
int findksmallest(int arr[],int q,int r,int k);
int getMedian(int arr[], int n);
int n=7;
int z[7];
int s[7];


int main()
{

    int arr[]={10,20,4,3,5,27,50};
    int x=20;
    //par_partition(arr,x);
    int k2=5;
    int q=0;
    int r=6;
    int res=findksmallest(arr,q,r,k2);
    cout<<k2<<" smallest number in the given list is "<<res<<endl;
}

void prefix_sum(int arr[],int n,int flag);

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
        cilk_for(int i=0;i<n/2;i++) //parallel-for loop
        {
            y[i]=arr[2*i]+arr[2*i+1];
        }
        prefix_sum(y,n/2,1);
        cilk_for(int i=0;i<n;i++) //parallel-for loop
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
int getMedian(int arr[], int n) //returns middle element after sorting
{
    sort(arr, arr+n);
    return arr[n/2];
}

int findksmallest(int arr[],int q,int r,int k)
{
    int n=r-q+1;
    if(n<=5)
    {
        sort(arr,arr+n);
        return arr[q+k-1];
    }
    else{
        if (k > 0 && k <= r - q + 1)
        {
        int median[(n+4)/5];
        int i=INT_MIN;
	cilk_for (int c=0; c<n/5; c++)
	{
            median[c] = getMedian(arr+q+c*5, 5);
            if(c>i){i=c;}	
	}
        if (i*5 < n) //last grp
        {
            median[i] = getMedian(arr+q+i*5, n%5);
            i++;
        }

        int medOfMed = (i == 1)?median[i-1]:findksmallest(median, 0, i-1, i/2);
        cout<<"medofmed = "<<medOfMed<<endl;


        int pos = par_partition(arr,medOfMed); //gives position of pivot


        if (pos-q == k-1) //if pos==k
            return arr[pos];
        else if (pos-q > k-1)  //left subarray
            return findksmallest(arr, q, pos-1, k);

        return findksmallest(arr, pos+1, r, k-pos+q-1); //right subarray
    }

    // if k is more than n
    return INT_MAX ;

    }


}
