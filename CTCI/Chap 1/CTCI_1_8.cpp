/* Zero Matrix: Write an algorithm such that if an element in an MxN matrix is 0, its entire row and
column are set to 0. */

#include <iostream>
#include <vector>
#include <algorithm>

void ZeroMatrix(int** arr, int row_size, int col_size) {

    // initialize row and col vectors that contain supposed to be zeroed indexes
    std::vector<int> row_index;
    std::vector<int> col_index;

    // iterate through the array
    for(unsigned int i = 0; i < row_size; i++) {
        for(unsigned int j = 0; j < col_size; j++){

            // check for 0
            if (arr[i][j] == 0) {

                // push back into the vectors
                row_index.push_back(i); col_index.push_back(j);


                // set all chronologically before in the array to 0.
                    for(unsigned int p = 0; p < i; p++) {
                        for(unsigned int q = 0; q < j; q++){
                                arr[p][j] = 0;
                                arr[i][q] = 0;
                        }
                    }
            }
            else {

                // set to 0 if it is supposed to be 0.
                if (std::find(row_index.begin(), row_index.end(), i) != row_index.end() || std::find(col_index.begin(), col_index.end(), j) != col_index.end()) { arr[i][j] = 0; }
            }

        }
    }
}




int main() {

    constexpr int magic_number_row = 5;
    constexpr int magic_number_col = 8;
    int** arr = new int*[magic_number_row];
    for(unsigned int i = 0; i < magic_number_row; i++) {
        arr[i] = new int[magic_number_col];
    }

    for(unsigned int i = 0; i < magic_number_row; i++) {
        for(unsigned int j = 0; j < magic_number_col; j++){
            arr[i][j] = 5;
        }
    }
    arr[3][2] = 0;
    arr[1][1] = 0;
    arr[4][4] = 0;

    ZeroMatrix(arr, magic_number_row, magic_number_col);

    printf("\n");
    for(unsigned int i = 0; i < magic_number_row; i++) {
        for(unsigned int j = 0; j < magic_number_col; j++){
            std::cout << arr[i][j] << " ";
        }
        printf("\n");
    }
    for(unsigned int i = 0; i < magic_number_row; i++) {
            delete[] arr[i];
        }


    return 0;
}
