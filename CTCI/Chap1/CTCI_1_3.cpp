/* URLify: Write a method to replace all spaces in a string with '%20'. You may assume that the string
has sufficient space at the end to hold the additional characters, and that you are given the "true"
length of the string. (Note: If implementing in Java, please use a character array so that you can
perform this operation in place.) */

#include <map>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>


// replaces all spaces with %20
void replace_spaces(std::string& input_string, int num_char) {

    // check for empty
    if (num_char == 0) { return; }
    if (input_string.empty()) { return; }

    // initialize 2 pointers and count
    int curr = 0;
    int prev = 0;
    int total_char = num_char;
//    unsigned int count = 0;

    // iterate till we reach num_char
    while (curr < total_char) {

        // if curr finds a white space, increment curr
        while (input_string.at(curr) == ' ') {
            curr++;
        }

        // if there was white space, replace and update
        if (curr != prev) {
            input_string.replace(prev, curr - prev, "%20");

            // increase the total char count.
            total_char += curr - prev + 1;
            prev = curr;

        }

        curr++; prev++;
    }

    std::cout << prev << " " << curr << '\n';
    if (curr != prev) {
        input_string.replace(prev, curr - prev, "%20");
        prev = curr;
    }

}


// TESTING

int main(){

    std::string test("hi lol  jogn sp ic");
    std::cout << test << '\n';
    replace_spaces(test, 13);

    std::cout << test << '\n';


    return 0;
}
