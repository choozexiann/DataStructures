/* 3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in 0(1) time. */

/* Initial solution to try a min element field ?*/

#include <iostream>
#include <stack>

/**
 * @brief Implemented
*/
template <typename T>
class StackMin{

public:

    // ===== CLASS ADMIN =====
    StackMin<T>() = default;
    StackMin<T>& operator=(const StackMin<T>& source);
    ~StackMin<T>() = default;

    // ====== PUBLIC MEMBER FUNCTIONS =====
    void push(T data);
    T peek(); 
     

private:

    // ===== PRIVATE DATA MEMBERS =====

    std::stack<T> mins_;
    std::stack<T> data_;

}; // class StackMin


// MARK: CLASS ADMIN ==========================================================================================

/**
 * @brief Copy Constructor
*/
template <typename T>
StackMin<T>& StackMin::operator=(const StackMin<T>& source) {

if (*this == source ) { return; }

// Copy over data members
mins_ = source.mins_;
data_ = source.data_;


}




// MARK: PUBLIC CLASS MEMBER FUNCTIONS =============================================================================================


int main() {


    return 0;
}