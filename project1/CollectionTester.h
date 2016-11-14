/* CollectionTester.h tests the MovieCollection class.
 * Student Name: Mark Davis
 * Date:mjd85
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef COLLECTIONTESTER_
#define COLLECTIONTESTER_

#include <iostream>
#include <fstream>
#include <istream>
#include "MovieCollection.h"

using namespace std;

class CollectionTester {
public:
	void testConstructor() const;
    void runTests() const;
    void testsearchByYear() const;
    void testsearchByPhrase() const;
    void testaddMovieandRemove() const;
    void saveTester() const;
};

#endif /*COLLECTIONTESTER_*/
