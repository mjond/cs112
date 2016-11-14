/* Movie.cpp
 * Student Name: Mark Davis mjd85
 * Date:Feb 10/15
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

 #include "Movie.h"

string Movie::getTitle() const {
	return myTitle;
}

int Movie::getYear() const {
	return myYear;
}

string Movie::getDirector() const {
	return myDirector;
}

Movie::Movie() {
	myTitle = "";
	myYear = 0;
	myDirector = "";
}

Movie::Movie(const string& title, int year, const string& director) {
	myTitle = title;
	myYear = year;
	myDirector = director;
}

void Movie::readFrom(istream& in) {
	getline(in, myTitle);
	in >> myYear;
	string newLine; getline(in, newLine);
	getline(in, myDirector);
	//myTitle.erase(myTitle.size() - 1, 1);
}

void Movie::writeTo(ostream& out) const {
	out << myTitle << '\n'
	    << myYear  << '\n'
	    << myDirector << '\n';
}

bool Movie::operator==(const Movie& movie2) const{
	/* operator() compares a movie to another and checks if they are the same
	    *
	    * @param: const Movie movie2
	    * Precondition: a movie needs to exist in the vector in order to
	    * 				compare to another movie
	    * Postcondition: nothing is changed.
	    * @return: returns true if check is the same
	    * 		   returns false if check is not the same
	    */
	//checks if the first movie is the same as the second
	if (myTitle == movie2.getTitle() && myYear == movie2.getYear() && myDirector == movie2.getDirector()){
		return true;
	}
	else{
		return false;
	}
}
