/* Three in One: Describe how you could use a single array to implement three stacks. */

/*
After seeing the hints, it seems that I will have to implement an array with some sort of "wrapping around".
This means that it should be in the free store? I'm not too sure but I will code and see if I come up with some sort of magic


I am ripping off tusharchugh's repo here: https://github.com/TusharChugh/ctci-modern_cplusplus/blob/master/include/stacks_queues/three_one.h
*/


#include <vector> 
#include <stdexcept>
#include <iostream>




// MARK: STACKARRAY CLASS ====================================================================================
/**
 * @brief StackArray class which is able to implement three stacks in an array.
*/
template <typename T>
class StackArray{

public:

    // ===== USINGS ======

    using value_type = typename std::vector<T>::value_type;
    using size_type = typename std::vector<T>::size_type;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;

    // ===== CLASS ADMIN ======

    /**
     * @brief StackArray constructor
     * @param num_stacks num of stacks
     * @param stack_capacity capacity of the stack
    */
    explicit StackArray( size_type num_stacks, size_type stack_capacity )
        : num_stacks_( num_stacks ), stack_capacities_( num_stacks, stack_capacity ), 
        sizes_( num_stacks ), data_( num_stacks * stack_capacity ) {}


    /**
     * @brief StackArray constructor
     * @param stack_capacities vector containing indiv info on stack capacities as well as num stacks
    */
    explicit StackArray(const std::vector<size_type>& stack_capacities)
        : num_stacks_( stack_capacities.size() ), stack_capacities_( stack_capacities ), sizes_( num_stacks_ ) {

        unsigned int total_capacity = 0;
        for ( auto& num : num_stacks_ ) { total_capacity += num; }

        // reserve basically tells the vector to resize if needed
        data_.reserve( total_capacity );
    }


private:

    // ===== USINGS ======
    using iterator = typename std::vector<T>::iterator;

    // ===== PRIVATE DATA MEMBERS =====

    const size_type num_stacks_;

    // stores the capacities of the respective stacks
    std::vector<size_type> stack_capacities_;

    // stores the sizes of the respective stacks
    std::vector<size_type> sizes_;
    std::vector<T> data_;


// MARK: PRIVATE FUNCTION DEFINITIONS =========================================================================================================

    /**
     * @brief returns the index of the top element wrt a stack_id
     * @param stack_id - the index of the stack we are referring to
     * @return index of top element
    */
    size_type indexOfTop (size_type stack_id) const {

        // offset is 
        size_type offset = stack_id * stack_capacities_.at[stack_id];
        size_type size = sizes_.at(stack_id);

        return offset + size - 1;
    }

    /**
     * @brief returns a bool on whether the given stack is full
     * @param stack_id index of stack
     * @return bool if it is true that stack is full
    */
    bool isFull (size_type stack_id) {
        
        size_type size = sizes_.at(stack_id);
        size_type capacity = stack_capacities_.at(stack_id);
        return size == capacity;
    }


public: 
// MARK: PUBLIC FUNCTION DEFINITIONS =========================================================================================================

    /**
     * @brief returns reference to data at top of stack_id
    */
    inline reference top ( size_type stack_id ) {

        if ( isEmpty( stack_id ) ) { throw std::runtime_error( "Stack is empty!" ); }
        return data_.at( indexOfTop( stack_id ) );

    }

    /**
     * @brief returns const reference to data at top of stack_id
    */
    inline const_reference top ( size_type stack_id ) const {

        if ( isEmpty( stack_id ) ) { throw std::runtime_error( "Stack is empty!" ); }
        return data_.at( indexOfTop( stack_id ) );

    }

    /**
     * @brief pushes element onto stack of stack_id
     * @param data data to be pushed
    */
    inline void push ( size_type stack_id, const value_type& data ) {
        if ( isFull( stack_id ) ) { throw std::runtime_error( "Stack is Full! " ); }
        sizes_.at( stack_id ) += 1;
        data_.at ( indexOfTop(stack_id) ) = data;
    }

    /**
     * @brief move semantics for push
     * @param data data to be pushed
    */
    inline void push ( size_type stack_id, value_type&& data ) {
        if ( isFull( stack_id ) ) { throw std::runtime_error( "Stack is Full! " ); }
        sizes_.at( stack_id ) += 1;
        data_.at ( indexOfTop(stack_id) ) = std::move( data );
    };

    /**
     * @brief pop stack
     * @param stack_id stack to be popped
    */
    inline void pop ( size_type stack_id ) {
        if( isEmpty( stack_id ) ) { throw std::runtime_error ("Stack is Empty!"); }
        data_.erase ( static_cast<iterator>( indexOfTop( stack_id  ) ) );
        sizes_.at( stack_id ) -= 1;
    }

    /**
     * @brief prints all of data_. also prints out stack ids and indexes
    */
    void printStacks() {

        printf("Data: \n");
        unsigned int count = 0;
        for ( auto& num : data_ ) { count++; printf( "%s ", std::to_string(num).c_str() ); if(count % 70 == 0) printf("\n"); } 

        count = 1;
        for ( auto& stack_size : sizes_ ) { 
            if ( stack_size == 0 ) continue;
            printf( "\nStack %u starts a index: %u ", count,  indexOfTop( count ) );
            count += 1;
        } 
    }

};



int main() {


    StackArray test = StackArray<int>( 3, 100 );
    test.push(0, 10);
    test.push(1, 10);
    test.push(1, 10);
    test.push(2, 10);
    // test.push(1, 10);
    // test.push(2, 10);
    // test.push(1, 10);
    test.printStacks();


    return 0;
}
