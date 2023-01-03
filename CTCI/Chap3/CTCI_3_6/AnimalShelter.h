/*

Animal Shelter: An animal shelter, which holds only dogs and cats, operates on a strictly"first in, first
out" basis. People must adopt either the "oldest" (based on arrival time) of all animals at the shelter,
or they can select whether they would prefer a dog or a cat (and will receive the oldest animal of
that type). They cannot select which specific animal they would like. Create the data structures to
maintain this system and implement operations such as enqueue, dequeueAny, dequeueDog,
and dequeueCat. You may use the built-in Linkedlist data structure.

*/

/* TODO: Animal classes to be defined via enum classes */
#pragma once

#include "Queue.h"
#include <string>

namespace chapter_03{

    // enum for the diff species of animals
    enum Species {none, dog, cat};

    // MARK: ANIMAL CLASS ===================================================================================================
    class Animal {
        protected:
        std::string name_;
        Species species_;
        int id_ = 0;
        
        public:

        // ====== CLASS ADMIN =======
        Animal(const std::string& name, int id = 0) 
            : name_(name), id_(id), species_(none) {}

        // ====== PUBLIC MEMBER FUNCS =====
        int getID() const { return id_; }
        void setID(int id) { id_ = id; }
        std::string getName() const { return name_; }
        Species getSpecies() const { return species_; }

    }; // class Animal

    // MARK: SPECIFIC ANIMAL CLASSES ===================================================================================================
    class Dog : public Animal {
        public:
        Dog(const std::string& name, int id = 0) : Animal(name, id) {
            species_ = Species::dog;
        }
    }; // class Dog

    class Cat : public Animal {
        public:
        Cat(const std::string& name, int id = 0) : Animal(name, id) {
            species_ = Species::cat;
        }
    }; // class Cat

    class AnimalShelter{
        private:
            chapter_03::Queue<Cat*> cats_;
            chapter_03::Queue<Dog*> dogs_;
            int curr_id = 0;
        public:
            void enqueue(Animal* ptr_to_animal);
            Cat* dequeueCat() { return cats_.isEmpty() ? nullptr : cats_.dequeue(); }
            Dog* dequeueDog() { return dogs_.isEmpty() ? nullptr : dogs_.dequeue(); }
            Animal* dequeueAny();

    }; // class AnimalShelter

// MARK: ANIMALSHELTER FUNCTIONS ===================================================================================================

/**
 * @brief enqueues cats and dogs into their respective queues
*/
void AnimalShelter::enqueue(Animal* ptr_to_animal) {
    if (ptr_to_animal == nullptr) { return; } 

    // assign ID
    ptr_to_animal->setID(curr_id);
    curr_id += 1;

    // enqueues to diff queues
    switch (ptr_to_animal->getSpecies()) {
    case dog:
        dogs_.enqueue(static_cast<Dog*>(ptr_to_animal));
        std::cout<< "heredog";
        break;
    case cat:
        cats_.enqueue(static_cast<Cat*>(ptr_to_animal));
        break;
    case none:
        throw (std::runtime_error("None Animal Type found!"));
        break;
    }
}

/**
 * @brief dequeues non empty lists if not chooses by rand
 * @return pointer to animal
*/
Animal* AnimalShelter::dequeueAny() {

    if (dogs_.isEmpty() || cats_.isEmpty()) {
        if (dogs_.isEmpty()) {
            std::cout << "here";
            return cats_.isEmpty() ? nullptr : dequeueCat();
        }
        else { return dequeueDog(); }
    }

    // return lowest ID
    if (dogs_.peek()->getID() < cats_.peek()->getID()) {
        return dequeueDog();
    }
    else { return dequeueCat(); }

    return nullptr;
}


}; // namespace chapter_03