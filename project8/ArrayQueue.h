/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name:Mark Davis
 * Date:April 7 2015
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast-1] == getLast().
 * 
 *  (When I am not empty:
 *     myFirst is the index of my oldest value;
 *     myLast is the index of the spot where the next
 *       item to be appended will be placed.)      
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include <cstring>

template<class Item>
 
class ArrayQueue {
public:

	ArrayQueue(unsigned capacity);
	ArrayQueue(const ArrayQueue& original);
	void makeCopyOf(const ArrayQueue& original);
	virtual ~ArrayQueue();
	ArrayQueue& operator=(const ArrayQueue& original);
	unsigned getSize() const;
	unsigned getCapacity() const;
	bool isEmpty() const;
	bool isFull() const;
	unsigned getFirst() const;
	unsigned getLast() const;
	void append(const Item& it);
	void setCapacity(unsigned newCap);
	Item remove();

protected:
//	virtual void makeCopyOf(const ArrayQueue& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirst;      // index of oldest item (if any)
	unsigned myLast;       // index of next available spot for append (if any)
	Item*    myArray;      // dynamic array of items

	friend class ArrayQueueTester;
};

template<class Item>
ArrayQueue<Item>::ArrayQueue(unsigned capacity) {
	if (capacity <= 0 ) {
		throw QueueException("ArrayQueue constructor()", "capacity must be positive");
	}
	else {
		mySize = 0;       // number of items I contain
		myCapacity = capacity; // how many items I can store
		myFirst = 0;   // index of oldest item (if any)
		myLast = 0;       // index of next available spot for append (if any)
		myArray = new Item[capacity];
	}

}

template<class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue<Item>& original) {
	makeCopyOf(original);
}

template<class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue<Item>& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirst = original.myFirst;
	myLast = original.myLast;
	myArray = new Item[myCapacity];
	memcpy(myArray, original.myArray, myCapacity*sizeof(Item) );
}

template<class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArray;
	myArray = NULL;
	mySize = myFirst = myLast = 0;
}

template<class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue<Item>& aQueue) {
	if (this != &aQueue) {
		delete [] myArray;
		makeCopyOf(aQueue);
	}
	return *this;
}

template<class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}

template<class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

template<class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

template<class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

template<class Item>
unsigned ArrayQueue<Item>::getFirst() const {
	if ( isEmpty() ){
		throw EmptyQueueException("getFirst() - queue is empty");
	}
	return myArray[myFirst];
}

template<class Item>
unsigned ArrayQueue<Item>::getLast() const {
	if ( isEmpty() ) {
		throw EmptyQueueException("getLast() - queue is empty");
	}
	return myArray[(myLast-1+myCapacity) % myCapacity];
}

template<class Item>
void ArrayQueue<Item>::append(const Item& it) {
	if( isFull() ) {
		throw FullQueueException("append() - queue is full!");
	}
	myArray[myLast] = it;
	mySize++;
	myLast = (myLast +1) % myCapacity;
}

template<class Item>
Item ArrayQueue<Item>::remove() {
	if ( isEmpty() ) {
		throw EmptyQueueException("remove() - queue is empty");
	}
	else {
		unsigned result = myArray[myFirst];
		myFirst = (myFirst+1) % myCapacity;
		mySize--;
		return result;
	}
}

template<class Item>
void ArrayQueue<Item>::setCapacity(unsigned newCap) {
	if ( newCap == 0 || newCap < getSize() ) {
		throw QueueException("setCapacity()", "capacity must be positive!");
	}
	else {
		Item* newArray = new Item[newCap];
		for ( unsigned i = 0; i < getSize(); i++ ) {
			newArray[i] = myArray[myFirst]; //maybe modulus this
			myFirst++;
		}
		for ( unsigned i = getSize(); i < newCap; i++ ) {
			newArray[i] = 0;
		}
		myCapacity = newCap;
		myFirst = myArray[0];
		myLast = getSize();
		delete [] myArray;
		myArray = newArray;
	}
}

#endif /*ARRAY_QUEUE_H_*/
