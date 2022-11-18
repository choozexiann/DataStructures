

#ifndef MERGE_SORT_ITERATOR_H
#define MERGE_SORT_ITERATOR_H

/* Copy of the most broken stuff ive seen */

#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>

// Generic template for merge sort. This will BT is the typename for the iterator for type T, which is of type T iterator
template <typename T, typename BT>
void merge(T begin, T mid, T end, BT begin_buffer) {

    // initialize variables
    T low = begin;
    T high = mid;
    BT buf = begin_buffer;

    // iterate through the current range in the T array
    while (low < mid && high < end) {

        // parallel array increments based on comparison of the two elements within the 2 arrays
        if (*low <= *high) {

            // swaps values of the elements the given iterators are pointing to.
            std::iter_swap(low, buf);

            // increment low
            low++;
        }

        // swaps values of the elements the given iterators are pointing to.
        else {
            std::iter_swap(high, buf);
            high++;
        }

        // increment buf
        buf++;
    }

    // at the endof the while loop, buf iter basically contains pointers to elements in order.

    // std::move takes range of elements to move between 2 its, beginning of destination range it
    std::move(low, mid, buf);
    std::move(high, end, buf);

    size_t size = std::distance(begin, end);
    std::move(begin_buffer, std::next(begin_buffer, size), begin);
}

template <typename T, typename BT>
void merge_sort_buffer(T begin, T end, BT begin_buffer) {

    // get distance between the iterators in the input array
    size_t size = std::distance(begin, end);

    // returns if the array is just of size 1
    if (size < 2) {
        return;
    }

    // creates variables that point to middle portion of the buffer
    size_t split = size/2;
    T mid = std::next(begin, split);
    BT mid_buffer = std::next(begin_buffer, split);

    // recursively call merge_sort onto the left part and the right part of the buffer
    merge_sort_buffer(begin, mid, begin_buffer);
    merge_sort_buffer(mid, end, mid_buffer);

    // merge together the two results
    merge(begin, mid, end, begin_buffer);
}

template <typename T>
void merge_sort (T begin, T end) {

    using valuetype = typename std::iterator_traits<T>::value_type;
    size_t size = std::distance(begin, end);
    std::vector<valuetype> buffer(size);

    merge_sort_buffer(begin, end, std::begin(buffer));
}



#endif // MERGE_SORT_ITERATOR_H



int main() {



    std::vector<int> a = {3, 0, 7, 5, 7, 8, 3, 1};
    merge_sort(std::begin(a), std::end(a));
    std::copy(std::begin(a), std::end(a),
              std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n";


return 0;}
