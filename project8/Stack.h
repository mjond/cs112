/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Invariant: myTop == 0 && isEmpty() && !isFull()
 *         || myTop == myCapacity && !isEmpty() && isFull()
 *         || myTop > 0 && myTop < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member myTop always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or getTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

//#include "StackException.h"
#include <string>
#include <iostream>
#include "StackException.h"
using namespace std;

template<class Item>

class Stack {
public:
	Stack(unsigned size);
	Stack(const Stack& original);
	~Stack();
	Stack& operator=(const Stack& original);
	bool isEmpty();
	bool isFull();
	void push(const Item& it);
	Item& getTop() const;
	Item pop();
	unsigned getSize() const;
	unsigned getCapacity() const;
	void setCapacity(unsigned newCapacity );
	
protected:
	void makeCopyOf(const Stack& original);
	
private:
	unsigned myCapacity;
	unsigned myTop;
	Item*    myArray;
	friend class StackTester;
};

/* explicit-value constructor
 * Parameter: size, an unsigned value.
 * Precondition: size > 0.
 * Postcondition: myTop == 0 && myCapacity == size
 *              && myArray contains the address of a dynamic array of 'size' entries.
 */
template<class Item>
Stack<Item>::Stack(unsigned size) {
	if ( size > 0) {
		myTop = 0;
		myCapacity = size;
		myArray = new Item[size];
	}
	else {
		throw StackException("Stack(size)", "size must be positive!");
	}

}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
Stack<Item>::Stack(const Stack<Item>& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template<class Item>
void Stack<Item>::makeCopyOf(const Stack<Item>& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	myTop = original.myTop;
}

/* destructor
 * Postcondition: myCapacity == 0 && myTop == 0
 *             && myArray has been deallocated.
 */
template<class Item>
Stack<Item>::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	myTop = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template<class Item>
Stack<Item>& Stack<Item>::operator=(const Stack<Item>& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

/* is Empty method
 * Parameter: none.
 * Postcondition: returns true if stack is empty
 * 				  else it returns false
 */
template<class Item>
bool Stack<Item>::isEmpty() {
	if (myTop == 0) {
		return true;
	}
	else {
		return false;
	}
}

/* is Full method
 * Parameter: none.
 * Postcondition: returns true if stack is full
 * 				  else it returns false
 */
template<class Item>
bool Stack<Item>::isFull() {
	if ( myTop == myCapacity ) {
		return true;
	}
	else {
		return false;
	}
}

/* push method
 * Parameter: an integer to put in the stack
 * Postcondition: the stack contains one more integer
 */
template<class Item>
void Stack<Item>::push(const Item& it) {
	if ( myCapacity == myTop ){
		throw StackException("push()", "stack is full");
	}
	else {
		myArray[myTop] = it;
		myTop++;
	}
}

/* getTop method
 * Parameter: none
 * Postcondition: returns the item at index myTop
 */
template<class Item>
Item& Stack<Item>::getTop() const{
	if (myTop > 0 ){
		return myArray[myTop - 1];
	}
	else {
		throw StackException("getTop()", "stack is empty");
	}
}

/* pop method
 * Parameter: none
 * Postcondition: returns the value of the first element
 */
template<class Item>
Item Stack<Item>::pop() {
	if (myTop == 0){
		throw StackException("pop()", "stack is empty");
	}
	else {
		myTop --;
		return myArray[myTop];
	}
}

/* getSize()
 * Parameter: none
 * Postcondition: returns the size of the stack
 */
template<class Item>
unsigned Stack<Item>::getSize() const {
	return myTop;
}

/* getCapacity()
 * Parameter: none
 * Postcondition: returns the capacity of the stack
 */
template<class Item>
unsigned Stack<Item>::getCapacity() const {
	return myCapacity;
}

/* setCapacity()
 * Parameter: unsigned int for the new capacity
 * Postcondition: a new stack with new capacity
 */
template<class Item>
void Stack<Item>::setCapacity(unsigned newCapacity) {
	if ( newCapacity < 0 ) {
		throw StackException("setCapacity()", "capacity must be positive!");
	}
	else if ( newCapacity < getSize() ) {
		throw StackException("setCapacity()", "new capacity must be bigger than original size!");
	}
	else {
		Item* newArray = new Item[newCapacity];
		for ( unsigned i = 0; i < getSize(); i++ ) {
			newArray[i] = myArray[i];
		}
		for ( unsigned i = getSize(); i < newCapacity; i++ ) {
			newArray[i] = 0;
		}
		delete [] myArray;
		myArray = newArray;
	//
		myCapacity = newCapacity;
	}
}
#endif

