
#include <cassert>
#include <list>
#include <iterator>
#include <iostream>

// Plan: progress through the LL and node down the node datas in a temp buffer
// Remove nodes which are dupes.

// remove without buffer (sadly) takes O(N^2) if we do not use a temp buffer.
// brute force method of searching entire list for every node we encounter if theres a dupe.
template <typename T>
void RemoveDuplicates(std::list<T> input_list) {

    // eliminate non possibilities
    if (input_list.empty()) { return; }

    // iterate through the list
    for (auto curr = input_list.begin(); curr != input_list.end(); curr++) {

        // look ahead and delete one in advance of iter
        for (auto it = ++curr; it != --input_list.end(); it++) {
            std::cout << *it << '\n';
//            if (++it == input_list.end()) { break; }

            // check to see if dupe. If dupe we delete
            std::list<T>::iterator future = it;
            std::next(future);

            if (*future == *curr) { 
                input_list.erase(future); 
            }
            it++;

        }

        if (curr == input_list.end()) { break; }

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

//    std::list<int> lst2;
//    lst2.push_back(3);
//    lst2.push_back(4);
//    lst2.push_back(3);
//    lst2.push_back(3);
//    lst2.push_back(3);
//    lst2.push_back(3);
//    RemoveDuplicates(lst2);
//    assert(lst2.size() == 2);

    return 0;
}
