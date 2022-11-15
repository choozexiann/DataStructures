

/* Proper Solution */


#include <string>
#include <cassert>

unsigned int isUniqueChars(std::string input_string) {

    // checked if this is ascii or unicode string.
    // Unicode contains 149,186 chars
    // ASCII contains just 128.

    // Check if this is not allowed in ascii
    if (input_string.length() > 128) { return false; }

    // initialize the index of all unique characters
    bool* all_chars = new bool[128]{false};

    // iterate through the string
    for (unsigned int i = 0; i < input_string.length(); i++) {

        // find pos in all_chars
        unsigned int pos = static_cast<unsigned int>(input_string[i]);

        // return false if there alr is the char
        if (all_chars[pos]) { delete[] all_chars; return false; }

        // else update to true
        else { all_chars[pos] = true; }
    }

    // returns true when it goes through entire string.

    delete[] all_chars; return true;
}
unsigned int isUniqueCharsConstrained(std::string input_string) {

    // without data structure

    // Check if this is not allowed in ascii
    if (input_string.length() > 128) { return false; }

    // iterate through the string
    for (unsigned int i = 0; i < input_string.length(); i++) {
        unsigned int count = 0;

        // iterate through rest of the string.
        for (unsigned int j = 0; j < input_string.length(); i++) {

            // increment count when found
            if (input_string[i] == input_string[j]) { count++; }
        }

        // when count exceeds 1 there is a dupe.
        if (count > 1) { return false; }
    }
    // returns true when it goes through entire string.

    return true;
}

int main() {


    std::string test_string = "asdfghjkl";
    assert (isUniqueChars(test_string));
    std::string test_string1 = "qwertyuiop";
    assert (isUniqueChars(test_string));
    std::string test_string2 = "asdfghjkasdl";
    assert (!isUniqueChars(test_string2));
    assert (isUniqueCharsConstrained(test_string));
    assert (isUniqueCharsConstrained(test_string1));
    assert (isUniqueCharsConstrained(test_string2));







}
