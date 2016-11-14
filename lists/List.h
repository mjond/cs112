/* List class
 * Corey Noble (cjn8)
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

template <class Item>

class List {
public:
	List();
	Item getSize() const;
	Item getFirst() const;
	Item getLast() const;
	void append(const Item& it);
	List(const List& original);
	List<Item>& operator=(const List<Item>& original);
	bool operator==(const List<Item>& list2);
	bool operator!=(const List<Item>& list2);
	void readFrom(istream& in);
	void writeTo(ostream& out);
	void readFrom(const string& fileName);
	void writeTo(const string& fileName);
	void prepend(const Item& it);
	int getIndexOf(const Item& it);
	void insert(const Item& it, int pos);
	Item& remove(int pos);
	void sort();
	List mergeSort(const List<Item>& list1, const List<Item>& list2 );
	virtual ~List();

private:
	struct Node {
		Node();
		Node(Item it, Node * next);
		virtual ~Node();
		Item myItem;
		Node * myNext;
	};
	unsigned mySize;
	Node * myFirst;
	Node * myLast;

	friend class ListTester;
};

/* List Default Constructor
 *
 * Precondition:  mySize, myFirst, and myLast exist
 *
 * Postcondition: mySize is set to 0; myFirst and myLast are set to NULL
 */
template <class Item>
List<Item>::List() {
	mySize = 0;
	myFirst = NULL;
	myLast = NULL;
}

/* Node Default Constructor
 *
 * Precondition:  Node struct exists; myItem and myNext exist
 *
 * Postcondition: myItem is set to 0; myNext is set to NULL
 */
template <class Item>
List<Item>::Node::Node() {
	myItem = 0;
	myNext = NULL;
}

/* Node explicit constructor
 *
 * @param: it, an Item; next, a Node pointer
 *
 * Precondition:  Node struct exists; myItem and myNext exist
 *
 * Postcondition: myItem is set to it; myNext is set to next
 */
template <class Item>
List<Item>::Node::Node(Item it, Node * next) {
	myItem = it;
	myNext = next;
}

/* mySize accessor
 *
 * @return: mySize
 */
template <class Item>
Item List<Item>::getSize() const {
	return mySize;
}

/* myFirst accessor
 *
 * @return: myFirst, if not negative or NULL
 */
template <class Item>
Item List<Item>::getFirst() const {
	if ((mySize < 0) or (myFirst == NULL)) {
		throw underflow_error("Either mySize is negative or myFirst is NULL.");
	}
	else {
		return myFirst->myItem;
	}
}

/* myLast accessor
 *
 * @return: myLast, if not negative or NULL
 */
template <class Item>
Item List<Item>::getLast() const {
	if ((mySize < 0) || (myLast == NULL)) {
		throw underflow_error("Either mySize is negative or myLast is NULL.");
	}
	else {
		return myLast->myItem;
	}
}

/* append() adds a node to the end of the list
 *
 * @param: it, a const reference to an Item
 *
 * Postcondition:  it is added (in form of a Node) to the list
 */
template <class Item>
void List<Item>::append(const Item& it) {
	Node * nodePtr = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = nodePtr;
	}
	else {
		myLast->myNext = nodePtr;
	}
	myLast = nodePtr;
	mySize++;
}

/* List Copy Constructor
 *
 * @param: original, a const reference to a List
 *
 * Postcondition: this is set to values of original
 */
template <class Item>
List<Item>::List(const List& original) {
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

/* Assignment operator
 *
 * @param: original, a const reference to a list
 *
 * Postcondition: operator is able to assign List to this
 */
template <class Item>
List<Item>& List<Item>::operator=(const List& original) {
	if (this != &original) {
		delete this->myFirst;
		myFirst = myLast = NULL;
		mySize = 0;
		if (original.getSize() != 0) {
			Node * nPtr = original.myFirst;
			while (nPtr != NULL) {
				this->append(nPtr->myItem);
				nPtr = nPtr->myNext;
			}
		}
	}
	return *this;
}

/* Equality overload
 *
 * @param: list2, a const reference to a List
 *
 * @return: true if this and list2 are equal;
 * 			false if this and list are not equal
 *
 * METHOD WRITTEN BY MARK DAVIS
 */
template <class Item>
bool List<Item>::operator==(const List& list2) {
	if (this->mySize == list2.mySize) {
		Node * lPtr1 = this->myFirst;
		Node * lPtr2 = list2.myFirst;
		for (unsigned i = 0; i < this->mySize; i++) {
			if (lPtr1->myItem == lPtr2->myItem) {
				lPtr1 = lPtr1->myNext;
				lPtr2 = lPtr2->myNext;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
	return true;
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
bool List<Item>::operator!=(const List& list2) {
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

/* readFrom() reads a list from a stream
 *
 * @param: in, a reference to an istream
 *
 * Postcondition: the list is read from in
 *
 * METHOD WRITTEN BY MARK DAVIS
 */
template <class Item>
void List<Item>::readFrom(istream& in) {
	List tempList;
	while (in) {
		int it;
		in >> it;
		this->append(it);
	}
	mySize = (mySize - 1);
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
	List tempList;
	while (fin) {
		int it;
		fin >> it;
		this->append(it);
	}
	fin.close();
	mySize = (mySize - 1);
}

/* writeTo() writes a list to a file
 *
 * @param: fileName, a const reference to a string
 *
 * Postcondition: the list is written to fileName
 *
 * METHOD WRITTEN BY MARK DAVIS
 */
template <class Item>
void List<Item>::writeTo(const string& fileName)  {
	ofstream fout(fileName.c_str());
	Node * lPtr = this->myFirst;
	for (unsigned i = 0; i < this->mySize; i++) {
		fout << lPtr->myItem << '\t';
		lPtr = lPtr->myNext;
	}
	fout.close();
}

/* prepend() adds an Item to the front of the list
 *
 * @param: it, a const reference to an Item
 *
 * Postcondition: a Node with the value it is prepended
 * 				  to the list
 *
 * METHOD WRITTEN BY MARK DAVIS
 */
template <class Item>
void List<Item>::prepend(const Item& it) {
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

/* List destructor
 *
 * Postcondition: dynamic memory from pointers is reclaimed
 */
template <class Item>
List<Item>::~List() {
	delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
	myFirst = myLast = NULL; // clear myFirst and myLast (optional)
	mySize = 0;              // clear mySize (optional)
}

/* List destructor
 *
 * Postcondition: dynamic memory from pointers is reclaimed
 */
template <class Item>
List<Item>::Node::~Node() {
	//	cout << "~Node() is deallocating the node containing item "
	//			<< myItem << endl;
	delete myNext;  // delete the next node, invoking ~Node() in it
	// (does nothing if myNext == NULL)
	myNext = NULL;  // clear myNext (optional)
	myItem = 0;     // clear myItem (optional)
}

template <class Item>
void List<Item>::sort() {
	if ( mySize > 1) {  //as long as the size is bigger than one
		int size = mySize/2; //cutting the original size in half
		List<double> listL;
		List<double> listR;
		Node * ptr = this->myFirst;

		if ( mySize % 2 != 0 ){ //checking if list is odd
			for ( int i = 0; i < size; i++) { // allocating the left list
				listL.append(ptr->myItem);
				ptr = ptr->myNext;
			}
			for ( unsigned i = size; i < mySize; i++){ // allocating the RIGHT list
				listR.append(ptr->myItem);						// RIGHT list will be smaller for the odd
				ptr = ptr->myNext;
			}
		}

		else { //for the even numbers
			for ( int i = 0; i < size; i++) { // allocating the LEFT VEC
				listL.append(ptr->myItem);
				ptr = ptr->myNext;
			}
			for ( unsigned i = size; i < mySize; i++){ // allocating the RIGHT list
				listR.append(ptr->myItem);
				ptr = ptr->myNext;
			}
		}
		listL.sort(); // call the function
		listR.sort(); //recursive

		List<double> newList;
		newList = mergeSort(listL, listR); //call the function that merges and sorts them back into one LIST
		*this = newList;
	}
}

template <class Item>
List<Item> List<Item>::mergeSort(const List<Item>& listL, const List<Item>& listR ) {
	Node * lptr = listL.myFirst; // pointer to iterate the left list
	Node * rptr = listR.myFirst; // pointer to iterate the right list
	List<double> newList; // new list to store the sorted elements

	while ( lptr != NULL && rptr != NULL ){ // make sure the lists are NOT NULL
		if ( lptr->myItem < rptr->myItem){ //if the left item is smaller than the right item
			newList.append(lptr->myItem); // append it to the new list
			lptr = lptr->myNext; //point to the next node in the left list
		}
		else if ( lptr->myItem == rptr->myItem ) { // if the items are equal
			newList.append(lptr->myItem); // append both of them to the list
			newList.append(rptr->myItem);
			lptr =lptr->myNext;// point to the next node
			rptr = rptr->myNext;
		}
		else { //else the right item is bigger than the left
			newList.append(rptr->myItem);// so add it to the new list
			rptr = rptr->myNext; //point to the next node in the right list
		}
	}
	if( lptr == NULL && rptr != NULL) {// if the LEFT list is done
		while (rptr != NULL) {
			newList.append(rptr->myItem);// append the RIGHT list items
			rptr = rptr->myNext; // point to the next node
		}
	}

	else if ( rptr == NULL && lptr != NULL) {// if the RIGHT list is done
		while ( lptr != NULL) {
			newList.append(lptr->myItem);//append the LEFT list items
			lptr = lptr->myNext; // point to the next node
		}
	}
	return newList;
}

#endif /* LIST_H_ */
