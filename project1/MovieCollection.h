/* Student Name: Mark Davis (mjd85)
 * Date: Feb 10/2015
 */


#ifndef MOVIECOLLECTION_H_
#define MOVIECOLLECTION_H_

#include <string>
#include "Movie.h"
#include <vector>
#include <cassert>
using namespace std;


class MovieCollection {
public:
   MovieCollection(const string& fileName);
   vector<Movie> searchByDirector(const string& directorName) const;
   vector<Movie> searchByYear(int year) const;
   vector<Movie> searchByPhrase(const string& phrase) const;
   void addMovie(const Movie& newMovie);
   void removeMovie(const Movie& aMovie);
   void save() const;
private:
	vector<Movie> myMovies;
};

#endif /*MOVIECOLLECTION_H_*/
