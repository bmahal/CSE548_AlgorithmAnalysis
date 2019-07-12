#include<iostream>
#include<climits>
#include <bits/stdc++.h>
using namespace std;
void prefix_sum(int arr[],int n,int flag);
void swap(int *a, int *b) ;
void par_select(int arr[],int q,int r,int k);

int n=7;
int z[7];
int s[7];

int main()
{

    int arr[]={10,20,4,3,5,27,50};
    int q,r,k;
    q=0;r=6;
    k=2;
    par_select(arr,q,r,k);

    return 0;
}

void par_select(int arr[],int q,int r,int k) //parallel divide and conquer algorithm
{
    int n=r-q+1;
    int b[n][n];
    int c[n];
    int res[k];
    int cnt=0;

    cilk_for(int i=1;i<=n;i++) //parallel nested loops
    {
       cilk_for(int j=1;j<=n;j++)
        {
            if(arr[q+i-1]>arr[q+j-1])
            {
                b[i-1][j-1]=1;
            }
            else{
                b[i-1][j-1]=0;
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        int temp[n];
        int ps;
        cilk_for (int k = 0; k < n; k++) //parallel loop
	{
            temp[k] = b[i-1][k];
        }
        prefix_sum(temp,n,0);
        cout<<"prefix sum is "<<s[n-1]<<endl;
        ps=s[n-1];
        c[cnt]=ps;
        cnt++;
    }

    for(int i=1;i<=n;i++)
    {
        cout<<"c is "<<c[i-1]<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        if(c[i-1]<k)
        {
            res[c[i-1]]=arr[i-1];
        }
    }

    cout<<"k smallest numbers in sorted order are : "<<endl;
    for(int m=0;m<k;m++)
    {
        cout<<res[m]<<endl;
    }

}

void prefix_sum(int arr[],int n,int flag) //parallel prefix sum
{

    //int s[n];
    int y[n/2];
    if (n==1)
    {
        s[0]=arr[0];
    }
    else{
        cilk_for(int i=0;i<n/2;i++) //parallel loop
        {
            y[i]=arr[2*i]+arr[2*i+1];
        }
        prefix_sum(y,n/2,1);
        cilk_for(int i=0;i<n;i++) //parallel loop
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

//helper swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
