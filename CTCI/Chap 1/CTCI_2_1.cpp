
/* R􀂧mov􀂧 Dups! Write code to remove duplicates from an unsorted linked list. */


#include <cassert>
#include <map>
#include <list>


// Plan: progress through the LL and node down the node datas in a temp buffer
// Remove nodes which are dupes.

template <typename T>
void RemoveDuplicates(std::list<T> input_list) {

    // initialize map to store counts in input_list
    std::map<T,int> counter;

    std::list<T>::iterator prev = input_list.begin();

    // iterate through the list
    for (auto curr = input_list.begin(); curr != input_list.end(); i++) {

        // check for contains. Removes if it does
        if (counter.contains(*curr)) {

            // remove element in list
            auto temp = curr++;
            list.erase(curr);
            curr = temp;
        }

        // increment the map
        else { counter[*curr]++; }
    }

}



int main() {

    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(2);

    assert(lst.size() == 4);

    return 0;
}
