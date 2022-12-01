#include <cassert>
#include <map>
#include <list>


// Plan: progress through the LL and node down the node datas in a temp buffer
// Remove nodes which are dupes.

template <typename T>
void RemoveDuplicates(std::list<T> input_list) {

    if (input_list.empty()) { return; }
    // initialize map to store counts in input_list
    std::map<T,int> counter;

    // iterate through the list
    for (auto curr = input_list.begin(); curr != input_list.end(); curr++) {

        // check for contains. Removes if it does
        if (counter.count(*curr)) {

            // remove element in list
            auto temp = curr++;
            input_list.erase(curr);
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
    RemoveDuplicates(lst);
    assert(lst.size() == 4);

    std::list<int> lst2;
    lst2.push_back(3);
    lst2.push_back(4);
    lst2.push_back(3);
    lst2.push_back(3);
    lst2.push_back(3);
    lst2.push_back(3);
    RemoveDuplicates(lst2);
    assert(lst2.size() == 2);

    return 0;
}
