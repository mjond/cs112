/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */

#include "Stack.h"

/* explicit-value constructor
 * Parameter: size, an unsigned value.
 * Precondition: size > 0.
 * Postcondition: myTop == 0 && myCapacity == size
 *              && myArray contains the address of a dynamic array of 'size' entries.
 */
Stack::Stack(unsigned size) {
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
Stack::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
void Stack::makeCopyOf(const Stack& original) {
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
Stack::~Stack() {
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
Stack& Stack::operator=(const Stack& original) {
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
bool Stack::isEmpty() {
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
bool Stack::isFull() {
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
void Stack::push(const Item& it) {
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
Item& Stack::getTop() const{
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
Item Stack::pop() {
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
unsigned Stack::getSize() const {
	return myTop;
}

/* getCapacity()
 * Parameter: none
 * Postcondition: returns the capacity of the stack
 */
unsigned Stack::getCapacity() const {
	return myCapacity;
}

/* setCapacity()
 * Parameter: unsigned int for the new capacity
 * Postcondition: a new stack with new capacity
 */
void Stack::setCapacity(unsigned newCapacity) {
	if ( newCapacity < 0 ) {
		throw StackException("setCapacity()", "capacity must be positive!");
	}
	else if ( newCapacity < getSize() ) {
		throw StackException("setCapacity()", "new capacity must be bigger than original size!");
	}
	else {
		Item newArray[newCapacity];
		for ( unsigned i = 0; i < newCapacity; i++ ) {
			newArray[i] = myArray[i];
		}
		delete [] myArray;
		myArray = newArray;
		delete [] newArray;
	}
}
