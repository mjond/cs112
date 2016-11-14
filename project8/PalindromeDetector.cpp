/*
 * PalindromeDetector.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: Mark Davis
 */

#include "PalindromeDetector.h"

using namespace std;

PalindromeDetector::PalindromeDetector(const string& file1, const string& file2) {
	string input_file = file1;
	string output_file = file2;
}

PalindromeDetector::~PalindromeDetector() {
	// TODO Auto-generated destructor stub
}

void PalindromeDetector::detectPalindrome() {
	ifstream fin(input_file.c_str()); // opening an input stream
	ofstream fout(output_file.c_str()); //opening an output stream to the new file
	while (fin) { //while there is content in the input file
		string word; // create a variable to hold the line
		getline(fin, word); // get the line
		fout << word; // write it to the output file
		isPalindrome(word); // process the line

		if ( isPalindrome(word) == true) {// if it is a palindrome
			fout << " *** " << endl; //print out ***
		}
		else {
			fout << endl;// else make a new line
		}
	}
	fin.close(); // close the streams
	fout.close();
}

bool PalindromeDetector::isPalindrome(string word) {
	char each; //char variable for each character
	Stack<char> st(1); // initialize stack with size of 1
	ArrayQueue<char> qu(1); // initialize queue with size of 1
	for ( unsigned i = 0; i < word.size(); i++ ) { // looping through the string
		each = i; //assign to char variable
		if ( isalpha(each) ) { // if it's a letter
			tolower(each); //make it lowercase
			try {
				st.push(each); // push into the stack
			}
			catch (QueueException& se) { //catching the error
				st.setCapacity(st.getCapacity() * 2); //doubling stack capacity
				st.push(each);// push the letter into the stack
				qu.setCapacity(qu.getCapacity() * 2);//doubling queue capacity
				qu.append(each); //append to queue
			}
		}
		else { // if it's not a letter
			i++; // increment the the loop's variable
			each = i; //set char variable to i
		}
	}
	while ( !( st.isEmpty() ) || !( qu.isEmpty() ) ) { //while containers are not empty
		char ch1;
		char ch2;
		//pop the first elements from queue and stack
		ch1 = st.pop();
		ch2 = qu.remove();
		if ( !( ch1 == ch2 ) ) { // if they are not the same
			return false; //return false
		}
	}
	return true; // else return true
}

