
/* Palindrome Permutation: Given a string, write a function to check if it is a permutation of a palindrome.
A palindrome is a word or phrase that is the same forwards and backwards. A permutation
is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words. */


#include <map>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>
#include <iterator>

// Idea: hash table counter

// For a string to be a palindrome, must %2 == 0 and just 1 letter can be count of 1. ignore white spaces.


// checks map to see if the map represents a possible palindrome
bool isPalindrome(const std::map<char, int>& input_map) {

    // flag for singular isolated char
    bool found_singular = false;

    // iterate through keys in map and ensure that all are mod 0.
     for ( const auto& kv : input_map ) {

        // set found singular to true if we find one
        if (kv.second % 2 == 1) {
            if (found_singular) { return false; }
            else { found_singular = true; }
        }


    }

    // returns true when its all good.
    return true;
}

// Function to be defined below:
bool isPalindromePermutation (const std::string& input_string) {

    // initialize map of char and count
    std::map<char, int> char_counts;

    // iterate through string and increment in char_counts
    for (unsigned int i = 0; i < input_string.length(); i++){

        // ignores white space
        if (input_string.at(i) != ' ') { char_counts[std::tolower(input_string.at(i))]++; }
    }

    if (!isPalindrome(char_counts)) { return false; }

    // returns true when all good.
    return true;

}

// main
int main() {

    assert(isPalindromePermutation("Tact Coa"));
    assert(isPalindromePermutation("ra c e car"));
    assert(isPalindromePermutation("rcaer ca"));
    assert(!isPalindromePermutation("ra cecap"));
    assert(!isPalindromePermutation("amnsdoiqwneqlnwe"));
    return 0;
}
