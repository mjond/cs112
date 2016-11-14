/* MovieTester.h
 * Student Name: Mark Davis
 * Date:Feb 10/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MOVIETESTER_H_
#define MOVIETESTER_H_

#include "Movie.h"
#include <iostream>
using namespace std;

class MovieTester {
public:
   void runTests() const;
   void testDefaultConstructor() const;
   void testExplicitConstructor() const;
   void testReadFrom() const;
   void readFrom(istream& in) const;
   void testWriteTo() const;
   void testoperator() const;
};

#endif /*MOVIETESTER_H_*/
