
/* Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees. Can you do this in place? */


#include <map>
#include <algorithm>
#include <string>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>


// Templated will be better for flexible input size but this will suffice
void RotateMatrix(int input_arr[4][4]) {

    // algo will be to shift layer by later. In this case we do it for a 4x4 matrix
    // magic 4 but in this case just to prove we can do it with n
    int n = 4;

    // iterate till n/2 to only do 90 deg rotate
    for (unsigned int layer = 0; layer < n/2, layer++) {

        // 0 to 3, then 2 to 2.
        int first_element = layer;
        int last_element = n - layer - 1;

        // shifting through for loop
        for (unsigned int i = first_element, i < last_element, i++) {

            // save top to temp obj

            int temp = input_arr[first_element][i];

            // shift left to top
            input_arr[first_element][i] = input_arr[last_element - i + first_element][first_element];

            // shift bot to left
            input_arr[last_element - i + first_element][first_element] = input_arr[last_element - i + first_element];


            // shift top -> right
            input_arr[i][last_element]

// I GIVE UP

        }


    }






}


int main() {

    int arr[4][4]  = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };


    RotateMatrix(arr);

    return 0;
}
