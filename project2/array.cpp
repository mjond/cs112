/* array.cpp defines "C style" array operation
 * Name:Mark Davis (mjd85)
 * Date:Feb 18/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */
 
#include "array.h"

void initialize(double *a, int size) {
	int val = 0;
	for (int i = 0; i < size; i++) {
		val = i+1;
		a[i] = val;
	}
}
 
void print(double *a, int size) {
	for (int i = 0; i < size; i++) {
		cout << *a << '\t';
		a++;
	}
}		

double average(double *a, int size) {
	double count = 0;
	for (int i = 0; i < size; i++){
		count += *a;
		a++;
	}
	return count/size;
}

double sum(double *a, int size){
	//This function should return the sum of the values in the array.
	double total = 0;
	for (int i = 0; i < size; i++){
		total += *a;
		a++;
	}
	return total;
}

void read(istream& in, double *a, int size){
	//This function should read size values from in and store them in a.
	for (int i = 0; i < size; i++){
		in >> *a;
		a++;
	}
}

void fill(const string& fileName, double *&a, int &numValues){
	//This function should (i) open an ifstream to the file named fileName, (ii) read an integer from the file into numValues,
	//(iii) dynamically allocate an array of numValues double values, storing its address in a, (iv) read numValues values from the file,
	//storing them in the dynamic array, and (v) close the ifstream.
	ifstream fin;
	fin.open( fileName.c_str() );
	cin >> numValues;

	a = double[numValues];
}

void resize(double *&a, int oldSize, int newSize){
	//This function should change the size of the array from oldSize to newSize.
	//If newSize > oldSize, all of the values in the old array must be copied into the new array.
	//If newSize < oldSize, the end-elements of the array should be truncated. Don't forget to properly "dispose of" the old array, or your function will leak memory!
}
