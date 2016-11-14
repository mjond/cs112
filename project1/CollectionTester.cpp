/* CollectionTester.cpp defines the MovieCollection test-methods.
 * Student Name: Mark Davis
 * Date:Feb 10/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "CollectionTester.h"
#include <iostream>


using namespace std;

void CollectionTester::runTests() const {
   cout << "Testing class MovieCollection..." << endl;
   testConstructor();
   testsearchByYear();
   testsearchByPhrase();
   testaddMovieandRemove();
   saveTester();
   cout << "All tests passed!" << endl;
}

void CollectionTester::testConstructor() const {
    cout << "- constructor..." << flush;
    MovieCollection mc("testCollection.txt");
    // case of 1 movie
    vector<Movie> v1 = mc.searchByDirector("Hand");
    assert( v1.size() == 1 );
   // cout << "nnn" <<  v1[0].getTitle().erase(v1[0].getTitle().size() -1, 1) << "nnn"<<flush;
    assert( v1[0].getTitle() == "Bambi" );
    cout << " 1 " << flush;
    // case of 2 movies
    vector<Movie> v2 = mc.searchByDirector("Spielberg");
    assert( v2.size() == 2 );
    assert( v2[0].getTitle() == "Jaws" );
    assert( v2[1].getTitle() == "Raiders of the Lost Ark" );
    cout << " 2 " << flush;
    // case of no movies
    vector<Movie> v3 = mc.searchByDirector("Hitchcock");
    assert( v3.size() == 0 );
    cout << " 3 " << flush;
    cout << " Passed! \n" << endl;
}

void CollectionTester::testsearchByYear() const{
	/* testsearchByYear() tests the searchByYear method
	    *
	    * @param: no parameter
	    * Precondition: proper syntax and logic in original method
	    *
	    * Postcondition: outputs to the console that the tests passed
	    */
	cout << "- search by year..." << flush;
	MovieCollection mc("testCollection.txt");
    //making vector to search for a year
    vector<Movie> v4 = mc.searchByYear(1981);
    //asserting that there is something in the vector
    assert( v4.size() == 1);
    assert( v4[0].getYear() == 1981);
    cout << " 1 " << flush;
    //search by a year that has 2 movies in that year
    vector<Movie> v5 = mc.searchByYear(1939);
    assert( v5.size() == 2 );
    assert( v5[0].getYear() == 1939);
    assert( v5[1].getYear() == 1939);
    cout << " 2 " << flush;
    //search by year that does not exist in txt file
    vector<Movie> v6 = mc.searchByYear(1919);
    assert( v6.size() == 0);
    cout << " Passed! \n" << flush;
}

void CollectionTester::testsearchByPhrase() const{
	/* testsearchByPhrase() tests searchByPhrase() method
	    *
	    * @param: no parameter
	    * Precondition: proper syntax and logic in original method
	    * Postcondition: outputs to the console if all tests passed or not
	    */
    //search by phrase
	cout << "- search by phrase..." << flush;
	MovieCollection mc("testCollection.txt");
	//create a vector that searches for word 'phrase'
    vector<Movie> v7 = mc.searchByPhrase("Wind");
    assert( v7.size() == 1 );
    assert( v7[0].getTitle() == "Gone with the Wind");
    cout << " 1 " << flush;
    //searching for word 'of'
    vector<Movie> v8 = mc.searchByPhrase("of");
    assert( v8.size() ==2 );
    assert( v8[0].getTitle() == "The Wizard of Oz");
    assert( v8[1].getTitle() == "Raiders of the Lost Ark");
    cout << " 2    Passed! \n" << flush;
}

void CollectionTester::testaddMovieandRemove() const {
	/* testaddMovieandRemove() tests the add and remove methods
	    * @param: no param
	    * Precondition: must have movies in the vector to add or remove
	    * 				movies must be properly inputed.
	    * Postcondition: outputs to console if tests failed or passed
	    * 				 adds movies or removes them to the vector
	    */
	cout << "- add and remove methods..."<< flush;
	// make a movie
	Movie m1("Batman", 2014, "Chuck");
	MovieCollection mc1("testCollection.txt");
	// add it to the vector
	mc1.addMovie(m1);
	//make sure it's there
	vector<Movie> v8 = mc1.searchByPhrase("Batman");
	assert( v8.size() == 1 );
	assert( v8[0].getTitle() == "Batman");
	assert( v8[0].getYear() == 2014);
	assert( v8[0].getDirector() == "Chuck");
	cout << " 1 " << flush;

	//now remove it from the vector
	mc1.removeMovie(m1);
	vector<Movie> v9 = mc1.searchByPhrase("Batman");
	assert( v9.size() == 0 );
	cout << "2   Passed! \n" << flush;
}


void CollectionTester::saveTester() const {
	/* saveTester() tests the save method
	    *
	    * @param: no param
	    * Precondition: movies must exist in the vector
	    * 				txt file must exist to be written out to
	    * Postcondition: outputs if tests failed or passed
	    * 			     writes out to the file
	    * 			     then removes it so multiple movies
	    * 			     aren't written each time test is ran
	    */
	//making a movie
	cout << "- save... " << flush;
	// declare a Movie with known value
	Movie m1("Iron Man", 2012, "Who knows");
	MovieCollection mc2("saveTester.txt");

	//making sure it's not in the vector yet
	vector<Movie> v10 = mc2.searchByPhrase("Iron");
	assert(v10.size() == 0);
	cout << " 1 " << flush;

	//add it to the vector and then save
	mc2.addMovie(m1);
	mc2.save();
	//make sure it's there
	vector<Movie> v11 = mc2.searchByPhrase("Iron");
	assert(v11.size() == 1);
	assert(v11[0].getTitle() == "Iron Man");
	assert(v11[0].getYear() == 2012);
	assert(v11[0].getDirector() == "Who knows");
	cout << " 2 " << flush;
	//remove it from the file so it's not added every time it's tested
	mc2.removeMovie(m1);
	mc2.save();
	vector<Movie> v12 = mc2.searchByPhrase("Iron");
	assert( v12.size() == 0);
	cout << "Passed! \n" << flush;

}



