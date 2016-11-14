/*
 * main.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: Mark Davis
 */


#include <iostream>
#include <string>
using namespace std;

int main() {
	int num = 5;
	int * iPtr = &num;
	cout << iPtr << endl;

	cout << *iPtr << endl;

}
