

/* Check Permutation: Given two strings, write a method to decide if one is a permutation of the
other. */

// Idea: just assign all into a hashmap and check counts accordingly.

#include <map>
#include <string>
#include <iostream>
#include <cassert>


// returns a bool on whether the two strings are permutations
bool isPermutation(std::string lhs, std::string rhs) {

    // check for if they are equal to empty string. if so, return false.
    if (lhs == "" || rhs == "") { return false; }

    // create a hashmap with key v pair of char, count
    std::map<char, int> char_counts;

    // iterate through lhs insert each char into char_counts.
    // Also, update the counts accordingly.
    for (const auto& character: lhs) {

        // increment map
        char_counts[character]++;
    }

    // iterate through rhs and decrement char_counts.
    // If it reaches negative, immediately reutrn false
    for (const auto& character: rhs) {

        // decrement map
        char_counts[character]--;

        // check for if it is negative
        if (char_counts[character] < 0) { return false; }
    }

    // IF we reach here, iteate through all values and ensrue they are 0.
    for (const auto& i: char_counts) {
        if (i.second != 0) { return false; }
    }

    // return true if all checks pass
    return true;
}






// ===== tests =======
int main() {

    std::string test_str1 = "hello world";
    std::string test_str2 = "wollo herld";
    std::string test_str3 = "heasdasdasd";

    assert(isPermutation(test_str1, test_str2));
    assert(!isPermutation(test_str1, test_str3));
    assert(!isPermutation(test_str2, test_str3));


return 0;
}
