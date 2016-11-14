/* Vec.cpp defines the methods for Vec, a simple vector clas
 * Student Name:Mark Davis (mjd85)
 * Date:Feb 26/ 2015
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#include "Vec.h"

Vec::Vec() {
	//default constructor
	myArray = NULL;
	mySize = 0;
}

Vec::~Vec() {
	//deconstructor
	delete [] myArray;
	myArray = NULL;
	mySize = 0;
}

Vec::Vec(unsigned size){
	//explicit constructor
	mySize = size;
	myArray = new Item[size]();

}

Vec::Vec(const Vec& original) {
	//copy constructor
	mySize = original.mySize;
	if (original.mySize > 0){
		myArray = new Item[mySize];
		for ( unsigned i = 0; i < mySize; i++){
			myArray[i] = original.myArray[i];
		}
	}
	else{
		myArray = NULL;
	}
}

Vec& Vec::operator=(const Vec& original) {
	//equals operator: returns the pointer of
	// the method (*this)
	if (&original != this){
		if (mySize != original.mySize){
			delete [] myArray;
			mySize = original.mySize;
			if (mySize > 0){
				myArray = new Item[mySize];
			}
			else{
				myArray = NULL;
			}
		}
		for(unsigned i = 0; i<mySize;i++){
			myArray[i]=original.myArray[i];
		}
	}
	return *this;
}

unsigned Vec::getSize() const {
	//returns the size of the vector
	return mySize;
}

void Vec::setItem(unsigned index, const Item& it) {
	//sets a new value at position i
	// in the vector
	if ( index < 0 || index >= mySize){
		throw range_error("error");
	}
	else{
		myArray[index] = it;
	}
}

Item Vec::getItem(unsigned index) const {
	//retrieves the value at the index
	if ( index < 0 || index >= mySize){
		throw range_error("error");
	}
	else{
		return myArray[index];
	}
}

void Vec::setSize(unsigned newSize) {
	/* setSize() set's the vectors index
	 *written by: Mark Davis (mjd85)
	 * @param: unsigned number of Vec size
	 * Precondition: vector exists
	 * Postcondition: vector at position 'i' has
	 * 				a new value at that position
	 */
	if (mySize != newSize){
		if (newSize == 0){
			delete [] myArray;
			myArray = NULL;
			mySize = 0;
		}

		else{
			Item* newArray = new Item[newSize];
			if (mySize < newSize){
				for ( unsigned i = 0; i < mySize; i++){
					newArray[i] = myArray[i];
				}

				for ( unsigned i = mySize; i < newSize; i++ ){
					newArray[i] = 0;
				}
			}
			if (newSize < mySize) {
				for ( unsigned i = 0; i < newSize; i++){


					myArray[i] = myArray[i];
				}
			}
			mySize = newSize;
			delete [] myArray;
			myArray = newArray;
		}
	}
}

bool Vec::operator==(const Vec& v2) {
	/* operator==() equality operater
	*written by: Mark Davis (mjd85)
	* @param: vector of Vec
    * Precondition: vector must exist
 * Postcondition: return true if vectors are equal and
 * false if they are not equal
						    */
	if( mySize != v2.mySize){
		return false;
	}
	for (unsigned i = 0; i < mySize; i++){
		if (myArray[i] != v2.myArray[i]){
			return false;
		}
	}
	return true;
}

void Vec::writeTo(ostream& out) const {
	/* writeTo() writes to a stream
		    *
		    * @param: name of the stream
		    * Precondition: stream is open
		    * Postcondition: stream contains values in the vector
		    */
	for (unsigned i = 0; i < mySize; i++){
		out << myArray[i] << "\t";
	}
	out << endl;
}

void Vec::readFrom(istream& in) {
	/* readFrom() reads in values from a istream
	    *
	    * @param: name of the stream
	    * Precondition: stream is open
	    * Postcondition: vector contains the values of the stream
	    */
	for (unsigned i = 0; i < mySize; i++){
		in >> myArray[i];
	}
}

Item& Vec::operator[](unsigned nIndex) const {
	/* operator[]() subscript operater
					    *written by: Mark Davis (mjd85)
					    * @param: unsigned index number
					    * Precondition: vector must exist
					    * Postcondition: value of that index in the vector is returned
					    */
	return myArray[nIndex];
}

Item& Vec::operator[](unsigned nIndex){
	/* operator[]() subscript operater
				    *written by: Mark Davis (mjd85)
				    * @param: unsigned index number
				    * Precondition: vector must exist
				    * Postcondition: value of that index in the vector is returned
				    */
	if ( nIndex >= mySize){
		throw out_of_range("out of range");
	}

	return myArray[nIndex];
}

bool Vec::operator!=(const Vec& v3){
	/* operator!=() inequality operater
	 *written by: Emily Jawkowski eaj3
	 * @param: a vector of Vec type
	 * Precondition: two vectors must exist to compare
	 * Postcondition: returns true if vectors are different and flase
	 * if they are the same
	 */
	if ( mySize != v3.mySize){
		return true;
	}
	for (unsigned i=0; i < mySize; i++){
		if (myArray[i] != v3.myArray[i]) {
			return true;
		}
	}
	return false;
}

Vec Vec::operator-(const Vec& v3){
	/* operator- (Vec& v2) overloads the - operator to subtract all the values
	 * 		of a vector
	 * written by: eaj3 (Emily Jakowski)
	 * @param: v2, a vector
	 * @return: the difference between v2 and original vector
	 */
	if ( mySize != v3.mySize){
		throw invalid_argument("vectors are not the same size!");
	}
	Vec result(mySize);
	for ( unsigned i = 0; i < mySize; i++){
		result.myArray[i] = myArray[i] - v3.myArray[i];
	}
	return result;
}

Vec Vec::operator+(const Vec& v3){
	/* operator+() adds two vectors
		    *written by: Mark Davis (mjd85)
		    * @param: a vector of Vec type
		    * Precondition: both vectors being added MUST be same size
		    * Postcondition: a new vector is created that stores the
		    * 				answer of the sum of the two vectors
		    */
	//make sure they are the same size
	if ( mySize != v3.mySize){
		throw invalid_argument("vectors are not the same size!");
	}
	//initialize the new vector
	Vec result(mySize);
	//adding each value in each index
	for (unsigned i = 0; i < mySize; i++){
		result.myArray[i] = myArray[i] + v3.myArray[i];
	}
	return result;
}

Item Vec::operator*(const Vec& v3){
	/* operator*() multiplies two vectors; the result is stored in a new vector
		    *written by: Mark Davis (mjd85)
		    * @param: a vector of Vec type
		    * Precondition: both vectors MUST be the same size
		    * Postcondition: a new vector is created that stores the
		    * 				answer of the product of the two vectors
		    */
	//make sure they are the same size
	if ( mySize != v3.mySize){
		throw invalid_argument("vectors are not the same size!");
	}
	//initialize the return variable
	Item result = 0;
	//multiply each value in each index and add it to the next one
	for (unsigned i = 0; i < mySize; i++){
		result += myArray[i] * v3.myArray[i];
	}
	return result;
}

void Vec::writeTo(const string& name){
	/* writeTo() writes a vector out to a file
	    *written by: Mark Davis (mjd85)
	    * @param: a string that is the file name
	    * Precondition: stream is open, vector exists
	    * Postcondition: a file is either opened or made to write
	    * 				that contains the values in the vector &&
	    * 				the file is closed
	    */
	//open the output stream
	ofstream fout(name.c_str());
	//make sure it's open
	assert( fout.is_open() );
	//output the size of the vec to the first line
	fout << getSize() << "\n";
	//write the rest of the values
	writeTo(fout);
	fout.close();
}

void Vec::readFrom(const string& name) {
	/* readFrom(const string& filename) reads integers from a file into a vector.
	 * written by: eaj3 (Emily Jakowski)
	 * @param: filename, a filestream to read in values
	 * @return: none
	 */

	if (myArray != NULL || mySize != 0){
		delete [] myArray;
		myArray = NULL;
		mySize = 0;
	}
	ifstream fin(name.c_str());
	unsigned size;
	fin >> size;
	mySize = size;
	myArray = new Item[mySize];
	Vec v(size);
	v.readFrom(fin);
	for (unsigned i = 0; i < size; i++){
		myArray[i] = v.myArray[i];
	}
	fin.close();
}

