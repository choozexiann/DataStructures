
/* String Rotation: Assume you have a method i 5Su b 5 tr ing which checks if one word is a substring
of another. Given two strings, 51 and 52, write code to check if 52 is a rotation of 51 using only one
call to i5Sub5tring (e.g., "waterbottle" is a rotation of" erbottlewat"). */


#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>

// isSubString which returns bool if s1 is substr of s2
bool isSubString(const std::string& sub_str, const std::string& ref_string) {
    return ref_string.find(sub_str) != std::string::npos;
}

/* checks to see if s2 is a rotation of s1 with only 1 call to issubstr.
 difiicult prob. I'll try to hit O(M+N) with parallel iteration. Might have to take 2 passes.
this approach turns out to be wrong */

/* the right approach is to understand that the s2 will be a substring of s1 + s1 concatted. (if this is onerotate)
This is because s2 will be the two parts of s1 merged between the 2 concats */


bool isRotation(std::string s1, std::string s2) {

    // elimitate non posibilities
    if (s1.length() != s2.length()) { return false; }
    if (s1 == "") { return false; }

    // concat s1.
    s1.append(s1);

    return isSubString(s2, s1);
}


int main() {

    assert(isRotation("erbottlewat", "waterbottle"));
    return 0;

}
