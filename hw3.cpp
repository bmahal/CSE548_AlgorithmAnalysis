#include<iostream>
#include<climits>
#include <bits/stdc++.h>
#include "unordered_map" 
using namespace std;

void swap(int *x, int *y); 
void selectItems(int arr[],int n,int k2,int arr2[]);
void removeDups(int arr[], int n); //to remove duplicates 


class MinHeap
{
	int *harr;
	int capacity; // maximum possible size of min heap
	int heap_size;

public:
	MinHeap(int a[], int size); // constructor
	void MinHeapify(int i);  //for maintaining the heap property
	int parent(int i) { return (i-1)/2; }
	int left(int i) { return (2*i + 1); }
	int right(int i) { return (2*i + 2); }
	int extractMin(); // extracts root
	int getMin() { return harr[0]; }
};

MinHeap::MinHeap(int a[], int size)
{
	heap_size = size;
	harr = a;
	int i = (heap_size - 1)/2;
	while (i >= 0)
	{
		MinHeapify(i);
		i--;
	}
}

int MinHeap::extractMin()
{
	if (heap_size == 0)
		return INT_MAX;
	int root = harr[0];
	if (heap_size > 1)
	{
		harr[0] = harr[heap_size-1];
		MinHeapify(0);
	}
	heap_size--;
	return root;
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int kthSmallest(int arr[], int n, int k) //using minheap
{

	MinHeap mheap(arr, n); //linear time
	// extract min (k-1) times
	for (int i=0; i<k-1; i++)
		mheap.extractMin();
	return mheap.getMin();
}

class MaxHeap
{
    int *harr;
    int capacity; // maximum possible size of max heap
    int heap_size;
public:
    MaxHeap(int a[], int size); // constructor
    void maxHeapify(int i); //maintaining the heap property
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    int extractMax();  // extracts root
    int getMax() { return harr[0]; }

    void replaceMax(int x) { harr[0] = x;  maxHeapify(0); }
};

MaxHeap::MaxHeap(int a[], int size)
{
    heap_size = size;
    harr = a;
    int i = (heap_size - 1)/2;
    while (i >= 0)
    {
        maxHeapify(i);
        i--;
    }
}

int MaxHeap::extractMax()
{
    if (heap_size == 0)
        return INT_MAX;

    int root = harr[0];
    if (heap_size > 1)
    {
        harr[0] = harr[heap_size-1];
        maxHeapify(0);
    }
    heap_size--;

    return root;
}

void MaxHeap::maxHeapify(int i) //to maintain max heap property
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && harr[l] > harr[i])
        largest = l;
    if (r < heap_size && harr[r] > harr[largest])
        largest = r;
    if (largest != i)
    {
        swap(&harr[i], &harr[largest]);
        maxHeapify(largest);
    }
}

int kthSmallestUsingMax(int arr[], int n, int k) //using maxheap
{
    MaxHeap mh(arr, k); //takes O(k) time

    for (int i=k; i<n; i++)
        if (arr[i] < mh.getMax())
           mh.replaceMax(arr[i]);


    return mh.getMax(); //return root
}

void removeDups(int arr[], int n) //using HashMap
{
    unordered_map<int, bool> mp;

    for (int i = 0; i < n; ++i)
        {
        if (mp.find(arr[i]) == mp.end()) {
            cout << arr[i] << " ";
        }

        mp[arr[i]] = true;
    }
}

int rand_select(int arr[], int n, int k)
{
    int k2 = log(n)*log(n);
    int random[k2] ;
    selectItems(arr,n,k2,random);

    int n2=sizeof(random) / sizeof(random[0]);
    removeDups(random,n2); //removing duplicates in random

    //set S is the random array
    int q=sizeof(random) / sizeof(random[0]);
    int l=INT_MIN;
    int u=INT_MAX;
    sort(random,random+q);

    cout<<"random sorted is "<<endl;
    for(int i=0;i<q;i++)
    {
        cout<<random[i]<<endl;
    }
    int c[q+1];
    c[0]=0;
    c[q]=0;
    for(int i=1;i<q;i++)
    {
        c[i]=0;
    }
    for(int j=0;j<n;j++)
    {
        for(int k=0;k<q;k++)
        {
            if(arr[j]<=random[0])
            {
                c[0]++;
                break;
            }
            else if(arr[j]>random[q-1])
            {
                c[q]++;
                break;
            }
            else if(arr[j]>random[k] && arr[j]<=random[k+1])
            {
                //cout<<"k is"<<k<<endl;
                c[k+1]++;
            }
        }
    }
    //for(int i=0;i<=q;i++)
    //{
        //cout<<"c is "<<c[i]<<endl;
    //}

    int p,sum;
    sum=0;p=0;
    int sumarr[q];
    for(int i=0;i<q;i++)
    {
        sumarr[i]=0;
    }
    for(int i=0;i<q;i++)
    {
        p=i;
        for(int k=0;k<=p;k++)
        {
            sumarr[i]=sumarr[i]+c[k];
        }
    }
    //for(int i=0;i<q;i++)
    //{cout<<"sumarr is "<<sumarr[i]<<endl;}

    for(int i=0;i<q;i++)
    {
        if(k<=sumarr[i])
        {
            p=i;
            break;
        }
    }

    int sum2=0;
    for(int i=0;i<p;i++)
    {
        sum2+=c[i];
    }

    int count=0;
    //cout<<"ll= "<<random[p-1]<<endl;
    //cout<<"ul= "<<random[p]<<endl;

    for(int j=0;j<n;j++)
    {
        if(arr[j]>random[p-1] && arr[j]<=random[p])
        {
            count++;
        }
    }
    int t[count];
    int cnt=0;
    for(int j=0;j<n;j++)
    {
        if(arr[j]>random[p-1] && arr[j]<=random[p])
        {
            t[cnt++]=arr[j];

        }
    }

    sort(t,t+count);
    //for(int i=0;i<count;i++)
    //{cout<<"t is "<<t[i]<<endl;}
    int m=k-sum2;
    //cout<<"m is"<<m<<endl;
    cout<<"kth smallest element is "<<t[m-1];
}

void selectItems(int stream[], int n, int k2 ,int reservoir[]) //for random selection of elements (reservoir algorithm)
{

    int i;
    for (i = 0; i < k2; i++)
        reservoir[i] = stream[i];
    srand(time(NULL));

    for (; i < n; i++)
    {
        int j = rand() % (i+1);
        if (j < k2)
          reservoir[j] = stream[i];
    }

    printf("Following are the randomly selected items \n");
    for(int i=0;i<k2;i++)
    {
        cout<<reservoir[i]<<endl;
    }
    //return reservoir;
}


int main()
{
    int n,k;
    cout<<"enter n"<<endl;
    cin>>n;
    int arr[n];
    cout<<"enter distinct array elements"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    cout<<"enter k";
    cin>>k;
    if(k<1 || k>n)
    {

        cout<<"invalid value for k"<<endl;
        return 0;
    }

    //Three cases arise
    if(k<=(n/log(n))) //use min heap
    {
        cout << "K'th smallest element using min heap is " << kthSmallest(arr, n, k);
    }
    else if(k>=(n - n/log(n))) //use max heap
    {
        cout << "K'th smallest element using max heap is " << kthSmallestUsingMax(arr, n, k);
    }
    else // ex: for k between 6 and 14 for n=20  //use random selection
    {
        rand_select(arr,n,k);
    }
	return 0;
}
