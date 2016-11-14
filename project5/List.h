/*
 * List.h
 *lab 5
 *  Created on: Mar 10, 2015
 *      Author: mjd85
 */

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cassert>
using namespace std;
template <class Item>

class List {
public:
	List();
	List(const List<Item>& original);
	List<Item> operator=(const List<Item>& original);
	unsigned getSize() const;
	Item getFirst() const;
	Item getLast() const;
	void append(const Item& it);
	bool operator==(const List<Item>& original) const;
	void insert(const Item& it, int pos);
	void prepend(const Item& it);
	void writeTo(const string& fileName) const;
	void readFrom(istream& in);
	virtual ~List();

	//corey's methods
	void readFrom(const string& fileName);
	int getIndexOf(const Item& it);
	Item& remove(int pos);
	bool operator!=(const List<Item>& list2);
	void writeTo(ostream& out);

private:
	struct Node{
		Item myItem;
		Node * myNext;
		Node();
		Node(Item it, Node * next);
		~Node();
	};
	unsigned mySize;
	Node * myFirst;
	Node * myLast;
	friend class ListTester;
};
template <class Item>
List<Item>::List() {
	mySize = 0;
	myFirst = NULL;
	myLast = NULL;
}
template <class Item>
List<Item>::~List() {

	delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
	myFirst = myLast = NULL; // clear myFirst and myLast (optional)
	mySize = 0;              // clear mySize (optional)
}

template <class Item>
List<Item>::Node::~Node() {
	delete myNext;  // delete the next node, invoking ~Node() in it
	// (does nothing if myNext == NULL)
	myNext = NULL;  // clear myNext (optional)
	myItem = 0;     // clear myItem (optional)
}

template <class Item>
List<Item>::Node::Node() {
	myItem = 0;
	myNext = NULL;
}

template <class Item>
List<Item>::Node::Node(Item it, Node * next){
	myItem = it;
	myNext = next;
}

template <class Item>
unsigned List<Item>::getSize() const{
	return mySize;
}

template <class Item>
Item List<Item>::getFirst() const{
	if ( mySize < 0 || myFirst == NULL){
		throw underflow_error("List::getFirst() is wrong");
	}
	return myFirst->myItem;
}

template <class Item>
Item List<Item>::getLast() const{
	if ( mySize < 0 || myFirst == NULL){
		throw underflow_error("List::getLast() is wrong");
	}
	return myLast->myItem;
}

template <class Item>
void List<Item>::append(const Item& it){
	Node * nodePtr = new Node(it, NULL);
	if( mySize == 0){
		myFirst = nodePtr;
	}
	else {
		myLast->myNext = nodePtr;
	}
	myLast = nodePtr;
	mySize++;
}

template <class Item>
List<Item>::List(const List<Item>& original) {
	myFirst = myLast = NULL;          //  set pointers
	mySize = 0;                       //   and size to 'empty' values
	if (original.getSize() > 0) {     //  if there are nodes to copy:
		Node* oPtr = original.myFirst; //  start at the first node
		while (oPtr != NULL) {         //  while there are more nodes:
			append(oPtr->myItem);       //   append the item in that node
			oPtr = oPtr->myNext;        //   advance to next node
		}
	}
}

template <class Item>
List<Item> List<Item>::operator=(const List<Item>& original) {
	if ( &original != this ) {
		delete this->myFirst;
		myFirst = myLast = NULL;
		mySize = 0;
		if( original.mySize > 0){
			Node * nPtr = original.myFirst;
			while( nPtr != NULL) {
				this->append(nPtr->myItem);
				nPtr = nPtr->myNext;
			}
		}
	}
	return *this;
}

template <class Item>
bool List<Item>::operator==(const List<Item>& original) const {
	/* Equality overload
	 *
	 * @param: list2, a const reference to a List
	 *
	 * @return: true if this and list2 are equal;
	 * 			false if this and list are not equal
	 *
	 * METHOD WRITTEN BY MARK DAVIS
	 */
	//if size is not equal
	if( mySize != original.mySize ) {
		return false;
	}
	//make new nodes to compare
	Node * OnePtr = original.myFirst;
	Node * TwoPtr = myFirst;

	//iterate through the lists
	for ( unsigned i = 0; i < mySize; i++ ) {
		if ( OnePtr->myItem != TwoPtr->myItem ) {
			return false;
		}
		//point to the next node
		OnePtr = OnePtr->myNext;
		TwoPtr = TwoPtr->myNext;
	}
	return true;
}


	/* insert() inserts a Node at a given position
	 *
	 * @param: it, a const reference to an Item
	 * 		   pos, an int
	 *
	 * Postcondition: a Node is added at pos;
	 * 				  mySize is updated
	 *
	 * METHOD WRITTEN BY MARK DAVIS
	 */
	//insert at beginning
template <class Item>
void List<Item>::insert(const Item& it, int pos) {
	Node * nodePtr = new Node(it, NULL);
	int intSize = mySize;
	if (pos <= 0) {
		Node * firstPtr = myFirst;
		nodePtr->myNext = firstPtr;
		myFirst = nodePtr;
		mySize++;
	}
	else if (pos >= intSize) {
		pos = intSize;
		Node * finalNode = myFirst;
		for (int i = 0; i < (pos - 1); i++) {
			finalNode = finalNode->myNext;
		}
		finalNode->myNext = nodePtr;
		myLast = nodePtr;
		mySize++;
	}
	else {
		Node * nodePtr2 = myFirst;
		for (int i = 0; i < (pos - 1); i++) {
			nodePtr2 = nodePtr2->myNext;
		}
		nodePtr->myNext = nodePtr2->myNext;
		nodePtr2->myNext = nodePtr;
		mySize++;
	}
}

template <class Item>
void List<Item>::prepend(const Item& it){
	/* prepend() adds an Item to the front of the list
	 *
	 * @param: it, a const reference to an Item
	 *
	 * Postcondition: a Node with the value it is prepended
	 * 				  to the list
	 *
	 * METHOD WRITTEN BY MARK DAVIS
	 */
	Node * nodePtr = new Node(it, NULL);
		if (mySize == 0) {
			myFirst = nodePtr;
			myLast = nodePtr;
		}
		else {
			nodePtr->myNext = myFirst;
			myFirst = nodePtr;
		}
		mySize++;
	}

template <class Item>
void List<Item>::writeTo(const string& fileName) const {
	/* writeTo() writes a list to a file
	 *
	 * @param: fileName, a const reference to a string
	 *
	 * Postcondition: the list is written to fileName
	 *
	 * METHOD WRITTEN BY MARK DAVIS
	 */
	//open the output stream
	ofstream fout(fileName.c_str());
	//make sure it's open
	assert( fout.is_open() );

	Node * nPtr = myFirst;
	while( nPtr != NULL) {
		//write out the value of the node
		fout << nPtr->myItem << "\t";
		//point to the next node
		nPtr = nPtr->myNext;
	}
	//close the file
	fout.close();
}

template <class Item>
void List<Item>::readFrom(istream& in) {
	/* readFrom() reads a list from a stream
	 *
	 * @param: in, a reference to an istream
	 *
	 * Postcondition: the list is read from in
	 *
	 * METHOD WRITTEN BY MARK DAVIS
	 */

	List<Item> tempList;
		while (in) {
			int it;
			in >> it;
			this->append(it);
		}
		mySize = (mySize - 1);
	}


/* readFrom() reads a list from a file
 *
 * @param: fileName, a const reference to a string
 *
 * Postcondition: the list is read from fileName
 *
 * METHOD WRITTEN BY COREY NOBLE
 */

template <class Item>
void List<Item>::readFrom(const string& fileName) {
	ifstream fin(fileName.c_str());
	List<Item> tempList;
	while (fin) {
		int it;
		fin >> it;
		this->append(it);
	}
	fin.close();
	mySize = (mySize - 1);
}

/* getIndexOf() finds the first occurrence of it
 *
 * @param: it, a const reference to an Item
 *
 * @return: an int position of it
 *
 * METHOD WRITTEN BY COREY NOBLE
 */

template <class Item>
int List<Item>::getIndexOf(const Item& it) {
	Node * nodePtr = myFirst;
	int zero = 0;
	if (nodePtr->myItem == it) {
		return zero;
	}
	else {
		int sizePlusOne = mySize + 1;
		for (int i = 1; i < sizePlusOne; i++) {
			nodePtr = nodePtr->myNext;
			if (nodePtr->myItem == it) {
				return i;
			}
		}
	}
	return -1;
}

/* remove() removes the Node at a given position
 * and returns the removed value
 *
 * @param: pos, an int
 *
 * @return: the value of the removed Node
 *
 * Postcondition: Node at pos is removed from list;
 * 				  mySize is updated
 *
 * METHOD WRITTEN BY COREY NOBLE
 */

template <class Item>
Item& List<Item>::remove(int pos) {
	Node * nodeRemove = myFirst;
	int intSize = mySize;
	if (pos <= 0) {
		pos = 0;
		mySize = mySize - 1;
		myFirst = nodeRemove->myNext;
		return nodeRemove->myItem;
		nodeRemove = NULL;
		delete nodeRemove;
	}
	else if (pos >= (intSize - 1)) {
		mySize = mySize - 1;
		pos = (mySize - 1);
		for (int i = 0; i < pos; i++) {
			nodeRemove = nodeRemove->myNext;
		}
		myLast = nodeRemove;
		Node * nodePtr = nodeRemove->myNext;
		return nodePtr->myItem;
		nodePtr = NULL;
		delete nodePtr;
	}
	else {
		mySize = mySize - 1;
		for (int i = 0; i < (pos - 1); i++) {
			nodeRemove = nodeRemove->myNext;
		}
		Node * nodePtr = nodeRemove->myNext;
		nodeRemove->myNext = nodePtr->myNext;
		return nodePtr->myItem;
		nodePtr = NULL;
		delete nodePtr;
	}
}

/* Inequality overload
 *
 * @param: list2, a const reference to a List
 *
 * @return: false if this and list2 are equal;
 * 			true if this and list are not equal
 *
 * METHOD WRITTEN BY COREY NOBLE
 */
template <class Item>
bool List<Item>::operator!=(const List<Item>& list2) {
	if (this->mySize == list2.mySize) {
		Node * lPtr1 = this->myFirst;
		Node * lPtr2 = list2.myFirst;
		for (unsigned i = 0; i < this->mySize; i++) {
			if (lPtr1->myItem == lPtr2->myItem) {
				lPtr1 = lPtr1->myNext;
				lPtr2 = lPtr2->myNext;
			}
			else {
				return true;
			}
		}
	}
	else {
		return true;
	}
	return false;
}

/* writeTo() writes a list to a stream
 *
 * @param: out, a reference to an ostream
 *
 * Postcondition: the list is written to out
 *
 * METHOD WRITTEN BY COREY NOBLE
 */
template <class Item>
void List<Item>::writeTo(ostream& out) {
	Node * lPtr = this->myFirst;
	for (unsigned i = 0; i < this->mySize; i++) {
		out << lPtr->myItem << '\t';
		lPtr = lPtr->myNext;
	}
}

#endif /* LIST_H_ */
