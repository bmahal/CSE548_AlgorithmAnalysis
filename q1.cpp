#include<iostream>
#include<climits>
#include<bits/stdc++.h>
#include "main_minheap.h"
#include "main_stack.h"
using namespace std;


int grid[4][4]={{0,8,-1,0},{2,0,0,0},{0,-1,18,0},{10,0,0,0}};
int profit[4][4];
char direction[4][4];
int minmatrix[4][4];
int s1,s2,b1,b2;

void initial();
void update_minmatrix();
void update_profit();
void find_selling_point();
void find_buying_point();


int main()
{

//grid={{0,8,-1,0},{2,0,0,0},{0,-1,18,0},{10,0,0,0}};
initial();
update_minmatrix();
update_profit();
find_selling_point();
find_buying_point();
cout<<"Maximum profit incurred is $"<<grid[s1][s2]-grid[b1][b2]<<endl;
//print direction matrix

return 0;
}


void initial()
{
int m,n;
m=4;n=4;
for(int i=m-1;i>=0;i--)
{
    for(int j=n-1;j>=0;j--)
    {
        minmatrix[i][j]=INT_MAX;
        profit[i][j]=0;
        direction[i][j]=0;
    }
}
}

void update_minmatrix()
{
int m,n;
m=4;n=4;
for(int i=1;i<m;i++)
{
     for(int j=1;j<n;j++)
     {
         if(grid[i][j]!=-1)
         {
         if(grid[i-1][j]!=-1 && grid[i][j-1]!=-1)
         {
             minmatrix[i][j] = min(grid[i-1][j],grid[i][j-1]); //min of top and left values
         }
         else if (grid[i-1][j]!=-1 && grid[i][j-1]==-1 ) //only accessible from top
         {
             minmatrix[i][j]=grid[i-1][j];
             direction[i-1][j]='S';
         }
         else if(grid[i][j-1]!=-1 && grid[i-1][j]==-1)
         {
             minmatrix[i][j]=grid[i][j-1];
             direction[i][j-1]='E';
         }
         }//end of if
     }
}
}

void update_profit()
{
int m,n;
m=4;n=4;
for(int i=1;i<m;i++)
{
     for(int j=1;j<n;j++)
     {
         if(grid[i][j]!=-1)
         {
         if(grid[i-1][j]!=0 && grid[i-1][j]!=-1)
         {
             if(grid[i-1][j]>minmatrix[i][j])
             {
                 profit[i][j]=grid[i-1][j]-minmatrix[i][j];
                 direction[i][j]='S';
             }
         }
         if(grid[i][j-1]!=0 && grid[i][j-1]!=-1)
         {
             if(grid[i][j-1]>minmatrix[i][j])
             {
                 profit[i][j]=grid[i][j-1]-minmatrix[i][j];
                 direction[i][j]='E';
             }
         }
         if(grid[i-1][j]!=0 && grid[i-1][j]!=-1 && grid[i][j-1]!=0 && grid[i][j-1]!=-1)
         {
             if(grid[i-1][j]>minmatrix[i][j] && grid[i-1][j]>profit[i][j])
             {
                 profit[i][j]=grid[i-1][j]-minmatrix[i][j];
                 direction[i][j]='S';

             }
             else if(grid[i][j-1]>minmatrix[i][j] && grid[i][j-1]>profit[i][j])
             {
                 profit[i][j]=grid[i][j-1]-minmatrix[i][j];
                 direction[i][j]='E';
             }
         }
         }
     }
}}

void find_selling_point()
{
    int k,l;
    int in=0;
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=3;j++)
        {
            if(profit[i][j]!=0 && profit[i][j]>in)
            {
                if(direction[i][j]=='S')
                {
                    k=i-1;l=j;
                }
                else{
                    k=i;l=j-1;
                }
            }
        }
    }
    cout<<"selling point is: "<<k<<" , "<<l<<endl;
    s1=k;s2=l;
}

void find_buying_point()
{
    int m,n;
m=4;n=4;
int min,k,l;
min=INT_MAX;
for(int i=1;i<m;i++)
{
     for(int j=1;j<n;j++)
     {
         if(minmatrix[i][j]>0 && minmatrix[i][j]<min)
         {
             cout<<i<<" , "<<j<<endl;
             cout<<direction[i][j]<<endl;
             if(direction[i][j]=='S')
             {
                 l=i-1;k=j;

             }
             else if(direction[i][j]=='E')
             {
                 l=i;k=j-1;

             }
             else
             {
                 if(j==1) //buying point is in leftmost column
                 {
                     l=j;k=0;

                 }
             }
         }
     }
}
cout<<"BUYING point is: "<<l<<" , "<<k<<endl;
b1=l;b2=k;
}

