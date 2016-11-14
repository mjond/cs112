/* MovieTester.cpp
 * Student Name: Mark Davis
 * Date:Feb 10/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "MovieTester.h"
#include <fstream>
#include <istream>

void MovieTester::runTests() const {
   cout << "Testing Movie class..." << endl;
   testDefaultConstructor();
   testExplicitConstructor();
   testReadFrom();
   testWriteTo();
   testoperator();
   cout << "All tests passed!" << endl;

}

void MovieTester::testDefaultConstructor() const {
    cout << "- Default Constructor ... " << flush;
    Movie m;
    assert( m.getTitle() == "" );
    assert( m.getYear() == 0 );
    assert( m.getDirector() == "" );
    cout << " Passed!" << endl;
}

void MovieTester::testExplicitConstructor() const {
    cout << "- Explicit Constructor... " << flush;
    Movie m("Bambi", 1942, "David Hand");
    assert( m.getTitle() == "Bambi" );
    assert( m.getYear() == 1942 );
    assert( m.getDirector() == "David Hand" );
    cout << "Passed!" << endl;
}

void MovieTester::testReadFrom() const {
	cout << "- readFrom()... " << flush;
	ifstream fin("movieTest.txt");
	assert( fin.is_open() );
	Movie m;
	m.readFrom(fin);
	assert( m.getTitle() == "Gone with the Wind" );
	assert( m.getYear() == 1939 );
	assert( m.getDirector() == "Victor Fleming" );
	string blankLine;
	getline(fin, blankLine);
	m.readFrom(fin);
	assert( m.getTitle() == "Star Wars" );
	assert( m.getYear() == 1977 );
	assert( m.getDirector() == "George Lucas" );
	cout << "Passed!" << endl;
}

void MovieTester::testWriteTo() const {
   cout << "- writeTo()... " << flush;
   // declare a Movie with known values
   Movie m1("Raiders of the Lost Ark", 1981, "Steven Spielberg");
   // write it to a file
   ofstream fout("writeTo.txt");
   m1.writeTo(fout);
   fout.close();
   // now open the same file for reading
   ifstream fin("writeTo.txt");
   assert( fin.is_open() );
   // now read the Movie back from the file
   Movie m2;
   m2.readFrom(fin);
   // and check that we got the same values we wrote
   assert( m2.getTitle() == "Raiders of the Lost Ark" );
   assert( m2.getYear() == 1981 );
   assert( m2.getDirector() == "Steven Spielberg" );
   fin.close();
   cout << " 1 " << flush;
   // two movies
   Movie m3("Blade Runner", 1982, "Ridley Scott");
   fout.open("writeTo.txt");
   m1.writeTo(fout);                          // write 1st movie
   fout << "\n";                              // write a blank line
   m3.writeTo(fout);                          // write 2nd movie
   fout.close();
   fin.open("writeTo.txt");
   Movie m4, m5;
   m4.readFrom(fin);                          // read 1st movie
   string blankline; getline(fin, blankline); // eat the blank line
   m5.readFrom(fin);                          // read 2nd movie
   fin.close();
   assert( m4.getTitle() == "Raiders of the Lost Ark" );
   assert( m4.getYear() == 1981 );
   assert( m4.getDirector() == "Steven Spielberg" );
   assert( m5.getTitle() == "Blade Runner" );
   assert( m5.getYear() == 1982 );
   assert( m5.getDirector() == "Ridley Scott" );
   cout << " 2 " << flush;
   cout << "Passed!" << endl;
}

void MovieTester::testoperator() const{
	/* testoperator() tests the operator() method
	    *
	    * @param: no parameter
	    * Precondition: operator() must have proper syntax and logic
	    *
	    * Postcondition: outputs if the movies are the same and the test
	    * passed to the console
	    */
	cout << "testing operator..." << flush;
	//creating two movies to be compared
	Movie m1("Star Wars", 1985, "Steven");
	Movie m2("Star Wars", 1985, "Steven");
	//asserting they are equal
	assert(m1 == m2);
	cout << " 1 " << flush;

	//making a different movie
	Movie m3("Indiana Jones", 2020, "Chuck");
	//asserting they are different
	assert( !(m1==m3) );
	cout << " 2 \n" << flush;
}

