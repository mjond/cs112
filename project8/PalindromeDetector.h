/*
 * PalindromeDetector.h
 *
 *  Created on: Apr 19, 2015
 *      Author: Mark Davis
 */

#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#include "ArrayQueue.h"
using namespace std;

class PalindromeDetector {
public:
	PalindromeDetector(const string& file1, const string& file2);
	virtual ~PalindromeDetector();
	void detectPalindrome();
	bool isPalindrome(string word);
private:
	string input_file;
	string output_file;
};


#endif /* PALINDROMEDETECTOR_H_ */
