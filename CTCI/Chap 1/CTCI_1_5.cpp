/* One Away: There are three types of edits that can be performed on strings: insert a character,
remove a character, or replace a character. Given two strings, write a function to check if they are
one edit (or zero edits) away. */


#include <map>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>
#include <iterator>



// handles when string length is same.
bool StringLengthSame(const std::string& s1, const std::string& s2) {

    bool found_diff = false;

    // iterates through the strings
    for (unsigned int i = 0; i < s1.length(); i++) {

        // allows one difference.
        if (s1.at(i) != s2.at(i) && !found_diff) {
            found_diff = true;
        }

        else if (s1.at(i) != s2.at(i) && found_diff) {
            return false;
        }
    }

    return true;
}


// when the string lengths are diff
bool StringLengthDifferent(const std::string& s1, const std::string& s2) {

    // iterates through both strings and only allows for 1 found difference.
    std::string shorter_str = s1.length() > s2.length() ? s2 : s1;
    std::string longer_str = s1.length() > s2.length() ? s1 : s2;
    unsigned int short_idx = 0; unsigned int long_idx = 0;

    bool found_diff = false;

    while (short_idx < shorter_str.length() && long_idx < longer_str.length()) {

        // if found diff increment longer str index by 1 and continue while
        if (shorter_str[short_idx] != longer_str[long_idx] && !found_diff) {
            found_diff = true;
            long_idx++; continue;
        }

        // throws false when theres more than 1 diff
        else if (shorter_str[short_idx] != longer_str[long_idx] && found_diff) {
            return false;
        }

        short_idx++; long_idx++;
    }

    return true;
}


bool isOneAway (const std::string& s1, const std::string& s2) {

    // check for same string
    if (s1 == s2) { return true; }

    // check for even possible for one away
    if (abs(s1.length() - s2.length()) > 1) { return false; }

    // returns checks from helper funcs
    if (s1.length() == s2.length()) { return StringLengthSame(s1, s2); }
    else { return StringLengthDifferent(s1, s2); }


    return true;
}
int main() {

    assert(isOneAway("pale", "ple"));
    assert(isOneAway("pales", "pale"));
    assert(isOneAway("pale", "bale"));
    assert(!isOneAway("pale", "bake"));

    return 0;
}
