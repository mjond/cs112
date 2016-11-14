/* MovieCollection.h ...
 * ...Student Name: MArk Davis
 * Date: Feb 10, 2015
 */


#include "MovieCollection.h"
#include <fstream>
using namespace std;

MovieCollection::MovieCollection(const string& fileName) {
	/* MovieCollection() constructs our collection using the data
	    *   in a given source file.
	    *
	    * @param: fileName, a string.
	    * Precondition: fileName contains the name of an input file
	    *                containing the data of N Movies (N >= 1),
	    *                separated by blank lines, ending with a newline.
	    * Postcondition: myMovies.size() == N &&
	    *                myMovies contains the Movies in fileName.
	    */
	ifstream fin( fileName.c_str() );
	assert( fin.is_open() );

	Movie aMovie;
	while (true) {
		aMovie.readFrom(fin);
		if ( !fin ) break;
		string blankLine;
		getline(fin, blankLine);
		myMovies.push_back(aMovie);
	}
	fin.close();
}

vector<Movie> MovieCollection::searchByDirector(const string& directorName) const {
   vector<Movie> v;
   for (unsigned i = 0; i < myMovies.size(); i++) {
      if ( myMovies[i].getDirector().find(directorName) != string::npos ) {
         v.push_back( myMovies[i] );
      }
   }
   return v;
}

vector<Movie> MovieCollection::searchByYear(int year) const{
	/* searchByYear() searches the collection for movies by a given year.
	    *
	    * @param: year, a integer containing the year
	    * @return: a vector containing all movies in the collection
	    * 			for whom year is a integer
	    */
	vector<Movie> h;
	for (unsigned i = 0; i < myMovies.size(); i++) {
		if ( myMovies[i].getYear() == year ) {
			h.push_back( myMovies[i] );
		}
	}
	return h;
}

vector<Movie> MovieCollection::searchByPhrase(const string& phrase) const {
	/* searchByPhrase() searches the collection for movies by a given phrase.
	    *
	    * @param: const string phrase, a string containing the phrase
	    * @return: a vector containing all movies in the collection
	    *          that have the phrase in the title.
	    */
   vector<Movie> c;
   for (unsigned i = 0; i < myMovies.size(); i++) {
      if ( myMovies[i].getTitle().find(phrase) != string::npos ) {
         c.push_back( myMovies[i] );
      }
   }
   return c;
}

void MovieCollection::addMovie(const Movie& newMovie) {
	/* addMovie() adds a movie to the vector
	    *
	    * @param: newMovie, a string.
	    * Precondition: myMovies vector must exist
	    * 				the user must input a movie with correct input formatting
	    * Postcondition: myMovies.size() == N &&
	    *                myMovies vector now contains a new movie.
	    */
	myMovies.insert(myMovies.begin(), newMovie);
}

void MovieCollection::removeMovie(const Movie& aMovie) {
	/* removeMovie() removes a movie from vector myMovies
	    *
	    * @param: aMovie, a string.
	    * Precondition: myMovie must be accessible
	    * 				the movie must exist in myMovie
	    * Postcondition: myMovies.size() == N &&
	    *                myMovies no longer contains aMovie
	    */
	for (unsigned i = 0; i < myMovies.size(); i++) {
		if (myMovies[i].getTitle() == aMovie.getTitle() ) {
			if (myMovies[i].getYear() == aMovie.getYear() ){
				if (myMovies[i].getDirector() == aMovie.getDirector() ) {
					myMovies.erase(myMovies.begin()+i);
				}
			}
		}
	}
}

void MovieCollection::save() const{
	/* save() outputs the vector myMovie to a text file and saves it
	    * @param: no parameters
	    * Precondition: must have movies in the vector
	    * 				text file must exist before saving it
	    * Postcondition: a text file is now saved with the movies in the vector
	    * 				the vector myMovie still has the movies in it
	    */
	ofstream write("saveTester.txt");
	for (unsigned i = 0; i < myMovies.size(); i++) {
		myMovies[i].writeTo(write);
		write << '\n';
	}
	write.close();
}
