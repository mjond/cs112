/* tester.cpp tests the classes in our project.
 *
 */

#include "MovieTester.h"
#include "CollectionTester.h"
#include <iostream>
#include <vector>
using namespace std;

MovieCollection mc1("optionMenu.txt");
void optionMenu() {
	/* optionMenu() provides an option menu for the user to manage
	 * 				the movie collection
	    *
	    * @param: no parameters
	    * Precondition: all methods should run properly and test correctly
	    * Postcondition: possible outcomes:
	    * 				 myMovies.size() == N &&
	    *                myMovies contains the Movies in fileName.
	    *                myMovies can save to a file
	    *                can search for movies by director, year or phrase
	    */
	string num;
	while (true) {
		//outputting the options
	    cout << "Welcome to Phil's Movie Collection Manager! \n "<< flush;
	    cout << "	a - to search the collection for movies by a given director" << endl;
	    cout << "	b - to search the collection for movies made in a given year" << endl;
	    cout << "	c - to search the collection for movies with a given phrase in their title" << endl;
	    cout << "	d - to add a new movie to the collection" << endl;
	    cout << "        e - to save" << endl;
	    cout << "	q - to quit" << endl;
	    cout << "Please Enter: " << flush;
	    //getting user's choice
	    getline(cin, num);
	    cout << num << flush;

	    if (num == "Q" || num == "q"){
	    	//quit the loop if 'q' is entered
	    	cout << "have a good day" << flush;
	    			break;
	    }

	    else if (num == "a" || num == "A"){
	    	//to search by director
	    	cout << "Enter director: ";
	    	string director;
	    	//getting rid of the space in the user's input
	  		cin.ignore(256, '\n');
	   		getline(cin, director);

	   		//searching for the director
	    	vector<Movie> vec = mc1.searchByDirector(director);

	    	//if vector size is 0, print NO MOVIES
	    	if(vec.size() == 0) {
	  			cout << "NO MOVIES!" << endl;
	    	}
	    	else {
	    		//else print the movie titles
	    		for(unsigned i = 0; i < vec.size(); i++) {
	    		cout << vec[i].getTitle();
	    		}
	  	   	}
	    }
	    else if (num == "b" || num == "B"){
	    	//to search by year
	    	cout << "Enter year: ";
	    	int year;
	    	cin >> year;

	    	//searching for movies with given year
	    	vector<Movie> vec2 = mc1.searchByYear(year);

	    	//if vector size is 0, print NO MOVIES
	    	if(vec2.size() == 0) {
	    	cout << "NO MOVIES!" << endl;
	 		}
	  		else {
	  			   //else print titles with given year
	    		   for(unsigned i = 0; i < vec2.size(); i++) {
	    		   cout << vec2[i].getTitle();
	    		}
	    	}
	    }

	    else if (num == "c" || num == "C"){
	    	//to search by phrase
	    	string mphrase;
	    	cout << "Enter the phrase: " << flush;
	    	//getting rid of whitespace in user's input
	    	cin.ignore(256, '\n' );
	    	getline(cin, mphrase);

	    	//searching for movie titles with given phrase
	    	vector<Movie> vec3 = mc1.searchByPhrase(mphrase);

	    	//if vector size is 0, print NO MOVIES
	    	if(vec3.size() == 0) {
	    		cout << "NO MOVIES!" << endl;
	    	}
	    	else {
	    		//else print out movie titles with given phrase
	    		for(unsigned i = 0; i < vec3.size(); i++) {
	    		cout << vec3[i].getTitle();
	    		}
	    	}
	    }

	    else if (num == "d" || num == "D"){
	    	//to add a movie
	    	string mtitle;
	    	int myear;
	    	string mdirector;

	   		cout << "Enter title: ";
	   		cin.ignore();
	   		getline(cin, mtitle);

    		cout << "Enter year";
	    	cin >> myear;

	   		cout << "Enter director: ";
	   		cin.ignore();
	   		getline(cin, mdirector);
	   		cout << '\n';

	    	Movie m1(mtitle, myear, mdirector);
	   		mc1.addMovie(m1);
	   		cout << "the movie was added!" << endl;

	    }

	    else if (num == "e" || num == "E"){
	    	//outputs the vector contents to a file and saves it
	    	mc1.save();
	    	cout << "Movie saved! \n" << flush;
   	    }

	    else{
	    	//if no given options are entered
	    	cout << "Enter a valid option" << endl;
	    }
	}

}


int main() {
	//created in lab
	//so the tests and option menu isn't running each time the tests do
	cout << "Press '0' to run tests or '1' to manage the collection: " << flush;
	int choice;
	cin >> choice;

	if(choice == 0){
		//if the user wants to run tests
		MovieTester mt;
		mt.runTests();
		CollectionTester ct;
		ct.runTests();
	}

	if(choice == 1){
		//if the user wants to manage movie collection
		optionMenu();
	}
}

