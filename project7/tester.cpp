/* tester.cpp is a "driver" to run the tests in the StackTester class.
 * Joel Adams, for CS 112 at Calvin College.
 */

#include "StackTester.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include "StackException.h"
using namespace std;

int main() {
	cout << "Press 0 to run tests or 1 to run program: " << flush;
	int choice;
	cin >> choice;
	if ( choice == 0 ) { // if wanting to run tests
		StackTester st;
		st.runTests();
	}

	else if ( choice == 1 ) { //if wanting to run program
		ifstream fin("text.txt"); // opening an input stream
		Stack<double> st(1); //making a stack with size 1
		char letter; //initialize character variable
		ofstream fout("newText.txt"); //opening an output stream to the new file

		while (fin) { //getting the elements from the file
			fin.get(letter); // putting them into the stack
			if ( isalnum(letter) ) { //if the element is digit or letter
				try {
					st.push(letter); // push into the stack
				}
				catch (StackException& se) { //catching the error
					st.setCapacity(st.getCapacity() * 2); //doubling the capacity
					st.push(letter);// push the letter to the stack
				}
			}

			else  { //if not alphanumeric
				if ( !( st.isEmpty() ) ) { // if stack is not full
					char top;  // create variable for the top element
					while ( !(st.isEmpty() ) ) { // while the stack is not full
						top = st.getTop(); // assign the top variable to the top element
						fout << top; // write out the stack's letter
						st.pop(); //pop the top element in the stack
					}
				}
				//so it doesn't double output the ending character
				if ( !(fin.eof() )) { //if end of file
					fout << letter; // write out the file
				}
			}
		}
		fin.close(); // close the streams
		fout.close(); // " " "
	}
}

