
/* Simple Templated Array resizing class for fun */

#pragma once

#include <utility>
#include <string>

namespace chapter_03{
    template <typename T>
    class SimpleArray {
        private:
            unsigned int capacity_ = 2;
            unsigned int size_ = 0;
            T* data_ = new T[capacity_];

        public:

            // ===== CLASS ADMIN =====
            SimpleArray<T>() = default;
            SimpleArray<T>& operator= (const SimpleArray<T>& source);
            SimpleArray<T>(const SimpleArray<T>& source) { *this = source; }
            SimpleArray<T>& operator= (SimpleArray<T>&& source);
            SimpleArray<T>(SimpleArray<T>&& source);

            ~SimpleArray<T>() { Clear(); }
            void Clear() { delete[] data_; data_ = nullptr; }

            // ====== GETTER/SETTER ======
            unsigned int getSize() const { return size_; }
            unsigned int getCapacity() const { return capacity_; }
            T* getData() const { return data_; }
            void setCapacity(unsigned int new_capacity) { capacity_ = new_capacity; }

            // ====== PUB MEM FUNCTIONS ======
            void resize();
            void push(const T& data);
            void debugPrint() const;
            T pop();
            T getElement(unsigned int index) const { return data_[index]; }


    }; // class SimpleArray


// MARK: CLASS ADMIN =========================================================================================================

/**
 * @brief Deep Copy Assignment
*/
template <typename T>
SimpleArray<T>& SimpleArray<T>::operator= (const SimpleArray& source) {

    if (this == &source) { return *this; }
    Clear();

    // copy priv members
    capacity_ = source.getCapacity(); size_ = source.getSize();

    // iterate through source.data_ and copy over.
    data_ = new T[capacity_];
    T* source_data = source.getData();
    for( unsigned int i = 0; i < source.getsize(); i += 1) { data_[i] = source_data[i]; }

    return *this;
}

/**
 * @brief Move Assignment
*/
template <typename T>
SimpleArray<T>& SimpleArray<T>::operator= (SimpleArray&& source) {

    if (this == &source) { return *this; }
    Clear();

    // copy priv members
    capacity_ = source.getCapacity(); size_ = source.getSize();

    // Move pointers around
    data_ = source.getData();
    source.Clear();
    return *this;
}

/**
 * @brief Move Constructor
*/
template <typename T>
SimpleArray<T>::SimpleArray(SimpleArray&& source) {

    Clear();

    // copy priv members
    capacity_ = source.getCapacity(); size_ = source.getSize();

    // Move pointers around
    data_ = source.getData();
    source.Clear();

}



// MARK: PUBLIC MEM FUNCTIONS =================================================================================================

/**
 * @brief Pushes element onto stack
*/
template <typename T>
void SimpleArray<T>::push(const T& data) {

    // allocate element to data
    data_[size_] = data;
    size_ += 1;

    // call resize if needed
    if (size_ == capacity_) { resize(); }
}

/**
 * @brief Grows the SimpleArray by twice it's size. Used when size == capacity after a push
*/
template <typename T>
void SimpleArray<T>::resize() {

    // create temp storage
    setCapacity(capacity_ * 2);
    T* temp_data = new T[capacity_];

    // move elements over
    for (unsigned int i = 0; i < size_; i += 1) {
        temp_data[i] = std::move(data_[i]);
    }

    delete[] data_;
    data_ = temp_data;
}

/**
 * @brief pops top element (does not deallocate!)
 * @return top element
*/
template <typename T> 
T SimpleArray<T>::pop(){ size_ -= 1; return getElement(size_ + 1); }

/**
 * @brief print for debugging
*/
template <typename T>
void SimpleArray<T>::debugPrint() const {
    printf("=========== SimpleArray ============\n");
    for (unsigned int i = 0; i < size_; i += 1) {
        printf("Element %u: \t Data: %s \n", i, std::to_string(data_[i]).c_str());
    }
}


}; // namespace chapter_03

