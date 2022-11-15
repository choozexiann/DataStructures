#ifndef HASHNODE_HPP
#define HASHNODE_HPP


// MARK: HASHNODE CLASS ==========================================================================================================================

template <typename K, typename V>
class HashNode {
public:
    // constructors
    HashNode<K,V>() = default;
    HashNode<K,V>(const HashNode<K,V>& source);
    HashNode<K,V>& operator= (const HashNode<K,V>& source);
    ~HashNode<K,V>() = default;

    // paremeterized constructor
    HashNode<K,V>(K key, V value);

    K key_;
    V value_;
    HashNode<K,V>* next_ = nullptr;
};

// HashNode Copy Constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(const HashNode<K,V>& source) {
    *this = source;
}

// HashNode Copy Assignment Constructor 
template <typename K, typename V>
HashNode<K,V>& HashNode<K,V>::operator=(const HashNode<K,V>& source) {

    // check and return if lhs == rhs
    if (this == &source) { return *this; }

    // copy over private members - we do not copy over next_ as it is meaningless.
    key_ = source.key_;
    value_ = source.value_;

    return *this;
}

//  HashNode parameterized constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(K key, V value) : key_(key), value_(value) {}

#endif