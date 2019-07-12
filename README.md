# CSE548_AlgorithmAnalysis
hw2: implemented the linear sieve algorithm using two priority queues and a stack. The priority queues were implemented using Minheap.
The main advantage of Linear Sieve (Sieve of Gries and Misra) over the sieve oferatosthenes is that in this sieve, we traverse a composite only once.

hw3: Implemented the Randomized Selection Algorithm
Three cases arise:-
1) If k <n/log n : use min-heap to find the kth smallest element.
2) If k>n-n/log n: use max-heap to find the kth smallest element.
3) Else, use the randomized selection algorithm.

hw4:
a) Implemented parallel selection algorithm. For parallel algorithm implementation, I used Cilk. The three main keywords to be used are
   cilk_for, cilk_spawn and cilk_sync.
  -This algorithm is based on dividing the given array into fixed size groups of five elements, sorting the elements in each group to find    the median and then selecting the median of medians as the pivot.
  -This algorithm gives linear time complexity in worst case.

b) Randomized quicksort to find the kth smallest element.This algorithm is based on using a random pivot element.

c) Parallel selection algorithm that can return the smallest k numbers in an array of n distinctnumbers in sorted order .
   Using Θ (nk) extra space, Θ (nk) work .
   I used PAR_PARTITION and PAR-PREFIX-SUM algorithms as taught in the class for this implementation.

