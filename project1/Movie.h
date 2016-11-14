
/* Movie.h
 * Student Name: Mark Davis mjd85
 * Date: Feb 10, 2015
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
#include <cassert>
#include <istream>
using namespace std;

class Movie {
public:
   Movie();
   string getTitle() const;
   int getYear() const;
   string getDirector() const;
   Movie(const string& title, int year, const string& director);
   void readFrom(istream& in);
   void writeTo(ostream& out) const;
   bool operator==(const Movie& movie2) const;
private:
   string myTitle;
   int    myYear;
   string myDirector;
};

#endif /*MOVIE_H_*/
