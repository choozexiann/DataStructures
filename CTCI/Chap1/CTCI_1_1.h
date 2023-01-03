
#ifndef CTCI_1_1H

#define CTCI_1_1H

/*
1.1 Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
cannot use additional data structures?
Hints: #44, #7 7 7, #732
*/


// ========== My Solution ==========

/* For part 1, probably going to try to utilize a hashmap and look for .contains(). low key misread the qn ngl*/

#include <map>
#include <iostream>
#include <string>
#include <cassert>

// Time: O(n), Space: O(1)

 unsigned int solution(std::string input_string) {

    // initialize the map for the char_table and res counter
    std::map<char, bool> char_table; unsigned int res = 0;

    // iterate through given string
    for (const char& character: input_string) {

        // check if string is not in hashtable
        if(!char_table.count(character)) {

            // increment res
            res += 1;

            // insert into the char_table
            char_table.insert({character, true});
        }
    }

    // return final count
    return res;
}

#endif // 1_1HPP
