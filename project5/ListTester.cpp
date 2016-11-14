/* ListTester.cpp defines the test methods for class List.
 * Joel Adams, for CS 112 at Calvin College.
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List
#include <iostream>     // cin, cout
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
using namespace std;

void ListTester::runTests() {
	cout << "Running List tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testAppend();
	testDestructor();
	testCopyConstructor();
	testAssignment();
	testEquality();
    testInsert();
	testPrepend();
	testReadFromStream();
	testWriteToFile();


	testReadFromFile();
	testWriteToStream();
	testInequality();
	testSearch();
	testRemove();
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List default constructor... " << flush;
	List<double> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == 0 );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
	cout << "Testing Node explicit constructor... " << flush;
	List<double>::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List<double>::Node *n3 = new List<double>::Node(33, NULL);
	List<double>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<double> list1;
	List<double> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<double> list1;
	List<double> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<double> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<double> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
	cout << " 5 " << flush;

	// assignment chaining
	List<double> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<double> list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<double> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testEquality() {
	cout << "Testing equality... " << flush;
	// two empty lists
	List<double> list1;
	List<double> list2;
	assert( list1 == list1 );
	cout << " 1 " << flush;

	// a non-empty list
	List<double> list3;
	list3.append(33);		// [33]
	assert( !(list3 == list1) );
	cout << " 2 " << flush;

	// equal, non-empty lists of the same size
	List<double> list4;
	list4.append(33);		// [33]
	assert( list4 == list3 );
	assert( list3 == list4 );
	cout << " 3 " << flush;

	// unequal, non-empty lists of the same size
	list3.append(55);		// [33,55]
	List<double> list5;
	list5.append(44);		// [44]
	list5.append(55);		// [44,55]
	assert( !(list5 == list3) );
	assert( !(list3 == list5) );
	cout << " 4 " << flush;

	// unequal non-empty lists of different sizes
	list4.append(44);		// [33,44]
	list4.append(55);		// [33,44,55]
	assert( !(list4 == list5) );
	assert( !(list5 == list4) );
	assert( !(list5 == list3) );
	cout << " 5 " << flush;

	cout << "Passed!" << endl;
}

//TEST WRITTEN BY MARK DAVIS
void ListTester::testInsert() {
	cout << "Testing insert()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}

	//add values to list
	aList.append(22);
	aList.prepend(11);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext->myItem == 22 );

	//test insert
	aList.insert(33, 1);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst->myNext->myItem == 33);
	cout << " 1 " << flush;

	aList.insert(44, 1);
	assert( aList.getSize() == 4 );
	assert( aList.myFirst->myNext->myItem == 44);
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;

	aList.insert(55, -34);
	assert( aList.getSize() == 5 );
	assert( aList.getFirst() == 55 );
	assert( aList.getLast() == 22 );
	cout << " 3 " << flush;

	aList.insert(66, 73);
	assert( aList.getSize() == 6 );
	assert( aList.getFirst() == 55 );
	assert( aList.getLast() == 66 );
	cout << " 4 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testPrepend() {
	cout << "Testing prepend... " << flush;
	//prepend to empty list
	List<double> list1;
	list1.prepend(1);
	assert( list1.myFirst->myItem == 1);
	cout << " 1 " << flush;

	//prepend to non-empty list
	list1.prepend(2);
	assert( list1.myFirst->myItem == 2);
	cout << " 2 " << flush;

	cout << " Passed! " << endl;
}

void ListTester::testWriteToFile() {
	cout << "Testing writeTo(string)... " << flush;
	// make a list whose values we know
	List<double> list;
	list.prepend(1);
	list.append(2);
	list.append(3);
	// write it to a file
	list.writeTo("writeTo(string).txt");
	cout << " 1 ";
	// now, read what we just wrote into a different Matrix
	List<double> list2;
	list2.readFrom("writeTo(string).txt");
	// test it
	assert( list2.myFirst->myItem == 1 );
	assert( list2.myLast->myItem == 3 );
	assert( list2.myFirst->myNext->myItem == 2);

	cout << "Passed!" << endl;

}

void ListTester::testReadFromStream() {
	cout << "Testing read from stream... " << flush;
	//create stream
	ifstream fin("readFrom(stream).txt");
	assert( fin.is_open() );

	List<double> list;
	list.readFrom(fin);

	assert( list.myFirst->myItem == 1);
	assert( list.myLast->myItem == 5);
	assert( list.getSize() == 5);
	assert( list.myFirst->myNext->myItem == 2);
	assert( list.myFirst->myNext->myNext->myItem == 3);
	cout << " 1 " << flush;

	cout << "Passed!" << endl;
}

//TEST WRITTEN BY COREY NOBLE
void ListTester::testRemove() {
	cout << "Testing remove()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.append(44);
	aList.append(55);
	assert(aList.getSize() == 5);
	assert(aList.getFirst() == 11);
	assert(aList.getLast() == 55);
	cout << " 1 " << flush;

	//test remove
	double test1;
	test1 = aList.remove(0);
	assert(test1 == 11);
	assert(aList.getSize() == 4);
	assert(aList.getFirst() == 22);
	assert(aList.getLast() == 55);
	cout << " 2 " << flush;

	double test2;
	test2 = aList.remove(1);
	assert(test2 == 33);
	assert(aList.getSize() == 3);
	assert(aList.getFirst() == 22);
	assert(aList.myFirst->myNext->myItem == 44);
	assert(aList.getLast() == 55);
	cout << " 3 " << flush;

	double test3;
	test3 = aList.remove(2);
	assert(test3 == 55);
	assert(aList.getSize() == 2);
	assert(aList.getFirst() == 22);
	assert(aList.getLast() == 44);
	cout << " 4 " << flush;

	//test with negative and large indices
	List<double> bList;
	bList.append(11);
	bList.append(22);
	bList.append(33);
	bList.append(44);
	assert(bList.getSize() == 4);
	cout << " 5 " << flush;

	double test4;
	test4 = bList.remove(-5);
	assert(test4 == 11);
	assert(bList.getSize() == 3);
	assert(bList.getFirst() == 22);
	assert(bList.getLast() == 44);
	cout << " 6 " << flush;

	double test5;
	test5 = bList.remove(725);
	assert(test5 == 44);
	assert(bList.getSize() == 2);
	assert(bList.getFirst() == 22);
	assert(bList.getLast() == 33);
	cout << " 7 " << flush;
	cout << "Passed!" << endl;
}

//TEST WRITTEN BY COREY NOBLE
void ListTester::testSearch() {
	cout << "Testing getIndexOf()... " << flush;
	//append values to empty list
	List<double> aList;
	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.append(44);
	aList.append(55);

	//test search with all values in list
	assert(aList.getSize() == 5);
	cout << " 0 " << flush;
	int test1 = aList.getIndexOf(11);
	assert(test1 == 0);
	cout << " 1 " << flush;
	int test2 = aList.getIndexOf(22);
	assert(test2 == 1);
	cout << " 2 " << flush;
	int test3 = aList.getIndexOf(33);
	assert(test3 == 2);
	cout << " 3 " << flush;
	int test4 = aList.getIndexOf(44);
	assert(test4 == 3);
	cout << " 4 " << flush;
	int test5 = aList.getIndexOf(55);
	assert(test5 == 4);
	cout << " 5 " << flush;
	cout << "Passed!" << endl;
}

//TEST WRITTEN BY COREY NOBLE
void ListTester::testInequality() {
	cout << "Testing inequality... " << flush;
	// two empty lists
	List<double> list1;
	List<double> list2;
	assert( !(list1 != list1) );
	cout << " 1 " << flush;

	// a non-empty list
	List<double> list3;
	list3.append(33);		// [33]
	assert( (list3 != list1) );
	cout << " 2 " << flush;

	// equal, non-empty lists of the same size
	List<double> list4;
	list4.append(33);		// [33]
	assert( !(list4 != list3) );
	assert( !(list3 != list4) );
	cout << " 3 " << flush;

	// unequal, non-empty lists of the same size
	list3.append(55);		// [33,55]
	List<double> list5;
	list5.append(44);		// [44]
	list5.append(55);		// [44,55]
	assert( (list5 != list3) );
	assert( (list3 != list5) );
	cout << " 4 " << flush;

	// unequal non-empty lists of different sizes
	list4.append(44);		// [33,44]
	list4.append(55);		// [33,44,55]
	assert( (list4 != list5) );
	assert( (list5 != list4) );
	assert( (list5 != list3) );
	cout << " 5 " << flush;
	cout << "Passed!" << endl;
}

//TEST WRITTEN BY COREY NOBLE
void ListTester::testWriteToStream() {
	cout << "Testing writeTo(ostream)... " << flush;
	//fill list with values
	List<double> l1;
	for (unsigned i = 0; i < 5; i++) {
		l1.append(i+10);
	}
	//use file for automation
	ofstream fout("listStreamOut.txt");
	assert( fout.is_open() );
	//write values to file
	l1.writeTo(fout);
	fout.close();
	//read in values
	ifstream fin("listStreamOut.txt");
	assert( fin.is_open() );
	//check to see if values were written and read correctly
	double value;
	for (unsigned i = 0; i < 5; i++) {
		fin >> value;
		assert( value == i+10 );
	}
	cout << "Passed! See 'listStreamOut.txt' for values..." <<
			endl;
}

//TEST WRITTEN BY COREY NOBLE
void ListTester::testReadFromFile() {
	cout << "Testing readFrom(fileName)... ";
	//read files into empty list
	List<double> testList;
	testList.readFrom("listFileTest.txt");
	//check to see if values were read correctly
	assert(testList.getFirst() == 10);
	assert(testList.getLast() == 60);
	assert(testList.getSize() == 6);
	cout << "Passed!" << endl;
}
