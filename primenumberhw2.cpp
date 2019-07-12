#include<iostream>
#include<string>
#include<climits>
#include<bits/stdc++.h>
#include "main_minheap.h"
#include "main_stack.h"
using namespace std;

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);
class MinHeap;
class Stack;
int n=500;
//Function prototypes
MinHeap h(n-1);
MinHeap h2(n-1);
struct Stack s;

//Define Head ADT
// Constructor
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// inserts a new key k
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n"<<endl;
		return;
	}

	// first insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	//restore heap property if violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// decreases value of key at index 'i' to new_val
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
        //cout<<"underflow"<<endl;
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// store the minimum value and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}

// deletes key at index i
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// recursive method to heapify a subtree with the root at given index
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

// utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


bool Stack::push(int x)
{
	if (top >= (MAX-1))
	{
		cout << "Stack Overflow"<<endl;
		return false;
	}
	else
	{
		a[++top] = x;
		cout<<x <<" pushed into stack\n"<<endl;
		return true;
	}
}

int Stack::pop()
{
	if (top < 0)
	{
		cout << "Stack Underflow"<<endl;
		return 0;
	}
	else
	{
		int x = a[top--];
		return x;
	}
}

bool Stack::isEmpty()
{
	return (top < 0);
}

void init(int n)
{
    //initialize queue1
	for(int i=2;i<=n;i++)
	{
	h.insertKey(i);
	}
	//cout << h.extractMin() << " ";
	//cout << h.getMin() << " "<<endl;
	//h.decreaseKey(2, 1);
	//cout << h.getMin();
	//MinHeap h2(n-1); //what to give as capacity ???

	//struct Stack s;
	//s.push(10);
	//s.push(20);
	//s.push(30);
	//cout<<s.pop() << " Popped from stack\n";

}

void main_insert(int x)
{
    h2.insertKey(x);
}

void main_save(int x)
{
    s.push(x);
}

void main_restore()
{

    while(!(s.isEmpty()))
    {
        int k = s.pop();
        h.insertKey(k);
    }
}

int main_invsucc(int x)
{
    //cout<<"heap 1 size= "<<h.heap_size<<endl;
    //cout<<"heap 2 size= "<<h2.heap_size<<endl;
    while(h.getMin()<=x)
    {
        h.extractMin();
    }

    if(h2.heap_size>0)
    {
    int current=-1;
    while(h2.getMin()<=h.getMin())
    {

        if(h2.getMin()==h.getMin())
        {
            if(h2.getMin()==current)
            {
                break;
            }
            h.extractMin();
        }
        current=h2.extractMin();
    } //end of while
    }//end of if
    int y2=h.extractMin();
    return y2;
}

void linearsieve()
{
     init(n); //for initialization of data structure
     int p=1;
     int q,p2;
     int count=0;
     while (p<=sqrt(n))
     {
         p2 = main_invsucc(p);
         cout<<"Prime number : "<<p2<<endl;
         count++;
         p=p2;
         q=p2;
         cout<<"p is "<<p<<endl;
         cout<<"q is "<<q<<endl;
         while((p*q)<=n)
         {
             float ul = ((log(n)-log(q))/log(p));
             for(int r=1;r<=ul;r++)
             {
                 main_insert((pow(p,r)*q));
             }
             q=main_invsucc(q); //q is updated
             cout<<"p is "<<p<<endl;
             cout<<"q is "<<q<<endl;
             main_save(q);
         }
        main_restore();

     }//end of outer while loop

     //printing results
     while(p<=n) //printing primes in range (sqrt(N),N]
        {
             p=main_invsucc(p);
             if(p<=n)
             {
                 cout<<"printing prime =  "<<p<<endl;
                 count++;
             }
        }
} // end of function

// Driver program to test above functions
int main()
{
    linearsieve();
	return 0;
}
