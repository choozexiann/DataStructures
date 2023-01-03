/* String Compression: Implement a method to perform basic string compression using the counts
of repeated characters. For example, the string aabcccccaaa would become a2blc5a3. If the
"compressed" string would not become smaller than the original string, your method should return
the original string. You can assume the string has only uppercase and lowercase letters (a - z). */


#include <map>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

// first idea is definitely 2 pointers and replace.

std::string CompressString(const std::string& input_str) {

    // initialize both pointers
    std::string::const_iterator prev = input_str.cbegin();
    std::string::const_iterator curr = input_str.cbegin();

    std::string output_str;

    // iterate through input

    while (prev != input_str.cend()) {

        // check for start of string:
        unsigned int count = curr == input_str.cbegin() ? 0 : 1;

        // when the letters consecutively are the same, increment both curr and count
        while (*curr == *prev && curr != input_str.cend()) { count++; curr++; }

        // using stringstream to append to the output str.
        std::ostringstream oss;
        oss << *prev << std::to_string(count);
        output_str.append(oss.str());

        if (curr == input_str.cend()) { break; }
        prev = curr; curr++;
    }

    // check that string returned is indeed smaller
    return output_str.length() <= input_str.length() ? output_str : input_str;

}

int main() {

    assert(CompressString("aabcccccaaa") == "a2b1c5a3");
    assert(CompressString("lllllllwwees") == "l7w2e2s1");
    assert(CompressString("abcdefghijk") == "abcdefghijk");

    return 0;
}
