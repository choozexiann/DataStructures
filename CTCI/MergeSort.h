#ifndef MERGESORT_H
#define MERGESORT_H

#include <string>
// MergeSort algorithm which is able to sort any array which is made of comparable datatype.
/*

The general pseudo-code for the merge sort technique is given below.

Declare an array Arr of length N
If N=1, Arr is already sorted
If N>1,
Left = 0, right = N-1
Find middle = (left + right)/2
Call merge_sort(Arr,left,middle) =>sort first half recursively
Call merge_sort(Arr,middle+1,right) => sort second half recursively
Call merge(Arr, left, middle, right) to merge sorted arrays in above steps.
Exit
*/

// Determines size of the input_arr we are not given one.
//template <typename T, unsigned int N>
//void merge_sort(T (&input_arr)[N]) {
//
//    // uses sizeof to give length into the merge_sort call.
//    merge_sort(input_arr, static_cast<unsigned int> (sizeof(input_arr)/sizeof(input_arr[0])));
//}

template <typename T>
void merge_sort(T* input_arr, unsigned int length) {

    // calls recursive function
    T test[] = *input_arr;
    merge_sort(test, (unsigned int)0, length - 1);
}

// merge_sort which takes in args of the indexes of the L and R elements in input_arr
template <typename T>
void merge_sort(T* input_arr, unsigned int left, unsigned int right) {

    // base case: when L = R there is only 1 element, which means the array is sorted
    if (left == right) { return; }

    // Find the mid index
    unsigned int mid = (left + right) / 2;

    // call merge_sort() recursively on the 2 different parts of the arr.
    // Left portion:
    merge_sort(input_arr, left, mid);

    // Right portion:
    merge_sort(input_arr, mid + 1, right);

    // Merge the two sorted arrays back.
    merge(input_arr, mid, right);


}

// merges the subarrays together. The arrays should
template <typename T>
void merge(T* input_arr, unsigned int left, unsigned mid, unsigned int right) {

    // unfortunately, for c++ we have to create a dynamically allocated object here to store the elements
    // temp_arr is pointer to a deep copy of input_arr.
    T* temp_arr = new T [right - left + 1];
    for (unsigned int i = 0; i < right - left + 1; i++) {
        temp_arr[i] = input_arr[left + i];
    }

    // parallel incrementation of the 2 sub arrays.
    // initialize counters in both subarrays
    unsigned int idx_left = left; unsigned int idx_right = mid + 1;

    // iterate through entire subarray given as temp_arr
    while (right - left + 1 > idx_left + idx_right) {

        // iterate through left subarray and add to input_arr
        if (temp_arr[idx_left] <= temp_arr[idx_right]) {

            // add to input_arr
            input_arr[idx_left + idx_right] = temp_arr[idx_left];

            // increment idx_left
            idx_left++;
        }

        // iterate through right subarray and add to input_arr
        if (temp_arr[idx_right] < temp_arr[idx_left]) {

            // add to input_arr
            input_arr[idx_left + idx_right] = temp_arr[idx_right];

            // increment idx_left
            idx_right++;
        }
    }

    // delete temp_arr
    delete[] temp_arr;
}

// print_arr for Debugging/ Testing
template <typename T>
void print_arr(T input_arr[]) {

    // uses sizeof to give length into the print_arr call.
    print_arr(input_arr, static_cast<unsigned int> (sizeof(input_arr)/sizeof(input_arr[0])));
}

template <typename T>
void print_arr(T input_arr[], unsigned int length) {
    printf("\n");
    for (unsigned int i = 0; i < length; i++) {
        printf("Element at position %u is %s\n", i, std::to_string(input_arr[i]).c_str());
    }
}

#endif










