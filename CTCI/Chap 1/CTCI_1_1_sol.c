
/* Proper Solution */


#include <string>

unsigned int isUniqueChars(std::string input_string) {

    // checked if this is ascii or unicode string.
    // Unicode contains 149,186 chars
    // ASCII contains just 128.

    // Check if this is not allowed in ascii
    if (input_string.length() > 128) { return false; }

    // initialize the index of all unique characters
    bool[] all_chars* = new bool[128] {false};

    // iterate through the string
    for (unsigned int i = 0; i < input_string.length(); i++) {

        // return false if there alr is the char
        if (all_chars[i]) { return false; }

        // else update to true
        else { all_chars[i} = true; }
    }

    // returns true when it goes through entire string.

    return true;
}

int main() {


    std::string test_string = "asdfghjkl";
    assert (isUniqueChars(test_string));
    std::string test_string2 = "asdfghjkasdl";
    assert (!isUniqueChars(test_string2));









}
